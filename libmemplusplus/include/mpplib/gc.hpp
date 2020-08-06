#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/memory_allocator.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#if MPP_DEBUG == 1
#include "mpplib/utils/options.hpp"
#include <fstream>
#endif

#include <cstring>
#include <memory>
#include <vector>

namespace mpp {
    /**
     * @brief GarbageCollector class.
     */
    class GC : public MemoryManager
    {
    protected:
        /**
         * @brief All active GcPtr's.
         *
         * All GcPtr's that are currently used in program adds to this list, to keep track
         * of them.
         */
        static std::vector<GcPtr*> s_activeGcPtrs;
        /**
         * @brief size of garbage, cleaned last time.
         */
        static std::size_t s_garbageSize;
        /**
         * @brief Required size of memory block, to save all user data in.
         */
        static std::size_t s_dataSize;

    public:
        /**
         * @brief Collect garbage.
         *
         * This method will construct graph of all inuse chunks.
         * Then it will create Heuristics object to relayout data in most efficient way.
         * After that, it will move all data to newly created arena, updating
         * corresponding gcptr's. And in the end it will destroy unused arenas.
         * @return true if everything is good, false - otherwise
         */
        static bool Collect();

        /**
         * @brief Get reference to vector of currently active GcPtr's
         * @return std::vector<GcPtr*>& of currently used GcPtr's
         */
        static std::vector<GcPtr*>& GetGcPtrs()
        {
            return s_activeGcPtrs;
        }

        // static std::string GetObjectsGraphDot();
    };
}