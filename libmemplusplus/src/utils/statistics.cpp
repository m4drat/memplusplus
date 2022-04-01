#include "mpplib/utils/statistics.hpp"
#include "mpplib/memory_manager.hpp"

namespace mpp { namespace utils {
    Statistics::~Statistics()
    {
#if MPP_STATS == 1
        if (EnvOptions::Get().GetMppShowStatistics()) {
            DumpStats(std::cerr, false, false, false);
        }
#endif
    }

    std::string Statistics::FormattedSize(std::size_t t_bytes, uint32_t t_decimals)
    {
        if (t_bytes == 0) {
            return "0 bytes";
        }

        std::stringstream ss;

        uint32_t k = 1024;
        std::vector<std::string> sizes{ "Bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
        int32_t i = std::floor(std::log(t_bytes) / std::log(k));
        ss << std::setprecision(t_decimals) << std::fixed << (t_bytes / std::pow(k, i)) << " "
           << sizes.at(i);

        return ss.str();
    }

    std::ostream& Statistics::DumpArenasGeneralStats(std::ostream& t_out)
    {
        uint32_t arenaIdx = 1;
        for (const auto& arenaStats : m_arenasStats) {
            t_out << "  -----------------  Arena: " << arenaIdx << "  -----------------  "
                  << std::endl;
            t_out << "MPP - Total amount of allocated memory inside arena : "
                  << FormattedSize(arenaStats->totalAllocated) << std::endl;
            t_out << "MPP - Total amount of freed memory inside arena     : "
                  << FormattedSize(arenaStats->totalFreed) << std::endl;
            t_out << "MPP - total freed == total allocated                : ";
            if (arenaStats->totalAllocated == arenaStats->totalFreed) {
#if MPP_COLOUR == 1
                t_out << col::GREEN << "true" << col::RESET << std::endl;
#else
                t_out << "true" << std::endl;
#endif
            } else {
#if MPP_COLOUR == 1
                t_out << col::RED << "false" << col::RESET << std::endl;
#else
                t_out << "false" << std::endl;
#endif
            }

            if (arenaStats->biggestAllocation == 0) {
                t_out << "MPP - Biggest allocation size                       : \"No allocations "
                         "have been made yet\""
                      << std::endl;
            } else {
                t_out << "MPP - Biggest allocation size                       : "
                      << FormattedSize(arenaStats->biggestAllocation) << std::endl;
            }
            if (arenaStats->smallestAllocation == std::numeric_limits<std::size_t>::max()) {
                t_out << "MPP - Smallest allocation size                      : \"No allocations "
                         "have been made yet\""
                      << std::endl;
            } else {
                t_out << "MPP - Smallest allocation size                      : "
                      << FormattedSize(arenaStats->smallestAllocation) << std::endl;
            }
            t_out << "MPP - Full size of arena                            : "
                  << FormattedSize(arenaStats->fullArenaSize) << std::endl;
            t_out << "MPP - Arena was allocated for big chunk             : "
                  << (arenaStats->bigArena ? "true" : "false") << std::endl;
            t_out << "MPP - Arena was allocated by GC                     : "
                  << (arenaStats->gcCreatedArena ? "true" : "false") << std::endl;
            t_out << std::endl;
            arenaIdx++;
        }
        return t_out;
    }

    std::ostream& Statistics::DumpGcStats(std::ostream& t_out)
    {
        uint32_t cycleIdx = 1;
        for (const auto& gcStats : m_gcCyclesStats) {
            t_out << "  -----------------  Cycle: " << cycleIdx << "  -----------------  "
                  << std::endl;
            t_out << "GC - Time wasted inside   GC::Collect() : " << gcStats->timeWasted.count()
                  << " ms" << std::endl;
            t_out << "GC - Memory cleaned after GC::Collect() : "
                  << FormattedSize(gcStats->memoryCleaned) << std::endl;
            t_out << "GC - Total size of active objects       : "
                  << FormattedSize(gcStats->activeObjectsTotalSize) << std::endl;
            t_out << std::endl;
            cycleIdx++;
        }
        return t_out;
    }

    std::ostream& Statistics::DumpStats(std::ostream& t_out,
                                        bool t_dumpActiveArenas,
                                        bool t_dumpFreedChunks,
                                        bool t_dumpInUseChunks)
    {
        t_out << "+============= STATISTICS DUMP START =============+" << std::endl;

        t_out << "MPP: MIN_CHUNK_SIZE     : " << MemoryManager::g_MIN_CHUNK_SIZE << " bytes"
              << std::endl;
        t_out << "MPP: CHUNK_HEADER_SIZE  : " << sizeof(Chunk::ChunkHeader) << " bytes"
              << std::endl;
        t_out << "MPP: DEFAULT_ARENA_SIZE : " << FormattedSize(MemoryManager::g_DEFAULT_ARENA_SIZE)
              << std::endl;
        t_out << "MPP: PAGE_SIZE          : " << FormattedSize(MemoryManager::g_PAGE_SIZE)
              << std::endl;

        if (t_dumpActiveArenas == true) {
            t_out << "~~~~~~~~~~~~~~~~ All active arenas ~~~~~~~~~~~~~~~~" << std::endl;
            for (auto* arena : MemoryManager::GetArenaList()) {
                Arena::DumpArena(t_out, arena, t_dumpFreedChunks, t_dumpInUseChunks) << std::endl;
            }
        }

        t_out << "~~~~~~~~~~~~~~~~~~ General stats ~~~~~~~~~~~~~~~~~~" << std::endl;
        DumpArenasGeneralStats(t_out);

        t_out << "~~~~~~~~~~~~~ Garbage Collector stats ~~~~~~~~~~~~~" << std::endl;
        DumpGcStats(t_out);

        t_out << "+============== STATISTICS DUMP END ==============+" << std::endl;
        return t_out;
    }

    void Statistics::AddGcCycleStats(std::unique_ptr<Statistics::GcStats> t_gcCycleStats)
    {
        m_gcCyclesStats.push_back(std::move(t_gcCycleStats));
    }

    void Statistics::AddArenaStats(std::shared_ptr<ArenaStats> t_arenaStats)
    {
        m_arenasStats.push_back(t_arenaStats);
    }

    std::vector<std::unique_ptr<Statistics::GcStats>>& Statistics::GetGcStats()
    {
        return m_gcCyclesStats;
    }

    std::vector<std::shared_ptr<Statistics::ArenaStats>>& Statistics::GetArenaStats()
    {
        return m_arenasStats;
    }

    Statistics& Statistics::GetInstance()
    {
        static Statistics s_stats;
        return s_stats;
    }
}}