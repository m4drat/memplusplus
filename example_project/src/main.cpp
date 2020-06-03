#include <iostream>

#include "mpplib/memory_allocator.hpp"

int main(int argc, char* argv[])
{
    using namespace mpp;
    // std::cout <<
    // "================================================================================================"
    // << std::endl; void* block1 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; void* block2 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; void* block3 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; void* block4 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl;

    // MemoryAllocator::Deallocate(block3);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; MemoryAllocator::Deallocate(block1);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; MemoryAllocator::Deallocate(block2);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl; MemoryAllocator::Deallocate(block4);
    // MemoryManager::DumpStats(std::cout);
    // std::cout <<
    // "================================================================================================"
    // << std::endl;

    // void* block5 = MemoryAllocator::Allocate(50331648);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "============================================================="
    //              "==================================="
    //           << std::endl;
    // MemoryAllocator::Deallocate(block5);
    // MemoryManager::DumpStats(std::cout);

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    ((ch1 != nullptr && ch2 != nullptr));
    (ch1 < ch2);

    (currentArena->chunksInUse.size() == 2);
    for (Chunk* chunk : currentArena->chunksInUse)
        (chunk->GetSize() == 160);
    (Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
    (Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->topChunk);

    MemoryManager::VisHeapLayout(std::cout) << std::endl;

    MemoryAllocator::Deallocate(ch1);
    MemoryManager::VisHeapLayout(std::cout) << std::endl;

    MemoryAllocator::Deallocate(ch2);
    MemoryManager::VisHeapLayout(std::cout) << std::endl;

    return 0;
}