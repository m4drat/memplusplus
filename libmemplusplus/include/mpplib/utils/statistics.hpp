#pragma once

#include <iostream>
#include <vector>

#include "mpplib/utils/options.hpp"

namespace mpp {
    namespace utils {
        class Statistics
        {
        public:
            typedef struct ArenaStats
            {
                std::size_t totalAllocated;
                std::size_t totalFreed;
                std::size_t biggestAllocation;
                std::size_t smallestAllocation;
                std::size_t fullArenaSize;
                bool bigArena;
            } ArenaStats_t;

            static __attribute__((destructor)) void DumpStats();

        private:
            std::vector<ArenaStats_t*> m_ArenasStats;
        };
    }
}