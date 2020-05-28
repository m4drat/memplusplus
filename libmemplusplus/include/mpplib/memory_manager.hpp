#pragma once

#include "mpplib/arena.hpp"
#include <vector>

namespace mpp {

    class MemoryManager
    {
    private:
    public:
        static std::vector<Arena*> s_ArenaList;

        static const std::size_t g_MIN_CHUNK_SIZE = 16;
        static const std::size_t g_CHUNK_HEADER_SIZE = 4;
        static const std::size_t g_DEFAULT_ARENA_SIZE = 16 * (1 << 20);
        static const std::size_t g_PAGE_SIZE = 4096;        
    };
}