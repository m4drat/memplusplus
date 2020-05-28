#pragma once

#include "mpplib/memory_manager.hpp"
#include <cmath>

namespace mpp {

    class MemoryAllocator : public MemoryManager
    {
    private:
        static inline size_t Align(std::size_t t_size, int t_allignment);
        static void* SysAlloc(std::size_t t_size);
        static void SysDealloc(void* t_ptr);
        static Arena* CreateArena(std::size_t t_arenaSize);
        static void* AllocateBigChunk(std::size_t t_userDataSize);
        static Arena* GetSuitableArena(std::size_t t_realSize);

    public:
        static void* Allocate(std::size_t t_userDataSize);
        static void Deallocate(void* t_chunkPtr);
    };
}