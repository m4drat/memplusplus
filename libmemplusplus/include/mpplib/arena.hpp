#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include <set>
#include <cstddef>
#include <vector>

namespace mpp {
    class Arena final
    {
        /**
         * What we should use to save information about freed/in-use blocks?
         * Should we save all active blocks + all freed blocks, or we just need
         * to save one list? Requrements for data structure:
         *     1. Fast Find max element - O(logN)
         *     2. Fast insert/delete - O(logN)
         *     3. Fast exact search - O(logN)
         *     4. Find bigger or equal element - O(logN)
         *      ===> Treap
         */
    public:
        ChunkTreap freedChunks;

        std::set<Chunk*> chunksInUse;
        std::size_t size{ 0 };
        Chunk* topChunk{ nullptr };
        void* begin{ nullptr };
        void* end{ nullptr };

        Arena(std::size_t t_size, void* t_begin) //, void* t_end)
        {
            size = t_size;
            topChunk = Chunk::ConstructChunk(t_begin, 0, t_size, 1, 1);
            begin = t_begin;
            end = reinterpret_cast<void*>((std::size_t)t_begin + t_size);
        };

        ~Arena()
        {
            chunksInUse.clear();
            // MemoryAllocator::SysDealloc(begin, (std::size_t)end - (std::size_t)begin);
            // TODO: correctly destroy ChunkTreap
        }

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
        Chunk* MergeTwoSequnceChunks(Chunk* t_chunk1, Chunk* t_chunk2);
        Chunk* MergeWithTop(Chunk* t_chunk);

        // TODO: Find the chunk that the current pointer belongs to
        Chunk* GetInUseChunkByPtr(void* t_ptr);

        static std::ostream& DumpArena(std::ostream& t_out, Arena* t_arena);
    };
}