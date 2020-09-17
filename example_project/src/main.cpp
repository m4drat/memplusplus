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

    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    Vertex* v1 = new Vertex((Chunk*)0x1000);
    Vertex* v2 = new Vertex((Chunk*)0x1100);
    Vertex* v3 = new Vertex((Chunk*)0x1200);
    Vertex* v4 = new Vertex((Chunk*)0x1300);
    Vertex* v5 = new Vertex((Chunk*)0x1400);
    Vertex* v6 = new Vertex((Chunk*)0x1500);
    Vertex* v7 = new Vertex((Chunk*)0x1600);
    Vertex* v8 = new Vertex((Chunk*)0x1700);
    
    objectsGraph->AddVertex(v3);
    objectsGraph->AddVertex(v1);
    objectsGraph->AddVertex(v4);
    objectsGraph->AddVertex(v2);
    objectsGraph->AddVertex(v5);

    objectsGraph->AddEdge(v3, v1);
    objectsGraph->AddEdge(v3, v2);
    objectsGraph->AddEdge(v3, v4);
    objectsGraph->AddEdge(v4, v2);
    objectsGraph->AddEdge(v4, v8);

    objectsGraph->AddEdge(v5, v6);
    objectsGraph->AddEdge(v6, v7);
    objectsGraph->AddEdge(v7, v5);

    objectsGraph->GenerateGraphvizLayout(std::cout);

    // struct Obj2 {
    //     SharedGcPtr<UserData> data1;    
    //     SharedGcPtr<UserData> data2;

    //     Obj() {
    //         data1 = MakeSharedGcPtr<UserData>(1337);
    //     }
    // };

    // struct Obj1 {
    //     SharedGcPtr<UserData> data1;    
    //     SharedGcPtr<UserData> data2;    
    //     SharedGcPtr<UserData> data3;

    //     Obj() {
    //         data1 = MakeSharedGcPtr<UserData>(1337);
    //         data2 = MakeSharedGcPtr<UserData>(1337);
    //         data3 = MakeSharedGcPtr<UserData>(1337);
    //     }
    // };

    // SharedGcPtr<Obj> p0 = MakeSharedGcPtr<Obj>();
    // SharedGcPtr<Obj> p1 = MakeSharedGcPtr<Obj>();

    // GC::GetInstance().Collect();

    // const std::size_t allocaSize = 65520;
    // const std::size_t realChunkSize = MemoryAllocator::Align(allocaSize + sizeof(Chunk::ChunkHeader), MemoryAllocator::g_MIN_CHUNK_SIZE);
    // const std::size_t allocationsCount = 13;

    // std::vector<void*> ptrs;
    // for (uint32_t i = 0; i < allocationsCount; ++i) {
        // ptrs.push_back(MemoryAllocator::Allocate(allocaSize));
    // }

    // for (uint32_t i = 0; i < allocationsCount / 2; i++) {
        // MemoryAllocator::Deallocate(ptrs.at(rand() % ptrs.size())); // rand() % ptrs.size()
    // }

    // MemoryAllocator::Deallocate(ptrs.at(1)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(3)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(5)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(7)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(9)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(11)); // rand() % ptrs.size()
    // MemoryAllocator::Deallocate(ptrs.at(13)); // rand() % ptrs.size()
    // MemoryManager::VisHeapLayout(std::cout);
    // MemoryAllocator::GetArenaList()[0]->freedChunks.GenerateGraphvizLayout(std::cout);
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