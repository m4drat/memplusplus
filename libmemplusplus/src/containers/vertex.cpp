#include "mpplib/containers/vertex.hpp"
#include "mpplib/gc.hpp"

namespace mpp {
    void Vertex::UpdateChunkPtr(Chunk* t_chunk)
    {
        m_correspondingChunk = t_chunk;
    }

    void Vertex::AddNeighbor(Vertex* t_neighbor)
    {
        m_neighbors.insert(t_neighbor);
    }

    void Vertex::AddPointingVertex(Vertex* t_pointingVertex)
    {
        m_pointingToVertices.insert(t_pointingVertex);
    }

    std::set<Vertex*>& Vertex::GetPointingVertices()
    {
        return m_pointingToVertices;
    }

    bool Vertex::RemoveNeighbor(Vertex* t_neighbor)
    {
        return m_neighbors.erase(t_neighbor);
    }

    std::set<Vertex*>& Vertex::GetNeighbors()
    {
        return m_neighbors;
    }

    void Vertex::AddGcPtr(GcPtr* t_gcPtr)
    {
        m_pointingToGcPtrs.insert(t_gcPtr);
    }

    bool Vertex::RemoveGcPtr(GcPtr* t_gcPtr)
    {
        PROFILE_FUNCTION();
        // Remove GcPtr pointer from current vertex
        auto toErase = m_pointingToGcPtrs.find(t_gcPtr);
        if (toErase != m_pointingToGcPtrs.end()) {
            m_pointingToGcPtrs.erase(toErase);
            return true;
        }
        return false;
    }

    std::set<GcPtr*> Vertex::GetAllOutgoingGcPtrs(std::set<GcPtr*>& t_gcPtrs)
    {
        auto begin = t_gcPtrs.lower_bound((GcPtr*)m_correspondingChunk);
        auto end =
            t_gcPtrs.upper_bound((GcPtr*)(m_correspondingChunk + m_correspondingChunk->GetSize()));

        return std::set<GcPtr*>(begin, end);
    }

    std::set<GcPtr*>& Vertex::GetPointingToGcPtrs()
    {
        return m_pointingToGcPtrs;
    }

    Chunk* Vertex::GetCorrespondingChunk() const
    {
        return m_correspondingChunk;
    }

    std::byte* Vertex::GetCorrespondingChunkAsBytePtr() const
    {
        return reinterpret_cast<std::byte*>(m_correspondingChunk);
    }

    std::string Vertex::ToString() const
    {
        std::stringstream ss;
        ss << static_cast<const void*>(m_correspondingChunk);
        return ss.str();
    }
}