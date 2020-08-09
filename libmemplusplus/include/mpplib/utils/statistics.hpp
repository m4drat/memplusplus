#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <cmath>

#include "mpplib/utils/options.hpp"

namespace mpp {
    namespace utils {
        /**
         * @brief Class to easily manage all kind of statistics
         */
        class Statistics
        {
        public:
            /**
             * @brief Structure that holds all possible kinds of arena statistics
             */
            struct ArenaStats
            {
                /**
                 * @brief Amount of total allocated memory (could be bigger than arena size, 
                 * if memory was reused)
                 */
                std::size_t totalAllocated;
                
                /**
                 * @brief total amount of freed memory (if all allocations was deallocated, 
                 * should be equal to totalAllocated)
                 */
                std::size_t totalFreed;

                /**
                 * @brief Biggest allocation that was performed in this arena
                 */
                std::size_t biggestAllocation;

                /**
                 * @brief Smallest allocation that was performed in this arena
                 */
                std::size_t smallestAllocation;

                /**
                 * @brief Arena full size 
                 */
                std::size_t fullArenaSize;

                /**
                 * @brief Arena was allocated for big chunk
                 */
                bool bigArena;

                /**
                 * @brief Arena was created by GC
                 */
                bool gcCreatedArena;
            };

            /**
             * @brief Structure to hold all stats about GC::Collect()
             */
            struct GcStats
            {
                /**
                 * @brief Time wasted inside GC::Collect()
                 */
                std::chrono::duration<double, std::milli> timeWasted;

                /**
                 * @brief Amount of memory cleaned by GC
                 */
                std::size_t memoryCleaned;

                /**
                 * @brief total size of objects, that
                 * remained active
                 */
                std::size_t activeObjectsTotalSize;
            };

            /**
             * @brief Destroy the Statistics object
             * and call DumpStats (if env MPP_SHOW_STATISTICS=1) after program termination
             */
            ~Statistics();

            /**
             * @brief Get size in bytes converted to appropriate unit (mb, kb, ...)
             * @param t_bytes size in bytes
             * @param decimals number of signs after comma
             * @return std::string size in a specific unit
             */
            static std::string FormattedSize(std::size_t t_bytes, uint32_t t_decimals = 3);

            /**
             * @brief Dump all arenas general stats
             * @param t_out - std::ostream& to write to
             * @return std::ostream&
             */
            std::ostream& DumpArenasGeneralStats(std::ostream& t_out);

            /**
             * @brief Dump GC stats
             * @param t_out - std::ostream& to write to
             * @return std::ostream&
             */
            std::ostream& DumpGcStats(std::ostream& t_out);

            /**
             * @brief Dump information about arenas.
             * @param t_out output sream to write to.
             * @param t_dumpActiveArenas dump active arenas.
             * @param t_DumpFreedChunks dump freed chunks.
             * @param t_DumpInUseChunks dump in use chunks.
             * @return std::ostream& stream reference
             */
            std::ostream& DumpStats(std::ostream& t_out, bool t_dumpActiveArenas, bool t_DumpFreedChunks, bool t_DumpInUseChunks);

            /**
             * @brief Add gc stats to vector of all gc statistics
             * @param t_arenaStats std::unique_ptr<GcStats>
             */
            void AddGcCycleStats(std::unique_ptr<GcStats> t_gcCycleStats);

            /**
             * @brief Add arena stats to vector of all arena statistics
             * @param t_arenaStats std::unique_ptr<ArenaStats>
             */
            void AddArenaStats(std::shared_ptr<ArenaStats> t_arenaStats);

            /**
             * @brief Get Gc stats
             * @return std::unique_ptr<GcStats>& 
             */
            std::vector<std::unique_ptr<Statistics::GcStats>>& GetGcStats();
            
            /**
             * @brief Get the vector of arena stats
             * @return std::vector<std::unique_ptr<ArenaStats>>& 
             */
            std::vector<std::shared_ptr<ArenaStats>>& GetArenaStats();

            /**
             * @brief Return static instance of statistics object
             * @return Statistics 
             */
            static Statistics& GetInstance();

        private:
            /**
             * @brief vector of all arenas statistics 
             */
            std::vector<std::shared_ptr<ArenaStats>> m_ArenasStats;
            
            /**
             * @brief Garbage Collector stats 
             */
            std::vector<std::unique_ptr<GcStats>> m_GcCyclesStats;
        };
    }
}