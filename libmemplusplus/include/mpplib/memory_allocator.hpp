#pragma once

#include "mpplib/memory_manager.hpp"
#include <cstdint>
#include <cmath>

namespace mpp {
    class MemoryAllocator : public MemoryManager
    {
    private:
        static inline std::size_t Align(std::size_t t_size, int32_t t_allignment);
        static void* SysAlloc(std::size_t t_size);
        static void SysDealloc(const std::pair<void*, std::size_t>& page);
        static Arena* CreateArena(std::size_t t_arenaSize);
        static void* AllocateBigChunk(std::size_t t_userDataSize);
        static Arena* GetSuitableArena(std::size_t t_realSize);

    public:
        static void* Allocate(std::size_t t_userDataSize);
        static void Deallocate(void* t_chunkPtr);

        template <class T, class... Args>
        static T* Allocate(Args&&... args);
        template <class T>
        static void Deallocate(T* t_chunkPtr);
    };
}