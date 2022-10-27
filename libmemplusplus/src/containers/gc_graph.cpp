#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/containers/vertex.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/utils.hpp"

namespace mpp {
    // WARNING: creates SHALLOW copy
    GcGraph::GcGraph(GcGraph& t_other)
    {
        for (auto* vertex : t_other.GetAdjList()) {
            m_adjList.insert(vertex);
        }
    }

    // WARNING: creates SHALLOW copy
    GcGraph::GcGraph(const std::vector<Vertex*>& t_other)
    {
        for (auto* vertex : t_other) {
            m_adjList.insert(vertex);
        }
    }

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

        Chunk* gcPtrObjectChunk = GC::FindChunkInUse(t_gcPtr->GetVoid());
        Chunk* gcPtrLocationChunk = GC::FindChunkInUse(t_gcPtr);

        // Check that "to" vertex already exists in graph
        Vertex* destination = FindVertex(gcPtrObjectChunk);
        if (destination != nullptr) {
            destination->AddGcPtr(t_gcPtr);
        } else {
            destination = new Vertex(gcPtrObjectChunk);
            destination->AddGcPtr(t_gcPtr);
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
            Vertex* origin = FindVertex((Chunk*)t_gcPtr);
            if (origin == nullptr) {
                origin = new Vertex((std::byte*)t_gcPtr);
            }
            AddEdge(origin, destination);
        }
    }

    std::ostream& GcGraph::GenerateGraphvizLayoutSimple(std::ostream& t_out) const
    {
        PROFILE_FUNCTION();

        const std::string colorRed = "#fbb4ae";
        const std::string colorOrange = "#fed9a6";
        const std::string colorGreen = "#ccebc5";
        const std::string colorGray = "#cccccc";
        const std::string colorLightPurple = "#bcbddc";

        t_out << "digraph Objects {\n";
        t_out << "\tnode[ style=filled ];\n";

        // Create all chunks
        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\"" << chunkAddrStr << "\" [ fillcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                t_out << "\" label=\"chunk\\n"
                      << chunkAddrStr << "\\n"
                      << "size = " << currChunk->GetSize() << "\"];\n";
            }
        }

        // Draw connections between chunks
        for (auto* vtx1 : m_adjList) {
            // We don't want to draw GC pointers
            if (!vtx1->IsChunk())
                continue;

            // if current vertex has neighbors draw all connections
            // for each neighbor draw connection between vtx1 and its neighbour
            for (auto it = vtx1->GetNeighbors().begin(); it != vtx1->GetNeighbors().end(); ++it) {
                t_out << "\t\"" + vtx1->ToString() + "\""
                      << " -> "
                      << "\"" + (*it)->ToString() + "\";\n";
            }
        }

        // Generate flat heap view
        t_out << "\tnode[ shape = none style = \"\" ];\n";
        t_out << "\theap[ label=<\n";
        t_out << "\t<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
        t_out << "\t\t<TR>\n";

        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\t\t"
                      << "<TD bgcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                t_out << "\" PORT=\"" << chunkAddrStr << "\">"
                      << chunkAddrStr.substr(chunkAddrStr.length() - 5) << "</TD>"
                      << "\n";
            }
            t_out << "\t\t\t"
                  << "<TD>.....</TD>"
                  << "\n";
        }

        t_out << "\t\t</TR>\n";
        t_out << "\t</table>>];\n";

        // Draw connection to the flat heap view
        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                std::string chunkAddrStr = utils::AddrToString((void*)pos);
                t_out << "\t\"" << chunkAddrStr << "\" -> heap:\"" << chunkAddrStr
                      << "\" [style=dashed, color=\"" << colorLightPurple << "\"];\n";
            }
        }

        t_out << "}";

        return t_out;
    }

    std::ostream& GcGraph::GenerateGraphvizLayoutAdvanced(std::ostream& t_out) const
    {
        PROFILE_FUNCTION();

        const std::string colorRed = "#fbb4ae";
        const std::string colorOrange = "#fed9a6";
        const std::string colorGreen = "#ccebc5";
        const std::string colorGray = "#cccccc";
        const std::string colorLightPurple = "#bcbddc";

        t_out << "digraph Objects {\n";
        t_out << "\tcompound=true;\n";
        t_out << "\tratio=expand;\n";
        t_out << "\tgraph [ranksep=1.5]\n";
        t_out << "\tnewrank=true;\n\n";

        // Generate flat heap view
        t_out << "\t// Draw flat heap layout\n";
        t_out << "\theap[ shape = none style = \"\" ];\n";
        t_out << "\theap[ label=<\n";
        t_out << "\t<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
        t_out << "\t\t<TR>\n";

        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                Chunk* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\t\t"
                      << "<TD bgcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                t_out << "\" PORT=\"" << chunkAddrStr << "\">"
                      << chunkAddrStr.substr(chunkAddrStr.length() - 5) << "</TD>"
                      << "\n";
            }
            t_out << "\t\t\t"
                  << "<TD>.....</TD>"
                  << "\n";
        }

        t_out << "\t\t</TR>\n";
        t_out << "\t</table>>];\n\n";

        t_out << "\t// Draw all chunks (begin)\n";
        t_out << "\tnode[ style=\"filled\" ];\n";

        std::set<GcPtr*> nonHeapGcPtrs = GC::GetInstance().GetOrderedGcPtrs();
        std::set<GcPtr*> orderedGcPtrs = nonHeapGcPtrs;

        uint32_t gcptrIndex = 1;

        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                Chunk* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                std::string chunkLabel = "label=\"chunk\\n" + chunkAddrStr + "\\n" +
                                         "size = " + std::to_string(currChunk->GetSize()) + "\"";
                std::string chunkColor;

                if (arena->TopChunk() == currChunk) {
                    chunkColor = colorOrange;
                } else if (currChunk->IsUsed()) {
                    chunkColor = colorGreen;
                } else {
                    chunkColor = colorRed;
                }

                auto chunkAsVertex = FindVertex(currChunk);
                if (!chunkAsVertex || chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()) {
                    // Current chunk doesn't have GC-pointers inside
                    t_out << "\t\"" << chunkAddrStr << "\" [fillcolor=\"" << chunkColor << "\", "
                          << chunkLabel << "];\n";
                } else {
                    // Current chunk does have GC-pointers inside
                    t_out << "\tsubgraph \"cluster-" << chunkAddrStr << "\" {\n";
                    t_out << "\t\trank=same;\n";
                    t_out << "\t\t" << chunkLabel << ";\n";
                    t_out << "\t\tstyle=\"rounded,filled\";\n";
                    t_out << "\t\tfillcolor=\"" << chunkColor << "\";\n";
                    t_out << "\t\tsubgraph \"cluster\" {\n";
                    t_out << "\t\t\tstyle=\"dashed\";\n";
                    t_out << "\t\t\tlabel=\"\";\n";

                    for (auto* gcPtr : chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs)) {
                        nonHeapGcPtrs.erase(gcPtr);
                        // std::cout << "Vertex: [" << chunkAsVertex << "] -> Chunk: [" <<
                        // chunkAddrStr
                        //           << "] -> GcPtr: " << utils::AddrToString(gcPtr->GetVoid())
                        //           << std::endl;
                        std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
                        t_out << "\t\t\t\"" << gcPtrAddrStr
                              << "\" [style=\"filled,dashed\", fillcolor=\"" << chunkColor
                              << "\", shape=box, label=\"gcptr-" << gcptrIndex++ << "\"];\n";
                    }

                    t_out << "\t\t}\n";
                    t_out << "\t}\n";
                }

                if (!chunkAsVertex)
                    continue;

                // Draw connections between GC-pointers and chunks
                t_out << "\n\t// Draw connections between GC-pointers from current chunk "
                      << chunkAddrStr << " and chunks\n";
                for (auto* gcPtr : chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs)) {
                    std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
                    Chunk* pointsToChunk = GC::FindChunkInUse(gcPtr->GetVoid());
                    Vertex* pointsToVertex = FindVertex(pointsToChunk);
                    bool pointsToCluster =
                        (pointsToVertex)
                            ? !pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                            : false;

                    t_out
                        << "\t\"" << gcPtrAddrStr << "\":s -> \""
                        << ((pointsToCluster)
                                ? utils::AddrToString(
                                      *pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                                : utils::AddrToString(pointsToChunk))
                        << "\"";

                    if (pointsToCluster) {
                        t_out << " [lhead=\"cluster-" << utils::AddrToString(pointsToChunk)
                              << "\"]";
                    }

                    t_out << ";\n";
                }
            }
        }

        t_out << "\t// Draw all chunks (end)\n";

        // Draw GC-pointers that are not on the heap
        t_out << "\n\t// Draw connections between non-heap GC-pointers and chunks\n";
        for (auto* gcPtr : nonHeapGcPtrs) {
            std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
            Chunk* pointsToChunk = GC::FindChunkInUse(gcPtr->GetVoid());
            Vertex* pointsToVertex = FindVertex(pointsToChunk);
            bool pointsToCluster =
                (pointsToVertex) ? !pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                                 : false;

            t_out << "\t\"" << gcPtrAddrStr << "\" [style=filled, fillcolor=\"" << colorGray
                  << "\", shape=rect, label=\"gcptr-" << gcptrIndex++ << "\"];\n";

            // Draw connections between non-heap GC-pointers and chunks
            t_out << "\t\"" << gcPtrAddrStr << "\":s -> \""
                  << ((pointsToCluster)
                          ? utils::AddrToString(
                                *pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                          : utils::AddrToString(pointsToChunk))
                  << "\"";

            if (pointsToCluster) {
                t_out << " [lhead=\"cluster-" << utils::AddrToString(pointsToChunk) << "\"]";
            }

            t_out << ";\n";
        }

        // Draw connection to the flat heap view
        t_out << "\n\t// Draw connections from all chunks to the flat heap view\n";
        for (auto* arena : MemoryManager::GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);

                Vertex* chunkVertex = FindVertex(currChunk);
                bool isCluster = (chunkVertex)
                                     ? !chunkVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                                     : false;

                t_out << "\t\""
                      << ((isCluster)
                              ? utils::AddrToString(
                                    *chunkVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                              : utils::AddrToString(currChunk))
                      << "\" -> heap:\"" << chunkAddrStr << "\"";

                if (isCluster) {
                    t_out << " [ltail=\"cluster-" << chunkAddrStr << "\", style=dashed, color=\""
                          << colorLightPurple << "\"]";
                } else {
                    t_out << " [style=dashed, color=\"" << colorLightPurple << "\"]";
                }

                t_out << ";\n";
            }
        }

        t_out << "}";

        return t_out;
    }

    void GcGraph::AddEdge(Vertex* t_from, Vertex* t_to)
    {
        PROFILE_FUNCTION();
        // Check if we already have starting vertex
        if (m_adjList.find(t_from) == m_adjList.end()) {
            AddVertex(t_from);
        }

        // Check if we already have ending vertex
        if (m_adjList.find(t_to) == m_adjList.end()) {
            AddVertex(t_to);
        }

        // Update vector of pointing to vertices
        t_to->AddPointingVertex(t_from);

        // Create connection between two vertices
        t_from->AddNeighbor(t_to);
    }

    bool GcGraph::HasEdge(Vertex* t_from, Vertex* t_to) const
    {
        if (m_adjList.find(t_from) == m_adjList.end() || m_adjList.find(t_to) == m_adjList.end())
            return false;

        if (t_from->GetNeighbors().find(t_to) == t_from->GetNeighbors().end())
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

    bool GcGraph::RemoveVertex(Vertex* t_vertex)
    {
        // Remove all edges that are pointing to this vertex
        for (auto* pointingVertex : t_vertex->GetPointingVertices()) {
            RemoveEdge(pointingVertex, t_vertex);
            // if (t_vertex->IsChunk()) {
            //     pointingVertex->RemoveGcPtr(t_vertex->GetLoc());
            // }
        }

        return m_adjList.erase(t_vertex);
    }

    std::vector<std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>> GcGraph::
        WeaklyConnectedComponents()
    {
        PROFILE_FUNCTION();
        // initialize weakly connected components
        // Each element in this vector contains isolated subgraph
        std::vector<std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>>
            weaklyConnectedComponents;

        // Copy of adjacency list to use with DFS
        std::set<Vertex*, VertexComparator> adjListCopy(m_adjList.begin(), m_adjList.end());

        // iterate through all vertices
        while (!adjListCopy.empty()) {
            // Find connected component inside graph
            std::unique_ptr<GcGraph, std::function<void(GcGraph*)>> connectedComponent(
                new GcGraph(UndirectedDFS(*(adjListCopy.begin()))), [](GcGraph* t_graph) {
                    t_graph->GetAdjList().clear();
                    operator delete(t_graph);
                });

            // delete each visited vertex from adjListCopy
            for (auto* vtx : connectedComponent->GetAdjList()) {
                adjListCopy.erase(vtx);
            }

            // Add found component to vector
            weaklyConnectedComponents.push_back(std::move(connectedComponent));
        }

        return weaklyConnectedComponents;
    }

    std::vector<Vertex*> GcGraph::DirectedDFS(Vertex* t_vertex)
    {
        PROFILE_FUNCTION();
        // Vector of visited vertices using directed DFS
        std::vector<Vertex*> visited;

        // Perform directed DFS, starting from t_vertex
        DDFS(t_vertex, visited);

        return visited;
    }

    void GcGraph::DDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited)
    {
        std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(),
                                       t_vertex->GetNeighbors().end());
        t_visited.push_back(t_vertex);
        for (auto* neighbor : neighbors) {
            if (std::find(t_visited.begin(), t_visited.end(), neighbor) == t_visited.end()) {
                GcGraph::DDFS(neighbor, t_visited);
            }
        }
    }

    std::vector<Vertex*> GcGraph::UndirectedDFS(Vertex* t_vertex)
    {
        PROFILE_FUNCTION();
        // Vector of visited vertices using undirected DFS
        std::vector<Vertex*> visited;

        // Perform undirected DFS, starting from t_vertex
        UDFS(t_vertex, visited);

        return visited;
    }

    void GcGraph::UDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited)
    {
        std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(),
                                       t_vertex->GetNeighbors().end());
        neighbors.insert(neighbors.end(),
                         t_vertex->GetPointingVertices().begin(),
                         t_vertex->GetPointingVertices().end());
        t_visited.push_back(t_vertex);
        for (auto* neighbor : neighbors) {
            if (std::find(t_visited.begin(), t_visited.end(), neighbor) == t_visited.end()) {
                GcGraph::UDFS(neighbor, t_visited);
            }
        }
    }

    Vertex* GcGraph::FindVertex(Chunk* t_chunk) const
    {
        PROFILE_FUNCTION();
        std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>(t_chunk);
        auto foundVertexIt = m_adjList.find(vertex.get());
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
}