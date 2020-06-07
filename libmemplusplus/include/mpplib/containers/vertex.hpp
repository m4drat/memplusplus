#pragma once

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include <mpplib/chunk.hpp>
#include <mpplib/gcptr.hpp>

namespace mpp {
    // Represents chunk in graph
    class Vertex
    {
    private:
        Chunk* m_correspondingChunk;
        std::set<Vertex*> m_neighbors;
        std::vector<GcPtr*> m_pointingToGcPtrs;

    public:
        Vertex() = delete;
        Vertex(Chunk* t_chunk)
            : m_correspondingChunk(t_chunk)
        {}
        
        void UpdateChunkPtr(Chunk* t_chunk);

        void AddNeighbor(Vertex* t_neigbor);
        bool RemoveNeighbor(Vertex* t_neigbor);
        std::set<Vertex*>& GetNeighbors();

        void AddGcPtr(GcPtr* t_gcPtr);
        bool RemoveGcPtr(GcPtr* t_gcPtr);
        std::vector<GcPtr*>& GetPointingToGcPtrs();

        Chunk* GetCorrespondingChunk() const;
        std::string ToString() const;
    };
}