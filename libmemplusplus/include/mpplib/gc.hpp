#pragma once

#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/memory_allocator.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"

#include <cstring>
#include <vector>
#include <memory>

namespace mpp {
    class GC : public MemoryManager
    {
    protected:
        static std::vector<GcPtr*> s_activeGcPtrs;
        static std::size_t s_garbageSize;
        static std::size_t s_dataSize;

    public:
        static bool Collect();
        static void AddInfoToObjectsGraph(GcPtr* t_gcPtr, std::unique_ptr<GcGraph>& t_objectsGraph);
        static std::vector<GcPtr*>& GetGcPtrs() { return s_activeGcPtrs; }
        // static std::string GetObjectsGraphDot();
   };
}