#include "mpplib/memory_allocator.hpp"
#include <sys/mman.h>

namespace mpp {

    size_t MemoryAllocator::Align(std::size_t size, int n)
    {
        return size + (n - (n % 4096));
    };

    void* MemoryAllocator::SysAlloc(std::size_t size)
    {
        void* rawPtr{ nullptr };
        if (size < g_DEFAULT_ARENA_SIZE) {
            rawPtr = mmap(NULL,
                          g_DEFAULT_ARENA_SIZE,
                          PROT_READ | PROT_WRITE,
                          MAP_PRIVATE,
                          0,
                          0);
        } else {
            // size = Align(size);
            rawPtr =
              mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
        }
        return rawPtr;
    };

    void* MemoryAllocator::AllocateBigChunk(std::size_t chunkSize)
    {
        size_t arenaSize = Align(chunkSize, 4096);
        void* arenaSpace = SysAlloc(arenaSize);
        Arena* arena = new Arena(arenaSize, arenaSpace, arenaSpace + arenaSize);
        s_ArenaList.push_back(arena);
        /*
        TODO
        */
        return nullptr;
    }

    void* MemoryAllocator::Allocate(std::size_t chunkSize)
    {
        if (s_ArenaList.empty()) {
            if (chunkSize > g_DEFAULT_ARENA_SIZE) {
                return AllocateBigChunk(chunkSize);
            } else {
                void* arenaSpace = SysAlloc(g_DEFAULT_ARENA_SIZE);
                Arena* arena = new Arena(g_DEFAULT_ARENA_SIZE,
                                         arenaSpace,
                                         arenaSpace + g_DEFAULT_ARENA_SIZE);
                s_ArenaList.push_back(arena);
            }
            for (auto arena : s_ArenaList) {
                if (arena->freeSpace > chunkSize) {
                    /*
                    
                    */
                };
            }
        };
    };

    void MemoryAllocator::SysDealloc(void* ptr){

    };

}