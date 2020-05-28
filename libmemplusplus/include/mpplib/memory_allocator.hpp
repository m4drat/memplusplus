#pragma once

#include "mpplib/memory_manager.hpp"
#include <cmath>

namespace mpp {

    class MemoryAllocator : public MemoryManager
    {
    private:
        static void* SysAlloc(std::size_t size);
        static void SysDealloc(void* ptr);
        static inline size_t Align(std::size_t size, int n);
        static void CreateArena();
        static void* AllocateBigChunk(std::size_t chunkSize);

    public:
        static void* Allocate(std::size_t chunkSize);
        static void* Deallocate(void* chunkPtr);

        static const std::size_t g_MIN_CHUNK_SIZE = 16;
        static const std::size_t g_CHUNK_HEADER_SIZE = 4;
        static const std::size_t g_DEFAULT_ARENA_SIZE = 16 * (1 << 20);
    };

}