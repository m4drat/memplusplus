#include "mpplib/containers/gc_graph.hpp"

namespace mpp {
GcGraph::GcGraph()
{}

// WARNING: creates SHALLOW copy
GcGraph::GcGraph(GcGraph& t_other)
{
    for (auto v : t_other.GetAdjList())
        m_adjList.insert(v);
}

// WARNING: creates SHALLOW copy
GcGraph::GcGraph(const std::vector<Vertex*>& t_other)
{
    for (auto v : t_other)
        m_adjList.insert(v);
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

    Chunk* gcPtrObjectChunk = MemoryManager::GetInUseChunkByPtr(t_gcPtr->GetVoid());
    Chunk* gcPtrLocationChunk = MemoryManager::GetInUseChunkByPtr(reinterpret_cast<void*>(t_gcPtr));

    // GcPtr is lying on heap
    if (gcPtrLocationChunk != nullptr) {
        // Check that "to" vertex is already exist
        Vertex* to = FindVertex(gcPtrObjectChunk);
        if (to != nullptr) {
            to->AddGcPtr(t_gcPtr);
        } else {
            to = new Vertex(gcPtrObjectChunk);
            to->AddGcPtr(t_gcPtr);
        }
        // Check that "from" vertex is already exist
        Vertex* from = FindVertex(gcPtrLocationChunk);
        if (from == nullptr) {
            from = new Vertex(gcPtrLocationChunk);
        }
        AddEdge(from, to);
        // GcPtr isn't lying on heap
    } else {
        Vertex* vertex = FindVertex(gcPtrObjectChunk);
        if (vertex != nullptr) {
            vertex->AddGcPtr(t_gcPtr);
        } else {
            vertex = new Vertex(gcPtrObjectChunk);
            vertex->AddGcPtr(t_gcPtr);
            AddVertex(vertex);
        }
    }
}

std::ostream& GcGraph::GenerateGraphvizLayout(std::ostream& t_out) const
{
    PROFILE_FUNCTION();
    
    t_out << "digraph Objects {\n";

    // iterate for each vertex in adjacency list
    for (auto v1 : m_adjList) {
        // if current vertex has neighbours draw all connections
        if (!v1->GetNeighbors().empty()) {
            // for each neigbour draw connection between v1 and its neighbour
            for (auto it = v1->GetNeighbors().begin(); it != v1->GetNeighbors().end(); ++it) {
                t_out << "\"" << v1->ToString() << "\" [label=\"chunk = " << v1->ToString() << "\n" << "chunk.size = " << v1->GetCorrespondingChunk()->GetSize() << "\"];" << std::endl; 
                t_out << "\"" << (*it)->ToString() << "\" [label=\"chunk = " << (*it)->ToString() << "\n" << "chunk.size = " << (*it)->GetCorrespondingChunk()->GetSize() << "\"];" << std::endl; 
                t_out << "\t\"" + v1->ToString() + "\"" << " -> " << "\"" + (*it)->ToString() + "\";\n";
            }
        } else {
            t_out << "\t\"" + v1->ToString() + "\";\n";
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
    return m_adjList.erase(t_vertex);
}

std::vector<std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>> GcGraph::
  WeaklyConnectedComponents()
{
    PROFILE_FUNCTION();
    // initialize weakly connected components
    // Each element in this vector contains isolated subgraph
    std::vector<std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>> weaklyConnectedComponents;

    // Copy of adjacence list to use with DFS
    std::set<Vertex*, VertexComparator> adjListCopy(m_adjList.begin(), m_adjList.end());

    // iteraste through all vertices
    while (adjListCopy.empty() != true) {
        // Find connected component inside graph
        std::unique_ptr<GcGraph, std::function<void(GcGraph*)>> connectedComponent(
          new GcGraph(UndirectedDFS(*(adjListCopy.begin()))), [](GcGraph* t_graph) {
              t_graph->GetAdjList().clear();
              operator delete(t_graph);
          });

        // delete each visited vertex from adjListCopy
        for (auto v : connectedComponent->GetAdjList()) {
            adjListCopy.erase(v);
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
    PROFILE_FUNCTION();
    std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(),
                                   t_vertex->GetNeighbors().end());
    t_visited.push_back(t_vertex);
    for (auto neighbor : neighbors) {
        if ((std::find(t_visited.begin(), t_visited.end(), neighbor) != t_visited.end()) == false) {
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
    PROFILE_FUNCTION();
    std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(),
                                   t_vertex->GetNeighbors().end());
    neighbors.insert(neighbors.end(),
                     t_vertex->GetPointingVertices().begin(),
                     t_vertex->GetPointingVertices().end());
    t_visited.push_back(t_vertex);
    for (auto neighbor : neighbors) {
        if ((std::find(t_visited.begin(), t_visited.end(), neighbor) != t_visited.end()) == false) {
            GcGraph::UDFS(neighbor, t_visited);
        }
    }
}

Vertex* GcGraph::FindVertex(Chunk* t_chunk)
{
    PROFILE_FUNCTION();
    std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>(t_chunk);
    auto foundVertexIt = m_adjList.find(vertex.get());
    if (foundVertexIt != m_adjList.end())
        return *foundVertexIt;

    return nullptr;
}

int32_t GcGraph::GetGraphVerticesCount()
{
    return m_adjList.size();
}

std::set<Vertex*, GcGraph::VertexComparator>& GcGraph::GetAdjList()
{
    return m_adjList;
}
}