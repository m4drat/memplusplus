#include "mpplib/containers/vertex.hpp"

namespace mpp {
    void Vertex::UpdateChunkPtr(Chunk* t_chunk)
    {
        m_correspondingChunk = t_chunk;
    }

    void Vertex::AddNeighbor(Vertex* t_neigbor)
    {
        m_neighbors.insert(t_neigbor);
    }

    void Vertex::AddPointingVertex(Vertex* t_pointingVertex)
    {
        m_pointingToVertices.insert(t_pointingVertex);
    }

    std::set<Vertex*>& Vertex::GetPointingVertices()
    {
        return m_pointingToVertices;
    }

    bool Vertex::RemoveNeighbor(Vertex* t_neigbor)
    {
        return m_neighbors.erase(t_neigbor);
    }

    std::set<Vertex*>& Vertex::GetNeighbors()
    {
        return m_neighbors;
    }

    void Vertex::AddGcPtr(GcPtr* t_gcPtr)
    {
        m_pointingToGcPtrs.push_back(t_gcPtr);
    }

    bool Vertex::RemoveGcPtr(GcPtr* t_gcPtr)
    {
        // Remove GcPtr pointer from current vertex
        auto toErase =
          std::find(m_pointingToGcPtrs.begin(), m_pointingToGcPtrs.end(), t_gcPtr);
        if (toErase != m_pointingToGcPtrs.end()) {
            m_pointingToGcPtrs.erase(toErase);
            return true;
        }
        return false;
    }

    std::vector<GcPtr*>& Vertex::GetPointingToGcPtrs()
    {
        return m_pointingToGcPtrs;
    }

    Chunk* Vertex::GetCorrespondingChunk() const
    {
        return m_correspondingChunk;
    }

    std::string Vertex::ToString() const
    {
        std::stringstream ss;
        ss << static_cast<const void*>(m_correspondingChunk);
        return ss.str();
    }
}