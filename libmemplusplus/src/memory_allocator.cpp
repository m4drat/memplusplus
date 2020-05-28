#include "mpplib/memory_allocator.hpp"
#include <sys/mman.h>

namespace mpp {

    size_t MemoryAllocator::Align(std::size_t size)
    {
        return (size + sizeof(u_int32_t) - 1) & ~(sizeof(u_int32_t) - 1);
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
            size = Align(size);
            rawPtr =
              mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
        }
        return rawPtr;
    };

    void MemoryAllocator::SysDealloc(void* ptr){

    };

}