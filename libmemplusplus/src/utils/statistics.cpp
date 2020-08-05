#include "mpplib/utils/statistics.hpp"
#include "mpplib/memory_manager.hpp"

namespace mpp {
    namespace utils {
        std::ostream& Statistics::DumpStats(std::ostream& t_out)
        {
            t_out << "------======================================------" << std::endl;

            t_out << "MPP: MIN_CHUNK_SIZE     : " << MemoryManager::g_MIN_CHUNK_SIZE << std::endl;
            t_out << "MPP: CHUNK_HEADER_SIZE  : " << sizeof(Chunk::ChunkHeader) << std::endl;
            t_out << "MPP: DEFAULT_ARENA_SIZE : " << MemoryManager::g_DEFAULT_ARENA_SIZE
                  << std::endl;
            t_out << "MPP: PAGE_SIZE          : " << MemoryManager::g_PAGE_SIZE << std::endl;

            for (auto* arena : MemoryManager::GetArenaList()) {
                Arena::DumpArena(t_out, arena) << std::endl;
            }

            t_out << "------======================================------" << std::endl;
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
    }
}