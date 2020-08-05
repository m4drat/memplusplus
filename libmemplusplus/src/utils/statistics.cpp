#include "mpplib/utils/statistics.hpp"

namespace mpp {
    namespace utils {
        void Statistics::DumpStats()
        {
            if (Options::GetMppShowStatistics())
            {
                std::cerr << "Arenas statistics: " << std::endl;
            }
        }

        void Statistics::AddArenaStats(std::unique_ptr<ArenaStats> t_arenaStats)
        {
            m_ArenasStats.push_back(std::move(t_arenaStats));
        }
    }
}