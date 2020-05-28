#pragma once

#include "mpplib/arena.hpp"
#include <vector>

namespace mpp {

    class MemoryManager
    {
    private:
        /* data */
    public:
        static std::vector<Arena*> s_ArenaList; 
    };
}