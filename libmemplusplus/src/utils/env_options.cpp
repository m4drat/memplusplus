#include "mpplib/utils/env_options.hpp"

namespace mpp { namespace utils {
    EnvOptions::EnvOptions()
    {
        SetOptions();
    }

    void EnvOptions::SetOptions()
    {
        char* dump_graph = std::getenv("MPP_DUMP_OBJECTS_GRAPH");
        char* show_stats = std::getenv("MPP_SHOW_STATISTICS");

        if (dump_graph && dump_graph[0] == '1') {
            m_dumpObjectsGraph = ObjectsGraphDumpType::SIMPLE;
        } else if (dump_graph && dump_graph[0] == '2') {
            m_dumpObjectsGraph = ObjectsGraphDumpType::ADVANCED;
        } else {
            m_dumpObjectsGraph = ObjectsGraphDumpType::DISABLED;
        }

        if (show_stats && show_stats[0] == '1') {
            m_showStatistics = true;
        } else {
            m_showStatistics = false;
        }
    }

    ObjectsGraphDumpType EnvOptions::GetMppDumpObjectsGraph() const
    {
        return m_dumpObjectsGraph;
    }

    bool EnvOptions::GetMppShowStatistics() const
    {
        return m_showStatistics;
    }

    EnvOptions& EnvOptions::Get()
    {
        static EnvOptions s_instance;
        return s_instance;
    }
}}