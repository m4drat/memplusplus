#pragma once

#include <stdlib.h>

namespace mpp {
    namespace utils {
        /**
         * @brief Class that wraps all environment options.
         */
        class Options
        {
        private:
            /**
             * @brief true, if environment variable MPP_DUMP_OBJECTS_GRAPH is set.
             */
            static bool s_MPP_DUMP_OBJECTS_GRAPH;

            /**
             * @brief true, if environment variable MPP_SHOW_STATISTICS is set.
             */
            static bool s_MPP_SHOW_STATISTICS;

            /**
             * @brief Constructor, that gets called before program start, to setup all
             * environment variables.
             */
            static __attribute__((constructor)) void SetOptions();

        public:
            /**
             * @brief Get the MppDumpObjectsGraph variable.
             * @return true, if variable is set, false - otherwise.
             */
            static bool GetMppDumpObjectsGraph();

            /**
             * @brief Get the MppShowStatistics variable.
             * @return true, if variable is set, false - otherwise.
             */
            static bool GetMppShowStatistics();
        };
    }
}