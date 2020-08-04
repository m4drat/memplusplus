#include "mpplib/utils/options.hpp"

namespace mpp {
    namespace utils {
        bool Options::s_MPP_DUMP_OBJECTS_GRAPH;
        bool Options::s_MPP_SHOW_STATISTICS;

        void Options::SetOptions()
        {
            char* dump_graph = std::getenv("MPP_DUMP_OBJECTS_GRAPH");
            char* show_stats = std::getenv("MPP_SHOW_STATISTICS");

            if (dump_graph != nullptr && dump_graph[0] == '1')
            {
                s_MPP_DUMP_OBJECTS_GRAPH = true;
            } else {
                s_MPP_DUMP_OBJECTS_GRAPH = false;
            }

            if (show_stats != nullptr && show_stats[0] == '1')
            {
                s_MPP_SHOW_STATISTICS = true;
            } else {
                s_MPP_SHOW_STATISTICS = false;
            }
        }

        bool Options::GetMppDumpObjectsGraph()
        {
            return s_MPP_DUMP_OBJECTS_GRAPH;
        }

        bool Options::GetMppShowStatistics()
        {
            return s_MPP_SHOW_STATISTICS;
        }
    }
}