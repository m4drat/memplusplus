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
            for (const auto& gcStats : m_GcCyclesStats) {
                t_out << "MPP - Time wasted inside GC::Collect(): " << gcStats->timeWasted.count() << " ms" << std::endl;
            }
            return t_out;
        }

        std::ostream& Statistics::DumpStats(std::ostream& t_out, bool t_dumpActiveArenas)
        {
            t_out << "+=================================================+" << std::endl;

            t_out << "MPP: MIN_CHUNK_SIZE     : " << MemoryManager::g_MIN_CHUNK_SIZE << std::endl;
            t_out << "MPP: CHUNK_HEADER_SIZE  : " << sizeof(Chunk::ChunkHeader) << std::endl;
            t_out << "MPP: DEFAULT_ARENA_SIZE : " << MemoryManager::g_DEFAULT_ARENA_SIZE
                  << std::endl;
            t_out << "MPP: PAGE_SIZE          : " << MemoryManager::g_PAGE_SIZE << std::endl;

            if (t_dumpActiveArenas == true) {
                t_out << "~~~~~~~~~~~~~~~~ All active arenas ~~~~~~~~~~~~~~~~" << std::endl;
                for (auto* arena : MemoryManager::GetArenaList()) {
                    Arena::DumpArena(t_out, arena) << std::endl;
                }
            }

            t_out << "~~~~~~~~~~~~~~~~~~ General stats ~~~~~~~~~~~~~~~~~~" << std::endl;
            DumpArenasGeneralStats(t_out) << std::endl;

            t_out << "~~~~~~~~~~~~~ Garbage Collector stats ~~~~~~~~~~~~~" << std::endl;
            DumpGcStats(t_out) << std::endl;

            t_out << "+=================================================+" << std::endl;
            return t_out;
        }

        void Statistics::DumpStats()
        {
            if (Options::GetMppShowStatistics()) {
                Statistics::GetInstance().DumpStats(std::cerr, false);
            }
        }

        void Statistics::AddGcCycleStats(std::unique_ptr<Statistics::GcStats> t_gcCycleStats)
        {
            m_GcCyclesStats.push_back(std::move(t_gcCycleStats));
        }

        void Statistics::AddArenaStats(std::unique_ptr<ArenaStats> t_arenaStats)
        {
            m_ArenasStats.push_back(std::move(t_arenaStats));
        }

        std::vector<std::unique_ptr<Statistics::GcStats>>& Statistics::GetGcStats()
        {
            return m_GcCyclesStats;
        }

        std::vector<std::unique_ptr<Statistics::ArenaStats>>& Statistics::GetArenaStats()
        {
            return m_ArenasStats;
        }

        Statistics& Statistics::GetInstance()
        {
            static Statistics s_Stats;
            return s_Stats;
        }
    }
}