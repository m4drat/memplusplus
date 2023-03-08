#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/utils/profiler_definitions.hpp"
#include "mpplib/utils/utils.hpp"

#if MPP_STATS == 1
#include "mpplib/utils/statistics.hpp"
#endif

#include <cstddef>
#include <iomanip>
#include <limits>
#include <memory>
#include <set>
#include <vector>

namespace mpp {
    /**
     * @brief Controls area of memory.
     */
    class Arena final
    {
    private:
        //! @brief Currently used space in arena.
        std::size_t m_currentlyAllocatedSpace{ 0 };

        /**
         * @brief All chunks in use. Invalid before call to @sa ConstructChunksInUse.
         * @warning call to ConstructChunksInUse by default doesn't rebuild this set if it's already
         * built. So it might be outdated.
         */
        std::set<Chunk*> m_chunksInUse;

#if MPP_STATS == 1
        /**
         * @brief Arena statistics.
         */
        std::shared_ptr<utils::Statistics::ArenaStats> m_arenaStats;
#endif

        /**
         * @brief Treap, to handle freed chunks.
         *
         * Treap is used, because we need fast search (logN), fast insert/remove (logN).
         */
        ChunkTreap m_freedChunks;

        /**
         * @brief Full arena size.
         */
        std::size_t m_size{ 0 };

        /**
         * @brief Pointer to top chunk, a.k.a wilderness.
         */
        Chunk* m_topChunk{ nullptr };

        /**
         * @brief Pointer to the first usable address in allocated using mmap block.
         */
        std::byte* m_Begin{ nullptr };

        /**
         * @brief Pointer to the first address right after arena.begin + arena.size.
         */
        std::byte* m_End{ nullptr };

    public:
        //! @brief Iterator for chunks inside arena.
        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Chunk;
            using pointer = Chunk*;
            using reference = Chunk&;

            explicit Iterator(pointer ptr)
                : m_ptr(ptr)
            {
            }

            reference operator*() const
            {
                return *m_ptr;
            }

            pointer operator->()
            {
                return m_ptr;
            }

            Iterator& operator++()
            {
                m_ptr = reinterpret_cast<Chunk*>((std::byte*)m_ptr + m_ptr->GetSize());
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const Iterator& t_first, const Iterator& t_second)
            {
                return t_first.m_ptr == t_second.m_ptr;
            };

            friend bool operator!=(const Iterator& t_first, const Iterator& t_second)
            {
                return t_first.m_ptr != t_second.m_ptr;
            };

        private:
            pointer m_ptr;
        };

#if MPP_STATS == 1
        //! @brief Stats for arena.
        std::shared_ptr<utils::Statistics::ArenaStats> GetArenaStats()
        {
            return m_arenaStats;
        }
#endif

        //! @brief Returns const reference to treap with all freed chunks.
        const ChunkTreap& GetFreedChunks() const
        {
            return m_freedChunks;
        }

        //! @brief Returns arena size
        std::size_t GetSize() const
        {
            return m_size;
        }

        //! @brief Returns reference to a pointer to top chunk.
        Chunk*& TopChunk()
        {
            return m_topChunk;
        }

        //! @brief Returns pointer to a beginning of the arena.
        std::byte* BeginPtr() const
        {
            return m_Begin;
        }

        //! @brief Returns pointer to an end of the arena.
        std::byte* EndPtr() const
        {
            return m_End;
        }

        //! @brief Returns iterator to the first chunk in arena.
        Iterator begin() const
        {
            return Iterator(reinterpret_cast<Chunk*>(m_Begin));
        }

        //! @brief Returns iterator to the memory address right after the last chunk in arena.
        Iterator end() const
        {
            return Iterator(reinterpret_cast<Chunk*>(m_End));
        }

        /**
         * @brief Default arena constructor.
         * @param t_size arena size.
         * @param t_begin allocated arena begin.
         */
        Arena(std::size_t t_size, std::byte* t_begin);

        /**
         * @brief Arena destructor.
         *
         * Deletes chunksInUse, freedChunks, and munmaps allocated memory page.
         */
        ~Arena();

        /**
         * @brief Constructs set of chunks, that are in use.
         * @warning This function traverses all chunks in arena, and is very slow O(n).
         * @warning By default this method doesn't rebuild chunksInUse if it was built earlier.
         * So it might be outdated.
         * @return std::set<Chunk*>& set of chunks
         */
        const std::set<Chunk*>& ConstructChunksInUse(bool t_rebuild = false);

        /**
         * @brief Clears m_chunksInUse set.
         */
        void ClearChunksInUse();

        /**
         * @brief Returns amount of freed memory inside chunk treap
         * @return std::size_t amount of memory
         */
        std::size_t FreeMemoryInsideChunkTreap() const;

        /**
         * @brief Get currently used space.
         * @return used by current arena space.
         */
        std::size_t GetUsedSpace() const;

        /**
         * @brief Updates arena used space.
         *
         * Complexity (average): O(logN).
         * @param t_newSize new used space value
         */
        void SetUsedSpace(std::size_t t_newSize);

        /**
         * @brief Find max size chunk in freed chunks.
         *
         * Complexity (average): O(logN).
         * @return Chunk of max size.
         */
        Chunk* MaxSizeChunk();

        /**
         * @brief Find max size chunk in freed chunks.
         *
         * Complexity (average): O(logN).
         * @return Chunk of max size.
         */
        Chunk* GetFirstGreaterOrEqualToChunk(std::size_t t_desiredChunkSize) const;

        /**
         * @brief Constructs chunk from freed chunk, earlier found in chunk treap
         * using GetFirstGreaterOrEqualThanChunk.
         *
         * If size of found chunk is bigger, than requested, split it into
         * two chunks. Adds allocated chunk to chunksInUse.
         * Complexity (average): O(logN).
         * @sa SplitChunkFromFreeList.
         * @param t_chunk found in chunk treap earlier using
         * GetFirstGreaterOrEqualThanChunk.
         * @param t_chunkSize requested chunk size.
         * @return chunk from the freedChunks, splitting it if needed.
         */
        Chunk* AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);

        /**
         * @brief Construct chunk from top chunk.
         *
         * Simply cuts part of the top chunk.
         * Complexity: O(1).
         * @sa SplitTopChunk.
         * @param t_chunkSize desired chunk size.
         * @return chunk allocated from top chunk.
         */
        Chunk* AllocateFromTopChunk(std::size_t t_chunkSize);

        /**
         * @brief Merge consequently placed freed chunks.
         *
         * Check left neighbor/right neighbor, and merge, if the are freed.
         * Complexity: O(1).
         * @param t_chunk chunk to merge with neighbors.
         * @return start of merged chunk.
         */
        Chunk* MergeNeighborsChunks(Chunk* t_chunk);

        /**
         * @brief Deallocates chunk.
         *
         * Deletes it from chunksInUse, and adds to freedChunks.
         * Also merge with neighbors if needed.
         * Complexity: O(logN).
         * @param t_chunk chunk to deallocate.
         */
        void DeallocateChunk(Chunk* t_chunk);

        /**
         * @brief Reuse first fit chunk from ChunkTreap.
         *
         * Complexity: O(logN).
         * @param t_chunk found chunk from ChunkTreap.
         * @param t_chunkSize requested chunk size.
         * @return splitted chunk.
         */
        Chunk* SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);

        /**
         * @brief Splits top chunk, and updates topChunk ptr.
         *
         * Complexity: O(1).
         * @param t_chunkSize requested chunk size.
         * @return splitted chunk from top.
         */
        Chunk* SplitTopChunk(std::size_t t_chunkSize);

        /**
         * @brief Merge two sequence chunks.
         *
         * Complexity: O(1).
         * @warning this method updates only resulting size of merged chunks!
         * @param t_chunk1 first chunk to merge.
         * @param t_chunk2 second chunk to merge with.
         * @return start of merged chunk (t_chunk1)
         */
        Chunk* MergeTwoSequenceChunks(Chunk* t_chunk1, Chunk* t_chunk2);

        /**
         * @brief Merge freed chunk with top. Updates corresponding pointers.
         *
         * Complexity: O(1).
         * @param t_chunk rightmost chunk to merge with top.
         * @return new top chunk ptr
         */
        Chunk* MergeWithTop(Chunk* t_chunk);

#if MPP_STATS == 1
        /**
         * @brief Dump arena statistics in human-readable format.
         * @param t_out file stream, to write to. (std::cout / std::ofstream)
         * @param t_arena arena, that is going to be dumped.
         * @param t_dumpFreedChunks dump all freed chunks
         * @param t_dumpInUseChunks dump all in use chunks
         * @return std::ostream, that earlier was passed as t_out
         */
        static std::ostream& DumpArena(std::ostream& t_out,
                                       std::unique_ptr<Arena>& t_arena,
                                       bool t_dumpFreedChunks,
                                       bool t_dumpInUseChunks);
#endif
    };
}