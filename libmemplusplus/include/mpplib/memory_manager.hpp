#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"

#include <iostream>
#include <vector>

namespace mpp {
    class Arena;
    /**
     * @brief Base class for Memory Allocator.
     */
    class MemoryManager
    {
    protected:
        // TODO: refactor to work with std::unique_ptr
        /**
         * @brief All existing arenas.
         */
        static std::vector<Arena*> s_ArenaList;

    public:
        /**
         * @brief Dump information about arenas.
         * @param t_out output sream to write to.
         * @return std::ostream& stream reference
         */
        static std::ostream& DumpStats(std::ostream& t_out);
        /**
         * @brief Visualizes heap layout.
         * @param t_out output sream to write to.
         * @return std::ostream& stream reference
         */
        static std::ostream& VisHeapLayout(std::ostream& t_out);

        /**
         * @brief Get reference to vector of arenas.
         * @return const std::vector<Arena*>& to arenas
         */
        static const std::vector<Arena*>& GetArenaList()
        {
            return s_ArenaList;
        }

        /**
         * @brief Check, that specified pointer points in any arena.
         * @param t_ptr pointer to some location.
         * @return Arena* if pointer points into arena, nullptr otherwise
         */
        static Arena* GetArenaByPtr(void* t_ptr);
        /**
         * @brief Check, that specified pointer points in any active chunk.
         * @param t_chunk pointer to some location.
         * @return Chunk* if pointer points into some chunk, nullptr otherwise
         */
        static Chunk* GetInUseChunkByPtr(void* t_chunk);

        // TODO:
        /**
         * @brief Resets allocator state by destroying all arenas.
         * @return true if everything is fine, false otherwise
         */
        static bool ResetAllocatorState();

        /**
         * @brief Minimum allowed chunk size. Chunk size less than that will be extended.
         */
        static const std::size_t g_MIN_CHUNK_SIZE = 32;
        /**
         * @brief Size of chunk header.
         */
        static const std::size_t g_CHUNK_HEADER_SIZE = sizeof(Chunk::ChunkHeader_t);
        /**
         * @brief Default arena size.
         */
        static const std::size_t g_DEFAULT_ARENA_SIZE = 32 * (1 << 20);
        /**
         * @brief Page size for mmap request.
         */
        static const std::size_t g_PAGE_SIZE = 4096;
    };
}