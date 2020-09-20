#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>

#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/chunk.hpp"
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
    const std::size_t realChunkSize = MemoryAllocator::Align(allocaSize + sizeof(Chunk::ChunkHeader), MemoryAllocator::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = 9;

    std::vector<void*> ptrs;
    for (uint32_t i = 0; i < allocationsCount; ++i) {
        ptrs.push_back(MemoryAllocator::Allocate(allocaSize));
    }

    MemoryAllocator::Deallocate(ptrs.at(1));
    MemoryAllocator::Deallocate(ptrs.at(3));
    MemoryAllocator::Deallocate(ptrs.at(5));
    MemoryAllocator::Deallocate(ptrs.at(7));
    
    // simulate invalid free
    MemoryAllocator::Deallocate((void*)0xdeadbeef);

    // Simulate doublefree
    // MemoryAllocator::Deallocate(ptrs.at(7));

    // MemoryManager::VisHeapLayout(std::cout);
    // MemoryAllocator::GetArenaList()[0]->freedChunks.GenerateGraphvizLayout(std::cout);
}

int main()
{
    logic();
    return 0;
}