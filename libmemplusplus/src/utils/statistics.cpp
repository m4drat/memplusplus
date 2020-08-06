#include "mpplib/utils/statistics.hpp"
#include "mpplib/memory_manager.hpp"

namespace mpp {
    namespace utils {
        std::ostream& Statistics::DumpArenasGeneralStats(std::ostream& t_out)
        {
            return t_out;
        }

        std::ostream& Statistics::DumpGcStats(std::ostream& t_out)
        {
            return t_out;
        }

        std::ostream& Statistics::DumpStats(std::ostream& t_out)
        {
            t_out << "+=================================================+" << std::endl;

            t_out << "MPP: MIN_CHUNK_SIZE     : " << MemoryManager::g_MIN_CHUNK_SIZE << std::endl;
            t_out << "MPP: CHUNK_HEADER_SIZE  : " << sizeof(Chunk::ChunkHeader) << std::endl;
            t_out << "MPP: DEFAULT_ARENA_SIZE : " << MemoryManager::g_DEFAULT_ARENA_SIZE
                  << std::endl;
            t_out << "MPP: PAGE_SIZE          : " << MemoryManager::g_PAGE_SIZE << std::endl;

            t_out << "~~~~~~~~~~~~~~~~ All active arenas ~~~~~~~~~~~~~~~~" << std::endl;
            for (auto* arena : MemoryManager::GetArenaList()) {
                Arena::DumpArena(t_out, arena) << std::endl;
            }

            t_out << "~~~~~~~~~~~~~~~~~~ General stats ~~~~~~~~~~~~~~~~~~" << std::endl;
            Statistics::Get().DumpArenasGeneralStats(t_out) << std::endl;

            t_out << "~~~~~~~~~~~~~ Garbage Collector stats ~~~~~~~~~~~~~" << std::endl;
            Statistics::Get().DumpGcStats(t_out) << std::endl;

            t_out << "+=================================================+" << std::endl;
            return t_out;
        }

        void Statistics::DumpStats()
        {
            if (Options::GetMppShowStatistics()) {
                DumpStats(std::cerr);
            }
        }

        void Statistics::AddArenaStats(std::unique_ptr<ArenaStats> t_arenaStats)
        {
            m_ArenasStats.push_back(std::move(t_arenaStats));
        }

        std::unique_ptr<Statistics::GcStats>& Statistics::GetGcStats()
        {
            return m_GcStats;
        }

        std::vector<std::unique_ptr<Statistics::ArenaStats>>& Statistics::GetArenaStats()
        {
            return m_ArenasStats;
        }

        Statistics& Statistics::Get()
        {
            static Statistics s_Stats;
            return s_Stats;
        }
    }
}