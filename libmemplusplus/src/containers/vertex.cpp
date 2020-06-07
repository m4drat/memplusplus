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

    bool Vertex::RemoveNeighbor(Vertex* t_neigbor)
    {
        return m_neighbors.erase(t_neigbor);
    }

    void Vertex::AddGcPtr(GcPtr* t_gcPtr)
    {
        m_pointingToGcPtrs.push_back(t_gcPtr);
    }

    bool Vertex::RemoveGcPtr(GcPtr* t_gcPtr)
    {
        auto toErase = std::find(m_pointingToGcPtrs.begin(), m_pointingToGcPtrs.end(), t_gcPtr);
        if (toErase != m_pointingToGcPtrs.end())
        {
            m_pointingToGcPtrs.erase(toErase);
            return true;
        }
        return false;
    }

    Chunk* Vertex::GetCorrespondingChunk() const
    {
        return m_correspondingChunk;
    }
}