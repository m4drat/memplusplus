#include <iostream>

#include "mpplib/memory_allocator.hpp"

int main(int argc, char* argv[])
{
    using namespace mpp;
    // std::cout << "================================================================================================" << std::endl;
    // void* block1 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // void* block2 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // void* block3 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // void* block4 = MemoryAllocator::Allocate(50);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;

    // MemoryAllocator::Deallocate(block3);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // MemoryAllocator::Deallocate(block1);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // MemoryAllocator::Deallocate(block2);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;
    // MemoryAllocator::Deallocate(block4);
    // MemoryManager::DumpStats(std::cout);
    // std::cout << "================================================================================================" << std::endl;

    void* block5 = MemoryAllocator::Allocate(50331648);
    MemoryManager::DumpStats(std::cout);
    std::cout << "================================================================================================" << std::endl;
    // FIXME
    MemoryAllocator::Deallocate(block5);
    MemoryManager::DumpStats(std::cout);

    return 0;
}