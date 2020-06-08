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

    std::string GcGraph::GenerateGraphvizLayout()
    {
        std::string graphvizStr = "digraph Objects {\n";
        for (auto v1 : m_adjList)
        {
            graphvizStr += "\t\"" + v1->ToString() + "\"";
            if (v1->GetNeighbors().size() != 0)
                graphvizStr += " -> ";

            for (auto v2 : v1->GetNeighbors())
            {
                graphvizStr += "\"" + v2->ToString() + "\"" + " -> ";
            }

            if (v1->GetNeighbors().size() != 0)
                graphvizStr = graphvizStr.substr(0, graphvizStr.size() - 4);
            
            graphvizStr += ";\n";
        }

        graphvizStr += "}";

        return graphvizStr;
    }

    void GcGraph::AddEdge(Vertex* t_from, Vertex* t_to)
    {
        if (m_adjList.find(t_from) == m_adjList.end())
        {
            AddVertex(t_from);
        }

        if (m_adjList.find(t_to) == m_adjList.end())
        {
            AddVertex(t_to);
        }
        t_to->AddPointingVertex(t_from);
        t_from->AddNeighbor(t_to);
    }

    void GcGraph::RemoveEdge(Vertex* t_from, Vertex* t_to)
    {
        t_from->RemoveNeighbor(t_to);
    }

    std::pair<std::set<mpp::Vertex *>::iterator, bool> GcGraph::AddVertex(Vertex* t_vertex)
    {
        return m_adjList.insert(t_vertex);
    }

    bool GcGraph::RemoveVertex(Vertex* t_vertex)
    {
        return m_adjList.erase(t_vertex);
    }

    std::vector<std::unique_ptr<GcGraph>> GcGraph::WeaklyConnectedComponents()
    {
        // initialize weakly connected components
        // Each element in this vector contains isolated subgraph
        std::vector<std::unique_ptr<GcGraph>> weaklyConnectedComponents;
        
        // Copy of adjacence list to use with DFS
        std::set<Vertex*, VertexComparator> adjListCopy(m_adjList.begin(), m_adjList.end());

        // iteraste through all vertixes
        while (adjListCopy.empty() != true)
        {
            std::unique_ptr<GcGraph> connectedComponent = std::make_unique<GcGraph>(UndirectedDFS(*(adjListCopy.begin())));
            // delete each visited vertex from adjListCopy
            for (auto v : connectedComponent->GetAdjList())
                adjListCopy.erase(v);
            weaklyConnectedComponents.push_back(std::move(connectedComponent));
        }

        return weaklyConnectedComponents;
    }

    std::vector<Vertex*> GcGraph::DirectedDFS(Vertex* t_vertex)
    {
        std::vector<Vertex*> visited;
        DDFS(t_vertex, visited);
        return visited;
    }

    void GcGraph::DDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited)
    {
        std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(), t_vertex->GetNeighbors().end());        
        t_visited.push_back(t_vertex);
        for (auto neighbor : neighbors)
        {
            if (std::find(t_visited.begin(), t_visited.end(), neighbor) 
                            != t_visited.end() == false)
            {  
                GcGraph::DDFS(neighbor, t_visited);
            }
        }
    }

    std::vector<Vertex*> GcGraph::UndirectedDFS(Vertex* t_vertex)
    {
        std::vector<Vertex*> visited;
        UDFS(t_vertex, visited);
        return visited;
    }

    void GcGraph::UDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited)
    {
        std::vector<Vertex*> neighbors(t_vertex->GetNeighbors().begin(), t_vertex->GetNeighbors().end());
        neighbors.insert(neighbors.end(), t_vertex->GetPointingVertices().begin(), t_vertex->GetPointingVertices().end());
        t_visited.push_back(t_vertex);
        for (auto neighbor : neighbors)
        {
            if (std::find(t_visited.begin(), t_visited.end(), neighbor) 
                            != t_visited.end() == false)
            {  
                GcGraph::UDFS(neighbor, t_visited);
            }
        }
    }

    Vertex* GcGraph::FindVertex(Chunk* t_chunk)
    {
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

    bool GcGraph::Clear()
    {
        for (Vertex* vertex : m_adjList)
            delete vertex;

        m_adjList.clear();
    }
}