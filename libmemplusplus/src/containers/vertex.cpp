#include "mpplib/containers/vertex.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/utils.hpp"

namespace mpp {
    bool Vertex::IsChunk() const
    {
        return m_currLocationIsAChunk;
    }

    void Vertex::UpdateLocationPtr(std::byte* t_location)
    {
        m_correspondingLocation = t_location;
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
        std::set<GcPtr*>::iterator begin;
        std::set<GcPtr*>::iterator end;

        begin = t_gcPtrs.lower_bound((GcPtr*)m_correspondingLocation);
        if (m_currLocationIsAChunk) {
            end = t_gcPtrs.upper_bound(
                (GcPtr*)(m_correspondingLocation + GetLocationAsAChunk()->GetSize()));
        } else {
            end = t_gcPtrs.upper_bound((GcPtr*)(m_correspondingLocation));
        }

        return std::set<GcPtr*>(begin, end);
    }

    std::set<GcPtr*>& Vertex::GetPointingToGcPtrs()
    {
        return m_pointingToGcPtrs;
    }

    std::byte* Vertex::GetLoc() const
    {
        return m_correspondingLocation;
    }

    Chunk* Vertex::GetLocationAsAChunk() const
    {
        MPP_ASSERT(m_currLocationIsAChunk, "Current location is not a chunk!");
        return reinterpret_cast<Chunk*>(m_correspondingLocation);
    }

    std::string Vertex::ToString() const
    {
        std::stringstream ss;
        ss << static_cast<const void*>(m_correspondingLocation);
        return ss.str();
    }
}