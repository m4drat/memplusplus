#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "mpplib/utils/options.hpp"

namespace mpp {
    namespace utils {
        class Statistics
        {
        public:
            struct ArenaStats
            {
                std::size_t totalAllocated;
                std::size_t totalFreed;
                std::size_t biggestAllocation;
                std::size_t smallestAllocation;
                std::size_t fullArenaSize;
                bool bigArena;
            };

            static __attribute__((destructor)) void DumpStats();
            void AddArenaStats(std::unique_ptr<ArenaStats> t_arenaStats);

        private:
            std::vector<std::unique_ptr<ArenaStats>> m_ArenasStats;
        };

        static Statistics s_Stats;
    }
}