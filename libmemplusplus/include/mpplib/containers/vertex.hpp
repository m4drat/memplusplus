#pragma once

#include <set>
#include <vector>
#include <algorithm>

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

        void AddGcPtr(GcPtr* t_gcPtr);
        bool RemoveGcPtr(GcPtr* t_gcPtr);

        Chunk* GetCorrespondingChunk() const;
    };
}