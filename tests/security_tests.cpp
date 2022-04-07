#include <catch2/catch_all.hpp>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"

TEST_CASE("DoubleFree - detect 1")
{
    using namespace mpp;

    std::vector<void*> ptrs;
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(256));
    ptrs.push_back(MemoryManager::Allocate(512));
    ptrs.push_back(MemoryManager::Allocate(16));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(256));
    ptrs.push_back(MemoryManager::Allocate(512));
    ptrs.push_back(MemoryManager::Allocate(1024));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(2048));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));

    MemoryManager::Deallocate(ptrs[0]);
    MemoryManager::Deallocate(ptrs[2]);
    MemoryManager::Deallocate(ptrs[4]);
    MemoryManager::Deallocate(ptrs[6]);
    MemoryManager::Deallocate(ptrs[8]);
    MemoryManager::Deallocate(ptrs[7]);
    MemoryManager::Deallocate(ptrs[10]);
    MemoryManager::Deallocate(ptrs[12]);

    // DoubleFree
    CHECK(CHECK_ABORT(MemoryManager::Deallocate, (void*)ptrs[8]));
}

TEST_CASE("Invalid free test")
{
    using namespace mpp;

    std::vector<void*> ptrs;
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(256));
    ptrs.push_back(MemoryManager::Allocate(512));
    ptrs.push_back(MemoryManager::Allocate(16));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(256));
    ptrs.push_back(MemoryManager::Allocate(512));
    ptrs.push_back(MemoryManager::Allocate(1024));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(2048));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));
    ptrs.push_back(MemoryManager::Allocate(128));

    MemoryManager::Deallocate(ptrs[0]);
    MemoryManager::Deallocate(ptrs[2]);
    MemoryManager::Deallocate(ptrs[4]);
    MemoryManager::Deallocate(ptrs[6]);
    MemoryManager::Deallocate(ptrs[8]);
    MemoryManager::Deallocate(ptrs[7]);
    MemoryManager::Deallocate(ptrs[10]);

    // InvalidFree
    CHECK(CHECK_ABORT(MemoryManager::Deallocate<void*>, (void*)0xdeadbeef));
}
