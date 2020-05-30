#pragma once

#include "mpplib/chunk.hpp"
#include <vector>

namespace mpp {
    struct Arena
    {
        /**
         * What we should use to save information about freed/in-use blocks?
         * Should we save all active blocks + all freed blocks, or we just need
         * to save one list? Requrements for data structure:
         *     1. Find max element
         *     2. Fast insert/delete
         *     3. Fast exact search
         *     4. Find bigger or equal element
         *      ===> Treap
         */
        std::vector<Chunk*> chunksInUse;
        std::size_t size{ 0 };
        std::size_t rightSpace{ 0 };
        //std::size_t maxBetweenSpace{ 0 };
        void* begin{ nullptr };
        void* rightSpaceStart{ nullptr };
        void* end{ nullptr };

        Arena(std::size_t t_size, void* t_begin)//, void* t_end)
        {
            size = t_size;
            rightSpaceStart = t_begin;
            begin = t_begin;
            end = reinterpret_cast<void*>((std::size_t)t_begin + t_size);
        };

        // Find chunk in ChunkTreap (tree of freed chunks)
        Chunk* MaxSizeChunk();
        Chunk* GetFirstGreaterOrEqualThanChunk(std::size_t t_desiredChunkSize);
        // Use already found chunk of suitable size, and split it if needed
        Chunk* ReuseChunk(Chunk* t_chunk, std::size_t t_chunkSize);
        // Just allocate from right side
        Chunk* AllocateChunkFromRightSpace(std::size_t t_chunkSize);
        // merge all consequently placed freed chunks
        void MergeNeighborsChunks(Chunk* t_chunk);
        void DeallocateChunk(Chunk* t_chunk);
    };
}