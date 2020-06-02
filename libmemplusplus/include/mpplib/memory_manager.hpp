#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include <iostream>
#include <vector>

namespace mpp {

    class MemoryManager
    {
    protected:
        // TODO: refactor to worrk with std::unique_ptr
        static std::vector<Arena*> s_ArenaList;

    public:
        static std::ostream& DumpStats(std::ostream& t_out);
        static const std::vector<Arena*>& GetArenaList()
        {
            return s_ArenaList;
        }

        // TODO: Find the arena that the current pointer belongs to
        static Arena* GetArenaByPtr(void* t_ptr);

        static bool ResetAllocatorState();

        static const std::size_t g_MIN_CHUNK_SIZE = 32;
        static const std::size_t g_CHUNK_HEADER_SIZE = sizeof(Chunk::ChunkHeader_t);
        static const std::size_t g_DEFAULT_ARENA_SIZE = 32 * (1 << 20);
        static const std::size_t g_PAGE_SIZE = 4096;
    };
}