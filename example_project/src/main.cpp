#include <iostream>

#include "mpplib/memory_allocator.hpp"

int main(int argc, char* argv[])
{
    using namespace mpp;

    void* block1 = MemoryAllocator::Allocate(50);

    return 0;
}