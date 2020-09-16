#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>

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

    // SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    // SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1338);
    // SharedGcPtr<UserData> p2 = MakeSharedGcPtr<UserData>(1339);
    // SharedGcPtr<UserData> p3 = MakeSharedGcPtr<UserData>(1340);
    // SharedGcPtr<UserData> p4 = MakeSharedGcPtr<UserData>(1341);
    // SharedGcPtr<UserData> p5 = MakeSharedGcPtr<UserData>(1342);

    // SharedGcPtr<unsigned char[]> array = MakeSharedGcPtr<unsigned char[]>(2048);

    // void* p0 = MemoryAllocator::Allocate(1024);
    // void* p1 = MemoryAllocator::Allocate(1024);
    // void* p2 = MemoryAllocator::Allocate(1024);
    // void* p3 = MemoryAllocator::Allocate(1024);
    // void* p4 = MemoryAllocator::Allocate(15);

    // p2 = nullptr;
    // p4 = nullptr;
    // p5 = nullptr;

    // std::vector<void*> ptrs;
    // for (uint32_t i = 0; i < 17000; ++i) {
    //     ptrs.push_back(MemoryAllocator::Allocate(2056));
    // }

    // for (uint32_t i = 0; i < 17000; i++) {
    //     MemoryAllocator::Deallocate(ptrs.at(i)); // rand() % ptrs.size()
    // }

    const std::size_t allocaSize = 65520;
    const std::size_t realChunkSize = MemoryAllocator::Align(allocaSize + sizeof(Chunk::ChunkHeader), MemoryAllocator::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = MemoryAllocator::g_DEFAULT_ARENA_SIZE / realChunkSize;

    std::vector<void*> ptrs;
    for (uint32_t i = 0; i < allocationsCount; ++i) {
        ptrs.push_back(MemoryAllocator::Allocate(allocaSize));
    }

    for (uint32_t i = 0; i < allocationsCount / 2; i++) {
        MemoryAllocator::Deallocate(ptrs.at(rand() % ptrs.size())); // rand() % ptrs.size()
    }

    // MemoryAllocator::Deallocate(ptrs.at(1)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(3)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(5)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(7)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(9)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(11)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(13)); // rand() % ptrs.size()
    // MemoryManager::VisHeapLayout(std::cout);
    MemoryAllocator::GetArenaList()[0]->freedChunks.GenerateGraphvizLayout(std::cout);
    // void* newArenaChunk = MemoryAllocator::Allocate(allocaSize);
    // MemoryAllocator::Deallocate(newArenaChunk);

    // std::for_each(ptrs.begin(), ptrs.end(), [](void* ptr){ MemoryAllocator::Deallocate(ptr); });

    // GC::GetInstance().Collect();

    // utils::Statistics::GetInstance().DumpStats(std::cout, true, false, false) << std::endl;
    // void* p0 = MemoryAllocator::Allocate(1 << 31);
}

int main()
{
    logic();
    return 0;
}