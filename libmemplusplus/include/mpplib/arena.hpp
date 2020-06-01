#pragma once

#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/chunk.hpp"
#include <vector>
#include <set>

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
        ChunkTreap freedChunks;

        // TODO: check if we don't need specific comparator
        // Add 
        std::set<Chunk*> chunksInUse;
        std::size_t size{ 0 };
        Chunk* topChunk{ nullptr };
        void* begin{ nullptr };
        void* end{ nullptr };

        Arena(std::size_t t_size, void* t_begin)//, void* t_end)
        {
            size = t_size;
            topChunk = Chunk::ConstructChunk(t_begin, 0, t_size, 1, 1);
            begin = t_begin;
            end = reinterpret_cast<void*>((std::size_t)t_begin + t_size);
        };

        // Find chunk in ChunkTreap (tree of freed chunks)
        Chunk* MaxSizeChunk();
        Chunk* GetFirstGreaterOrEqualThanChunk(std::size_t t_desiredChunkSize);
        // Use already found chunk of suitable size, and split it if needed
        Chunk* AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);
        // Just allocate from right side
        Chunk* AllocateFromTopChunk(std::size_t t_chunkSize);
        // merge all consequently placed freed chunks
        Chunk* MergeNeighborsChunks(Chunk* t_chunk);
        void DeallocateChunk(Chunk* t_chunk);
        Chunk* SplitChunkFromFreeList(Chunk* chunk, std::size_t t_chunkSize);
        Chunk* SplitTopChunk(std::size_t t_chunkSize);
        Chunk* MergeTwoChunks(Chunk* t_chunk1, Chunk* t_chunk2);
        void Arena::MergeWithTop(Chunk* t_chunk);
    };
}