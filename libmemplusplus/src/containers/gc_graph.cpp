#include "mpplib/containers/gc_graph.hpp"

namespace mpp {
    GcGraph::GcGraph()
    {}

    GcGraph::~GcGraph()
    {
        Clear();
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

    Vertex* GcGraph::FindVertex(Chunk* t_chunk)
    {
        std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>(t_chunk);
        auto foundVertexIt = m_adjList.find(vertex.get());
        if (foundVertexIt != m_adjList.end())
            return *foundVertexIt;
        
        return nullptr;
    }

    std::pair<std::set<mpp::Vertex *>::iterator, bool> GcGraph::AddVertex(Vertex* t_vertex)
    {
        return m_adjList.insert(t_vertex);
    }

    bool GcGraph::RemoveVertex(Vertex* t_vertex)
    {
        return m_adjList.erase(t_vertex);
    }

    bool GcGraph::Clear()
    {
        for (Vertex* vertex : m_adjList)
            delete vertex;

        m_adjList.clear();
    }
}