#include <catch2/catch_all.hpp>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mpplib/chunk.hpp"
#include "mpplib/memory_allocator.hpp"

TEST_CASE("DoubleFree - detect 1")
{
    using namespace mpp;

    std::vector<void*> ptrs;
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(256));
    ptrs.push_back(MemoryAllocator::Allocate(512));
    ptrs.push_back(MemoryAllocator::Allocate(16));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(256));
    ptrs.push_back(MemoryAllocator::Allocate(512));
    ptrs.push_back(MemoryAllocator::Allocate(1024));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(2048));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));

    MemoryAllocator::Deallocate(ptrs[0]);
    MemoryAllocator::Deallocate(ptrs[2]);
    MemoryAllocator::Deallocate(ptrs[4]);
    MemoryAllocator::Deallocate(ptrs[6]);
    MemoryAllocator::Deallocate(ptrs[8]);
    MemoryAllocator::Deallocate(ptrs[7]);
    MemoryAllocator::Deallocate(ptrs[10]);
    MemoryAllocator::Deallocate(ptrs[12]);

    // DoubleFree
    CHECK(CHECK_ABORT(MemoryAllocator::Deallocate, (void*)ptrs[8]));
}

TEST_CASE("Invalid free test")
{
    using namespace mpp;

    std::vector<void*> ptrs;
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(256));
    ptrs.push_back(MemoryAllocator::Allocate(512));
    ptrs.push_back(MemoryAllocator::Allocate(16));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(256));
    ptrs.push_back(MemoryAllocator::Allocate(512));
    ptrs.push_back(MemoryAllocator::Allocate(1024));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(2048));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));
    ptrs.push_back(MemoryAllocator::Allocate(128));

    MemoryAllocator::Deallocate(ptrs[0]);
    MemoryAllocator::Deallocate(ptrs[2]);
    MemoryAllocator::Deallocate(ptrs[4]);
    MemoryAllocator::Deallocate(ptrs[6]);
    MemoryAllocator::Deallocate(ptrs[8]);
    MemoryAllocator::Deallocate(ptrs[7]);
    MemoryAllocator::Deallocate(ptrs[10]);

    // InvalidFree
    CHECK(CHECK_ABORT(MemoryAllocator::Deallocate<void*>, (void*)0xdeadbeef));
}
