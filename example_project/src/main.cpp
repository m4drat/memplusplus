#include <iostream>

#include "mpplib/memory_allocator.hpp"

int main(int argc, char* argv[])
{
    using namespace mpp;

    void* block1 = MemoryAllocator::Allocate(50);
    void* block2 = MemoryAllocator::Allocate(50);
    void* block3 = MemoryAllocator::Allocate(50);
    void* block4 = MemoryAllocator::Allocate(50);
    std::cout << "[1]" << block1 << std::endl;
    std::cout << "[2]" << block2 << std::endl;
    std::cout << "[3]" << block3 << std::endl;
    std::cout << "[4]" << block4 << std::endl;

    MemoryAllocator::Deallocate(block3);
    MemoryAllocator::Deallocate(block1);    
    MemoryAllocator::Deallocate(block2);
    MemoryAllocator::Deallocate(block4);

    MemoryManager::DumpStats(std::cout);

    void* block5 = MemoryAllocator::Allocate(50331648);
        
    // FIXME
    MemoryAllocator::Deallocate(block5);

    return 0;
}