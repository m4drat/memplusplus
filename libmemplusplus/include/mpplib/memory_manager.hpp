#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include <vector>
#include <iostream>

namespace mpp {

    class MemoryManager
    {
    private:
    public:
        static std::vector<Arena*> s_ArenaList;

        static std::ostream& DumpStats(std::ostream& t_out);

        static const std::size_t g_MIN_CHUNK_SIZE = 32;
        static const std::size_t g_CHUNK_HEADER_SIZE = sizeof(Chunk::ChunkHeader_t);
        static const std::size_t g_DEFAULT_ARENA_SIZE = 32 * (1 << 20);
        static const std::size_t g_PAGE_SIZE = 4096;
    };
}