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

    // std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    // Vertex* v1 = new Vertex((Chunk*)0x1000);
    // Vertex* v2 = new Vertex((Chunk*)0x1100);
    // Vertex* v3 = new Vertex((Chunk*)0x1200);
    // Vertex* v4 = new Vertex((Chunk*)0x1300);
    // Vertex* v5 = new Vertex((Chunk*)0x1400);
    // Vertex* v6 = new Vertex((Chunk*)0x1500);
    // Vertex* v7 = new Vertex((Chunk*)0x1600);
    // Vertex* v8 = new Vertex((Chunk*)0x1700);
    
    // objectsGraph->AddVertex(v3);
    // objectsGraph->AddVertex(v1);
    // objectsGraph->AddVertex(v4);
    // objectsGraph->AddVertex(v2);
    // objectsGraph->AddVertex(v5);

    // objectsGraph->AddEdge(v3, v1);
    // objectsGraph->AddEdge(v3, v2);
    // objectsGraph->AddEdge(v3, v4);
    // objectsGraph->AddEdge(v4, v2);
    // objectsGraph->AddEdge(v4, v8);

    // objectsGraph->AddEdge(v5, v6);
    // objectsGraph->AddEdge(v6, v7);
    // objectsGraph->AddEdge(v7, v5);

    // objectsGraph->GenerateGraphvizLayout(std::cout);

    struct Node {
        uint32_t data;
        SharedGcPtr<Node> prev;
        SharedGcPtr<Node> next;

        Node(uint32_t t_data, SharedGcPtr<Node> t_p, SharedGcPtr<Node> t_n)
            : data{t_data}, prev{t_p}, next{t_n}
        {
        }
    };

    SharedGcPtr<Node> n1 = MakeSharedGcPtr<Node>(1, nullptr, nullptr);
    SharedGcPtr<Node> n2 = MakeSharedGcPtr<Node>(2, nullptr, nullptr);
    SharedGcPtr<Node> n3 = MakeSharedGcPtr<Node>(3, nullptr, nullptr);
    SharedGcPtr<Node> n4 = MakeSharedGcPtr<Node>(4, nullptr, nullptr);

    n1->prev = nullptr;
    n1->next = n2;

    n2->prev = n1;
    n2->next = n3;
    
    n3->prev = n2;
    n3->next = n4;
    
    n4->prev = n3;
    n4->next = nullptr;

    struct TreeNode {
        uint32_t data;
        SharedGcPtr<TreeNode> left;
        SharedGcPtr<TreeNode> right;
        SharedGcPtr<TreeNode> up;

        TreeNode(uint32_t t_data, SharedGcPtr<TreeNode> t_left, SharedGcPtr<TreeNode> t_right, SharedGcPtr<TreeNode> t_up)
            : data{t_data}, left{t_left}, right{t_right}, up{t_up}
        {
        }
    };

    SharedGcPtr<TreeNode> root = MakeSharedGcPtr<TreeNode>(0, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode1 = MakeSharedGcPtr<TreeNode>(1, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode2 = MakeSharedGcPtr<TreeNode>(2, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode3 = MakeSharedGcPtr<TreeNode>(3, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode4 = MakeSharedGcPtr<TreeNode>(4, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode5 = MakeSharedGcPtr<TreeNode>(5, nullptr, nullptr, nullptr);

    root->up = nullptr;
    root->left = treeNode1;
    root->right = treeNode2;

    treeNode1->up = root;
    treeNode1->left = nullptr;
    treeNode1->right = nullptr;

    treeNode2->up = root;
    treeNode2->left = treeNode3;
    treeNode2->right = treeNode4;

    treeNode3->up = treeNode2;
    treeNode3->left = nullptr;
    treeNode3->right = nullptr;

    treeNode4->up = treeNode2;
    treeNode4->left = treeNode5;
    treeNode4->right = nullptr;

    treeNode5->up = treeNode4;
    treeNode5->left = nullptr;
    treeNode5->right = nullptr;

    GC::GetInstance().Collect();

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