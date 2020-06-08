#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/utils/utils.hpp"

#include <set>
#include <cstddef>
#include <vector>

namespace mpp {
    class Arena final
    {
    private:
        /**
         * Currently used space in arena.
         */
        std::size_t CurrentlyAllocatedSpace{ 0 };

    public:
        /**
         * Treap, to handle freed chunks. Treap is used, because we need fast 
         * search (logN), fast insert/remove (logN).
         */
        ChunkTreap freedChunks;

        /**
         * All currently used chunks inside arena.
         */
        std::set<Chunk*> chunksInUse;

        /**
         * Full arena size.
         */
        std::size_t size{ 0 };
        
        /**
         * Pointer to top chunk, a.k.a wilderness.
         */
        Chunk* topChunk{ nullptr };
        /**
         * Pointer to first usable address in allocated using mmap block.
         */ 
        void* begin{ nullptr };
        /**
         * Pointer to first address right after arena.begin + arena.size.
         */
        void* end{ nullptr };

        /**
         * Default arena constructor. 
         * @param t_size arena size.
         * @param t_begin allocated arena begin.
         */
        Arena(std::size_t t_size, void* t_begin);

        /**
         * Arena destructor. Deletes chunksInUse, freedChunks, and munmaps allocated 
         * memoty page. 
         */
        ~Arena();

        /**
         * Get currently used space.
         * @return used by current arena space.
         */
        std::size_t GetUsedSpace();
        
        /**
         * Update arenas used space.
         * Complexity (average): O(logN).
         * @param t_newSize new used space value
         */
        void SetUsedSpace(std::size_t t_newSize);  

        /**
         * Find max size chunk in freed chunks.
         * Complexity (average): O(logN).
         * @return Chunk of max size.
         */
        Chunk* MaxSizeChunk();
        
        /**
         * Find max size chunk in freed chunks.
         * Complexity (average): O(logN).
         * @return Chunk of max size.
         */
        Chunk* GetFirstGreaterOrEqualThanChunk(std::size_t t_desiredChunkSize);
        
        /**
         * Constructs chunk from freed chunk, earlier found in chunk treap 
         * using GetFirstGreaterOrEqualThanChunk.
         * If size of found chunk is bigger, than requested, split it into 
         * two chunks. Add allocated chunk to chunksInUse.
         * Complexity (average): O(logN).
         * @sa SplitChunkFromFreeList.
         * @param t_chunk found in chunk treap earlier using GetFirstGreaterOrEqualThanChunk.
         * @param t_chunkSize requested chunk size.
         * @return chunk from the freedChunks, splitting it if needed.
         */
        Chunk* AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);
        
        /**
         * Construct chunk from top chunk. Simply cut part of top chunk.
         * Complexity: O(1).
         * @sa SplitTopChunk.
         * @param t_chunkSize desired chunk size. 
         * @return chunk allocated from top chunk.
         */
        Chunk* AllocateFromTopChunk(std::size_t t_chunkSize);
        
        /**
         * Merge consequently placed freed chunks. Check left neighbor/right neighbor, 
         * and merge, if the are freed.
         * Complexity: O(1).
         * @param t_chunk chunk to merge with neighbors.
         * @return start of merged chunk.
         */
        Chunk* MergeNeighborsChunks(Chunk* t_chunk);
        
        /**
         * Deallocates chunk. Deletes it from chunksInUse, and adds to freedChunks.
         * Also merge with neighbors if needed.
         * Complexity: O(logN).
         * @param t_chunk chunk to deallocate.
         */
        void DeallocateChunk(Chunk* t_chunk);
        
        /**
         * Reuse first fit chunk from ChunkTreap. 
         * Complexity: O(logN).
         * @param t_chunk found chunk from ChunkTreap.
         * @param t_chunkSize requested chunk size.
         * @return splitted chunk.
         */
        Chunk* SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);
        
        /**
         * Splits top chunk, and updates topChunk ptr.
         * Complexity: O(1).
         * @param t_chunkSize requested chunk size.
         * @return splitted chunk from top.
         */
        Chunk* SplitTopChunk(std::size_t t_chunkSize);
        
        /**
         * Simply merge two sequence chunks. 
         * Complexity: O(1).
         * @warning this method updates only resulting size of merged chunks!
         * @param t_chunk1 first chunk to merge.
         * @param t_chunk2 second chunk to merge with.
         * @return start of merged chunk (t_chunk1)
         */
        Chunk* MergeTwoSequnceChunks(Chunk* t_chunk1, Chunk* t_chunk2);
        
        /**
         * Merge freed chunk with top. Updates corresponding pointers.
         * Complexity: O(1).
         * @param t_chunk rightmost chunk to merge with top.
         * @return new top chunk ptr
         */
        Chunk* MergeWithTop(Chunk* t_chunk);
        
        /**
         * Find a chunk by the pointer pointing to this chunk.
         * Complexity: O(logN).
         * @warning t_ptr should be in chunksInUse! Using this function you can find only inUse chunk.
         * @param t_ptr pointer, that points into some active chunk (everywhere inside active chunk). 
         * @return found chunk or nullptr
         */
        Chunk* GetInUseChunkByPtr(void* t_ptr);

        /**
         * Dump arena statistics in human-readable format.
         * @param t_out file stream, to write to. (std::cout / std::ofstream)
         * @param t_arena arena, that is going to be dumped.
         * @return std::ostream, that earlier was passed as t_out
         */
        static std::ostream& DumpArena(std::ostream& t_out, Arena* t_arena);
    };
}