#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

using namespace mpp;
class UserData
{
private:
    int m_data{ 0 };
    char data[2048];

public:
    UserData(int val)
        : m_data{ val }
    {}

    ~UserData()
    {}

    int GetData()
    {
        return m_data;
    }
};

void logic()
{
    using namespace mpp;
    using namespace std::literals::chrono_literals;

    const std::size_t allocaSize = 112;
    const std::size_t realChunkSize = MemoryAllocator::Align(
      allocaSize + sizeof(Chunk::ChunkHeader), MemoryAllocator::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = 9;

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
    MemoryAllocator::Deallocate(ptrs[8]);

    // simulate invalid free
    // MemoryAllocator::Deallocate((void*)0xdeadbeef);

    // Simulate doublefree
    // MemoryAllocator::Deallocate(ptrs.at(7));

    // MemoryManager::VisHeapLayout(std::cout)
    MemoryAllocator::GetArenaList()[0]->freedChunks.GenerateGraphvizLayout(std::cout, "Treap")
      << std::endl;
}

int main()
{
    logic();
    return 0;
}