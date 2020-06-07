#include "mpplib/containers/gc_graph.hpp"

namespace mpp {
    GcGraph::GcGraph()
    {}

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