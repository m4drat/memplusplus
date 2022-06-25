#pragma once

#include "mpplib/utils/profiler_definitions.hpp"
#include <cstdlib>

namespace mpp { namespace utils {
    /**
     * @brief Class that wraps all environment options.
     */
    class EnvOptions
    {
    private:
        /**
         * @brief true, if environment variable MPP_DUMP_OBJECTS_GRAPH is set.
         */
        bool m_dumpObjectsGraph;

        /**
         * @brief true, if environment variable MPP_SHOW_STATISTICS is set.
         */
        bool m_showStatistics;

        /**
         * @brief Constructor, that gets called before program start, to setup all
         * environment variables.
         */
        void SetOptions();

    public:
        /**
         * @brief Construct a new EnvOptions object
         */
        EnvOptions();

        /**
         * @brief Get the MppDumpObjectsGraph variable.
         * @return true, if variable is set, false - otherwise.
         */
        bool GetMppDumpObjectsGraph() const;

        /**
         * @brief Get the MppShowStatistics variable.
         * @return true, if variable is set, false - otherwise.
         */
        bool GetMppShowStatistics() const;

        /**
         * @brief Get static instance
         * @return EnvOptions& 
         */
        static EnvOptions& Get();
    };
}}