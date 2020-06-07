#include <iostream>

#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/chunk.hpp"
#include <memory>

using namespace mpp;

class UserData
{
private:
    int m_data{ 0 };
public:
    UserData(int val) : m_data{ val }
    {
        std::cout << "Created!\n";
    }

    ~UserData()
    {
        std::cout << "Deleted!\n";
    }
};

// SharedGcPtr<UserData> foo()
// {
//     SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1337);
//     return p1;
// }

int main(int argc, char* argv[])
{
    // SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    // SharedGcPtr<UserData> p1(p0);
    // SharedGcPtr<UserData> p2(p0);
    // SharedGcPtr<UserData> p3(p0);
    // SharedGcPtr<UserData> p4(p0);
    // SharedGcPtr<UserData> p5(p0);

    // MemoryManager::DumpStats(std::cout);
    // MemoryManager::VisHeapLayout(std::cout);

    // GC::Collect();

    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    Vertex* v1 = new Vertex((Chunk*)0x1000);
    Chunk* v1ch = (Chunk*)0x1000;
    Vertex* v2 = new Vertex((Chunk*)0x1100);
    Chunk* v2ch = (Chunk*)0x1100;
    Vertex* v3 = new Vertex((Chunk*)0x1200);
    Chunk* v3ch = (Chunk*)0x1200;
    Vertex* v4 = new Vertex((Chunk*)0x1300);
    Chunk* v4ch = (Chunk*)0x1300;

    objectsGraph->AddVertex(v3);
    objectsGraph->AddVertex(v1);
    objectsGraph->AddVertex(v4);
    objectsGraph->AddVertex(v2);

    objectsGraph->AddEdge(v3, v1);
    objectsGraph->AddEdge(v1, v3);
    objectsGraph->AddEdge(v1, v1);
    objectsGraph->AddEdge(v1, v2);
    objectsGraph->AddEdge(v1, v3);
    objectsGraph->AddEdge(v1, v1);

    std::cout << objectsGraph->GenerateGraphvizLayout() << std::endl;

    return 0;
}