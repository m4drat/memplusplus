#pragma once

#include <stdlib.h>

namespace mpp {
    namespace utils {
        class Options
        {
        private:
            static bool s_MPP_DUMP_OBJECTS_GRAPH;
            static bool s_MPP_SHOW_STATISTICS;
            static __attribute__((constructor)) void SetOptions();

        public:
            static bool GetMppDumpObjectsGraph();
            static bool GetMppShowStatistics();
        };
    }
}