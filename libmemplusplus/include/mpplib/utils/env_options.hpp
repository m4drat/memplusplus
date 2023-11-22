#pragma once

#include "mpplib/utils/log.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#include <cstdlib>

namespace mpp { namespace utils {
    enum class ObjectsGraphDumpType
    {
        SIMPLE,
        ADVANCED,
        DISABLED
    };

    /**
     * @brief Class that wraps all environment options.
     */
    class EnvOptions final
    {
    private:
        /**
         * @brief If environment variable MPP_DUMP_OBJECTS_GRAPH is set to 1 - dumps simple objects
         * graph. If set to 2 - dumps advanced objects graph.
         */
        ObjectsGraphDumpType m_dumpObjectsGraph;

        /**
         * @brief true, if environment variable MPP_SHOW_STATISTICS is set.
         */
        bool m_showStatistics;

        /**
         * @brief Environment variable MPP_LOG_LEVEL.
         */
        logging::LogLevel m_logLevel;

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
        ObjectsGraphDumpType GetMppDumpObjectsGraph() const;

        /**
         * @brief Get the MppShowStatistics variable.
         * @return true, if variable is set, false - otherwise.
         */
        bool GetMppShowStatistics() const;

        /**
         * @brief Get the MppLogLevel variable.
         * @return LogLevel
         */
        logging::LogLevel GetMppLogLevel() const;

        /**
         * @brief Get static instance
         * @return EnvOptions&
         */
        static EnvOptions& Get();
    };
}}