#pragma once

#include "mpplib/memory_manager.hpp"
#include "mpplib/gcptr.hpp"

#include <vector>

namespace mpp {
    class GC : public MemoryManager
    {
    protected:
        static std::vector<GcPtr*> s_activeGcPtrs;
        static std::size_t s_garbageSize;
        static std::size_t s_dataSize;

    public:
        static bool Collect();
        static std::vector<GcPtr*>& GetGcPtrs() { return s_activeGcPtrs; }
   };
}