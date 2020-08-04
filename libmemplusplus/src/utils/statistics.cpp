#include "mpplib/utils/statistics.hpp"

namespace mpp {
    namespace utils {
        static Statistics s_Stats;

        void Statistics::DumpStats()
        {
            if (Options::GetMppShowStatistics())
            {
                std::cerr << "Arenas statistics: " << std::endl;
                // for (uint32_t i = 0; i < )
            }
        }
    }
}