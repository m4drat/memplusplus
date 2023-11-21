#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/containers/vertex.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/utils.hpp"
#include <cstdint>
#include <memory>
#include <stack>

namespace mpp {
    GcGraph::~GcGraph()
    {
        Clear();
    }

    bool GcGraph::Clear()
    {
        PROFILE_FUNCTION();

        // delete each vertex from graph
        for (Vertex* vertex : m_adjList) {
            delete vertex;
            vertex = nullptr;
        }

        m_adjList.clear();
        return true;
    }

    void GcGraph::AddObjectInfo(GcPtr* t_gcPtr)
    {
        PROFILE_FUNCTION();
        Chunk* gcPtrObjectChunk = m_gc.FindChunkInUse(t_gcPtr->GetVoid());
        Chunk* gcPtrLocationChunk = m_gc.FindChunkInUse(t_gcPtr);

        // Check that "to" vertex already exists in graph
        Vertex* destination = FindVertex(gcPtrObjectChunk);
        if (destination != nullptr) {
            destination->AddGcPtr(t_gcPtr);
        } else {
            destination = new Vertex(gcPtrObjectChunk);
            destination->AddGcPtr(t_gcPtr);

            // Added to support reference cycles (gcPtrLocationChunk == gcPtrLocationChunk).
            // If gcptr from inside the chunk points to the chunk it is located inside, we want to
            // create only one vertex as it is the beginning and the end. Otherwise we might create
            // 2 separate vertices which will point to the same location, which in turn will result
            // in an incorrectly functioning GC.
            AddVertex(destination);
        }

        // GcPtr is on the heap
        if (gcPtrLocationChunk != nullptr) {
            // Check that "from" vertex already exist in graph
            Vertex* origin = FindVertex(gcPtrLocationChunk);
            if (origin == nullptr) {
                origin = new Vertex(gcPtrLocationChunk);
            }
            AddEdge(origin, destination);
        } else {
            // GcPtr isn't on the heap
            // Check that "from" vertex already exist in graph

            // We don't really care about the location of the GcPtr,
            // thus it is okay to cast t_gcPtr to Chunk*
            Vertex* origin = FindVertex(reinterpret_cast<Chunk*>(t_gcPtr));
            if (origin == nullptr) {
                origin = new Vertex(reinterpret_cast<std::byte*>(t_gcPtr));
            }
            AddEdge(origin, destination);

            // This is the root vertex (non-heap located). Add it to the list of all root vertices
            // to later filter-out non-reachable vertices.
            AddRootVertex(origin);
        }
    }

    void GcGraph::AddEdge(Vertex* t_from, Vertex* t_to)
    {
        PROFILE_FUNCTION();
        // Check if we already have starting vertex
        if (!m_adjList.contains(t_from)) {
            AddVertex(t_from);
        }

        // Check if we already have ending vertex
        if (!m_adjList.contains(t_to)) {
            AddVertex(t_to);
        }

        // Update vector of pointing to vertices
        t_to->AddPointingVertex(t_from);

        // Create connection between two vertices
        t_from->AddNeighbor(t_to);
    }

    bool GcGraph::HasEdge(Vertex* t_from, Vertex* t_to) const
    {
        if (!m_adjList.contains(t_from) || !m_adjList.contains(t_to))
            return false;

        if (!t_from->GetNeighbors().contains(t_to))
            return false;

        return true;
    }

    void GcGraph::RemoveEdge(Vertex* t_from, Vertex* t_to)
    {
        t_from->RemoveNeighbor(t_to);
    }

    std::pair<std::set<mpp::Vertex*>::iterator, bool> GcGraph::AddVertex(Vertex* t_vertex)
    {
        return m_adjList.insert(t_vertex);
    }

    std::pair<std::set<mpp::Vertex*>::iterator, bool> GcGraph::AddRootVertex(Vertex* t_vertex)
    {
        return m_roots.insert(t_vertex);
    }

    bool GcGraph::RemoveVertex(Vertex* t_vertex)
    {
        // Remove all edges that are pointing to this vertex
        for (auto* pointingVertex : t_vertex->GetPointingVertices()) {
            RemoveEdge(pointingVertex, t_vertex);
        }

        return m_adjList.erase(t_vertex);
    }

    std::vector<std::unique_ptr<GcGraphView>> GcGraph::WeaklyConnectedComponents()
    {
        PROFILE_FUNCTION();

        // Each element in this vector contains isolated subgraph.
        std::vector<std::unique_ptr<GcGraphView>> weaklyConnectedComponents;

        // Copy of adjacency list to use with DFS.
        std::set<Vertex*, VertexComparator> adjListCopy(m_adjList.begin(), m_adjList.end());

        // Iterate through all vertices.
        while (!adjListCopy.empty()) {
            // Find connected component inside the graph.
            auto connectedComponent = UndirectedDFS(*(adjListCopy.begin()));

            // Delete each visited vertex from adjListCopy.
            for (auto* vtx : connectedComponent->GetAdjList()) {
                adjListCopy.erase(vtx);
            }

            // Add found component to the vector.
            weaklyConnectedComponents.push_back(std::move(connectedComponent));
        }

        return weaklyConnectedComponents;
    }

    std::vector<std::unique_ptr<GcGraphView>> GcGraph::ReachableWeaklyConnectedComponents()
    {
        PROFILE_FUNCTION();

        auto& orderedActiveGcPtrs = m_gc.GetOrderedGcPtrs();

        // Each element in this vector contains isolated subgraph.
        auto weaklyConnectedComponents = WeaklyConnectedComponents();

        // List of all weakly-connected components, but with the guarantee that each vertex is
        // reachable from the root.
        std::vector<std::unique_ptr<GcGraphView>> reachableComponents;
        reachableComponents.reserve(weaklyConnectedComponents.size());

        // For each subgraph we want to perform DFS starting from the root nodes to find only
        // reachable vertices.
        for (auto& component : weaklyConnectedComponents) {
            std::unordered_set<Vertex*> reachable;

            // Collect all directly-reachable vertices
            for (auto* rootVtx : component->GetRoots()) {
                auto rootReachable = DirectedDFS(rootVtx, reachable);
                reachable.insert(rootReachable->GetAdjList().begin(),
                                 rootReachable->GetAdjList().end());
            }

            // Remove all non-reachable GcPtr's from the set of active gcptr's.
            for (auto* unreachableVtx : component->GetAdjList()) {
                // Check if the vertex is not in the reachable graph.
                if (reachable.contains(unreachableVtx)) {
                    continue;
                }

                // Remove all GcPtr's that reference the current vertex.
                for (auto* unreachableGcPtr : unreachableVtx->GetPointingToGcPtrs()) {
                    orderedActiveGcPtrs.erase(unreachableGcPtr);
                }

                // Remove all GcPtr's that are referenced by the current vertex.
                auto curVtxReferences = unreachableVtx->GetAllOutgoingGcPtrs(orderedActiveGcPtrs);
                for (auto* unreachableGcPtr : curVtxReferences) {
                    orderedActiveGcPtrs.erase(unreachableGcPtr);
                }

                // Update set of pointing-to vertices for each neighbor of the unreachable vertex.
                for (auto* neighbor : unreachableVtx->GetNeighbors()) {
                    std::erase_if(neighbor->GetPointingVertices(),
                                  [unreachableVtx](const Vertex* t_vertex) {
                                      return t_vertex == unreachableVtx;
                                  });
                }
            }

            // Do not process this component any further if we don't have any vertices.
            if (reachable.empty()) {
                continue;
            }

            reachableComponents.emplace_back(std::make_unique<GcGraphView>(
                reachable, component->GetRoots(), m_gc, m_memoryManager));
        }

        return reachableComponents;
    }

    std::unique_ptr<GcGraphView> GcGraph::DirectedDFS(
        Vertex* t_vertex,
        const std::unordered_set<Vertex*>& t_externalVisited)
    {
        PROFILE_FUNCTION();
        // Vector of visited vertices using directed DFS
        std::unordered_set<Vertex*> visited;

        // Vector of visited root-vertices.
        std::unordered_set<Vertex*> roots;

        // Perform directed DFS, starting from t_vertex
        std::stack<Vertex*> stack;
        stack.push(t_vertex);

        while (!stack.empty()) {
            Vertex* vtx = stack.top();
            stack.pop();

            if (t_externalVisited.contains(vtx)) {
                continue;
            }

            if (visited.contains(vtx)) {
                continue;
            }

            visited.insert(vtx);

            // Update roots set, if current vertex is the root.
            if (vtx->IsRoot()) {
                roots.insert(vtx);
            }

            // Visit all directly-reachable neighbors.
            for (auto* neighbor : vtx->GetNeighbors()) {
                if (!visited.contains(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }

        return std::make_unique<GcGraphView>(visited, roots, m_gc, m_memoryManager);
    }

    std::unique_ptr<GcGraphView> GcGraph::UndirectedDFS(Vertex* t_vertex)
    {
        PROFILE_FUNCTION();
        // Vector of visited vertices.
        std::unordered_set<Vertex*> visited;

        // Vector of visited root-vertices.
        std::unordered_set<Vertex*> roots;

        // Perform undirected DFS, starting from t_vertex
        std::stack<Vertex*> stack;
        stack.push(t_vertex);

        while (!stack.empty()) {
            Vertex* vtx = stack.top();
            stack.pop();

            if (visited.contains(vtx)) {
                continue;
            }

            visited.insert(vtx);

            // Update roots set, if current vertex is the root.
            if (vtx->IsRoot()) {
                roots.insert(vtx);
            }

            // Visit all directly-reachable neighbors.
            for (auto* neighbor : vtx->GetNeighbors()) {
                if (!visited.contains(neighbor)) {
                    stack.push(neighbor);
                }
            }

            // Visit all neighbors that can't be visited by going through the neighbors set.
            for (auto* neighbor : vtx->GetPointingVertices()) {
                if (!visited.contains(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }

        return std::make_unique<GcGraphView>(visited, roots, m_gc, m_memoryManager);
    }

    Vertex* GcGraph::FindVertex(Chunk* t_chunk) const
    {
        PROFILE_FUNCTION();
        Vertex vertex{ t_chunk };
        auto foundVertexIt = m_adjList.find(&vertex);
        if (foundVertexIt != m_adjList.end()) {
            return *foundVertexIt;
        }

        return nullptr;
    }

    uint32_t GcGraph::GetVerticesCount()
    {
        return m_adjList.size();
    }

    std::set<Vertex*, GcGraph::VertexComparator>& GcGraph::GetAdjList()
    {
        return m_adjList;
    }

    std::set<Vertex*, GcGraph::VertexComparator>& GcGraph::GetRoots()
    {
        return m_roots;
    }
}