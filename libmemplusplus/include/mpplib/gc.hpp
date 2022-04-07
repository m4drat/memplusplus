#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#if MPP_STATS == 1
#include "mpplib/utils/statistics.hpp"
#include "mpplib/utils/timer.hpp"
#endif

#if MPP_DEBUG == 1
#include "mpplib/utils/env_options.hpp"
#include <fstream>
#endif

#include <cstring>
#include <memory>
#include <vector>

namespace mpp {
    /**
     * @brief GarbageCollector class.
     */
    class GC
    {
    protected:
        /**
         * @brief All active GcPtr's.
         *
         * All GcPtr's that are currently used in program adds to this list, to keep track
         * of them.
         */
        std::vector<GcPtr*> s_activeGcPtrs;

        /**
         * @brief size of garbage, cleaned last time.
         */
        std::size_t s_garbageSize{ 0 };

        /**
         * @brief Required size of memory block, to save all user data in.
         */
        std::size_t s_dataSize{ 0 };

#if MPP_STATS == 1
        /**
         * @brief Used to keep track of garbage collector stats
         */
        std::unique_ptr<utils::Statistics::GcStats> m_gcStats;
#endif

        /**
         * @brief Current cycle to dump objects graph
         */
        static uint32_t m_currentCycle;

    public:
        /**
         * @brief Construct a new GC object
         */
        GC();

        /**
         * @brief Collect garbage.
         *
         * This method will construct graph of all in use chunks.
         * Then it will create Heuristics object to relayout data in most efficient way.
         * After that, it will move all data to newly created arena, updating
         * corresponding gcptr's. And in the end it will destroy unused arenas.
         * @return true if everything is good, false - otherwise
         */
        bool Collect();

        /**
         * @brief Get reference to vector of currently active GcPtr's
         * @return std::vector<GcPtr*>& of currently used GcPtr's
         */
        std::vector<GcPtr*>& GetGcPtrs()
        {
            return s_activeGcPtrs;
        }
    };
}