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
#include <set>
#include <unordered_set>
#include <vector>

namespace mpp {
    /**
     * @brief GarbageCollector class.
     */
    class GC
    {
    private:
        static constexpr float m_newAllocExtendThreshold = 0.25f;
        static constexpr float m_newAllocExpandFactor = 1.25f;
        /**
         * @brief All active GcPtr's.
         *
         * All GcPtr's that are currently used in the program are added to this list, to keep track
         * of them.
         */
        std::unordered_set<GcPtr*> m_activeGcPtrs;

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
         * @brief 
         * 
         */
        Chunk* GetChunkInUseByPtr(Arena* t_arena, void* t_ptr);

        /**
         * @brief Get reference to unordered set of currently active GcPtr's
         * @return std::unordered_set<GcPtr*>& of currently used GcPtr's
         */
        std::unordered_set<GcPtr*>& GetGcPtrs()
        {
            return m_activeGcPtrs;
        }

        /**
         * @brief Transforms an unordered set of GcPtr's to a set of GcPtr's
         * and returns it as a copy.
         * @return std::set<GcPtr*> of currently used GcPtr's
         */
        std::set<GcPtr*> GetOrderedGcPtrs()
        {
            return std::set(m_activeGcPtrs.begin(), m_activeGcPtrs.end());
        }

        /**
         * @brief Adds new gcptr to the list of active gcptr's
         * @param t_ptr pointer to GcPtr to add
         */
        void AddGcPtr(GcPtr* t_ptr)
        {
            m_activeGcPtrs.insert(t_ptr);
        }

        /**
         * @brief Get the Instance of GC object
         * @return GC& Global Garbage Collector
         */
        static GC& GetInstance()
        {
            static GC gcInstance;
            return gcInstance;
        }
    };
}