#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

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
                 * @brief Chunk headers total size
                 */
                std::size_t chunksMetadataSize;
                
                /**
                 * @brief Full amount of memory, that was used for
                 * metadata (chunk treap, active chunks, ...)
                 */
                std::size_t fullMetadataSize;
                
                /**
                 * @brief Arena was allocated for big chunk
                 */
                bool bigArena;
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
            };

            /**
             * @brief Dump all arenas general stats
             * @param t_out - std::ostream& to write to
             * @return std::ostream&
             */
            static std::ostream& DumpArenasGeneralStats(std::ostream& t_out);

            /**
             * @brief Dump GC stats
             * @param t_out - std::ostream& to write to
             * @return std::ostream&
             */
            static std::ostream& DumpGcStats(std::ostream& t_out);

            /**
             * @brief Dump information about arenas.
             * @param t_out output sream to write to.
             * @return std::ostream& stream reference
             */
            static std::ostream& DumpStats(std::ostream& t_out);

            /**
             * @brief destructor function, that will print all
             * stats (if env MPP_SHOW_STATISTICS=1) after program termination
             */
            static __attribute__((destructor)) void DumpStats();
            
            /**
             * @brief Add arena stats to vector of all arena statistics
             * @param t_arenaStats std::unique_ptr<ArenaStats>
             */
            void AddArenaStats(std::unique_ptr<ArenaStats> t_arenaStats);

            /**
             * @brief Get Gc stats
             * @return std::unique_ptr<GcStats>& 
             */
            std::unique_ptr<GcStats>& GetGcStats();
            
            /**
             * @brief Get the vector of arena stats
             * @return std::vector<std::unique_ptr<ArenaStats>>& 
             */
            std::vector<std::unique_ptr<ArenaStats>>& GetArenaStats();

            /**
             * @brief Return static instance of statistics object
             * @return Statistics 
             */
            static Statistics& Get();

        private:
            /**
             * @brief vector of all arenas statistics 
             */
            std::vector<std::unique_ptr<ArenaStats>> m_ArenasStats;
            
            /**
             * @brief Garbage Collector stats 
             */
            std::unique_ptr<GcStats> m_GcStats;
        };
    }
}