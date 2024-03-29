#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include <cstddef>
#include <memory>
#include <sstream>

TEST(GcGraphTest, AddObjectInfo_Issue88)
{
    using namespace mpp;

    mpp::g_memoryManager = std::make_unique<mpp::MemoryManager>();

    class Vertex
    {
    private:
        SharedGcPtr<Vertex> m_gc;
        uint64_t m_data;

    public:
        explicit Vertex(uint64_t t_data)
            : m_data(t_data)
        {
        }

        Vertex()
            : m_data(0x13371337deadbeef)
        {
        }

        void AddPointer(const SharedGcPtr<Vertex>& t_ptr)
        {
            m_gc = t_ptr;
        }

        SharedGcPtr<Vertex>& GetInternalPointer()
        {
            return m_gc;
        }

        uint64_t& GetData()
        {
            return m_data;
        }
    };

    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);

    mpp::SharedGcPtr<Vertex> ptr1 = mpp::MakeShared<Vertex>(0x1337);
    EXPECT_TRUE(ptr1->GetData() == 0x1337);

    ptr1->AddPointer(ptr1);
    objectsGraph->AddObjectInfo(&ptr1->GetInternalPointer());
    objectsGraph->AddObjectInfo(&ptr1);
    EXPECT_TRUE(objectsGraph->GetVerticesCount() == 2);
    EXPECT_TRUE(objectsGraph->GetAdjList().size() == 2);
    EXPECT_TRUE((*objectsGraph->GetAdjList().begin())->GetPointingVertices().size() == 2);
    EXPECT_TRUE((*objectsGraph->GetAdjList().begin())->GetPointingToGcPtrs().size() == 2);
}

TEST(GcGraphTest, UndirectedDFS)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    auto* v1 = new Vertex((std::byte*)0x1000, true);
    auto* v2 = new Vertex((std::byte*)0x1100, true);
    auto* v3 = new Vertex((std::byte*)0x1200, false);
    auto* v4 = new Vertex((std::byte*)0x1300, true);
    auto* v5 = new Vertex((std::byte*)0x1400, false);

    // First weakly-connected component: { v1, v2, v3 }
    objectsGraph->AddEdge(v1, v2);
    objectsGraph->AddEdge(v2, v3);

    // Second weakly-connected component: { v4, v5 }
    objectsGraph->AddEdge(v4, v5);
    objectsGraph->AddEdge(v5, v4);

    ASSERT_TRUE(objectsGraph->GetVerticesCount() == 5);

    auto visited1 = objectsGraph->UndirectedDFS(v1);
    ASSERT_TRUE(visited1->GetAdjList().size() == 3);
    ASSERT_TRUE(visited1->GetRoots().size() == 1);
    ASSERT_TRUE(visited1->GetRoots().contains(v3));

    auto visited2 = objectsGraph->UndirectedDFS(v2);
    ASSERT_TRUE(visited2->GetAdjList().size() == 3);
    ASSERT_TRUE(visited2->GetRoots().size() == 1);
    ASSERT_TRUE(visited2->GetRoots().contains(v3));

    auto visited3 = objectsGraph->UndirectedDFS(v3);
    ASSERT_TRUE(visited3->GetAdjList().size() == 3);
    ASSERT_TRUE(visited3->GetRoots().size() == 1);
    ASSERT_TRUE(visited3->GetRoots().contains(v3));

    for (auto* vtx : { v1, v2, v3 }) {
        ASSERT_TRUE(visited1->GetAdjList().contains(vtx));
        ASSERT_TRUE(visited2->GetAdjList().contains(vtx));
        ASSERT_TRUE(visited3->GetAdjList().contains(vtx));
    }

    auto visited4 = objectsGraph->UndirectedDFS(v4);
    ASSERT_TRUE(visited4->GetAdjList().size() == 2);
    ASSERT_TRUE(visited4->GetRoots().size() == 1);
    ASSERT_TRUE(visited4->GetRoots().contains(v5));

    auto visited5 = objectsGraph->UndirectedDFS(v5);
    ASSERT_TRUE(visited5->GetAdjList().size() == 2);
    ASSERT_TRUE(visited5->GetRoots().size() == 1);
    ASSERT_TRUE(visited5->GetRoots().contains(v5));

    for (auto* vtx : { v4, v5 }) {
        ASSERT_TRUE(visited4->GetAdjList().contains(vtx));
        ASSERT_TRUE(visited5->GetAdjList().contains(vtx));
    }
}

TEST(GcGraphTest, DirectedDFS)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    auto* v1 = new Vertex((std::byte*)0x1000, false);
    auto* v2 = new Vertex((std::byte*)0x1100, true);
    auto* v3 = new Vertex((std::byte*)0x1200, false);
    auto* v4 = new Vertex((std::byte*)0x1300, true);
    auto* v5 = new Vertex((std::byte*)0x1400, false);

    // First component
    objectsGraph->AddEdge(v1, v2);
    objectsGraph->AddEdge(v2, v3);

    // Second component
    objectsGraph->AddEdge(v4, v5);
    objectsGraph->AddEdge(v5, v4);

    ASSERT_TRUE(objectsGraph->GetVerticesCount() == 5);

    auto visited1 = objectsGraph->DirectedDFS(v1);
    ASSERT_TRUE(visited1->GetAdjList().size() == 3);
    ASSERT_TRUE(visited1->GetRoots().size() == 2);
    ASSERT_TRUE(visited1->GetRoots().contains(v3));
    ASSERT_TRUE(visited1->GetRoots().contains(v1));

    auto visited2 = objectsGraph->DirectedDFS(v2);
    ASSERT_TRUE(visited2->GetAdjList().size() == 2);
    ASSERT_TRUE(visited2->GetRoots().size() == 1);
    ASSERT_TRUE(visited2->GetRoots().contains(v3));

    auto visited3 = objectsGraph->DirectedDFS(v3);
    ASSERT_TRUE(visited3->GetAdjList().size() == 1);
    ASSERT_TRUE(visited3->GetRoots().size() == 1);
    ASSERT_TRUE(visited3->GetRoots().contains(v3));

    for (auto* vtx : { v1, v2, v3 }) {
        ASSERT_TRUE(visited1->GetAdjList().contains(vtx));
    }

    for (auto* vtx : { v2, v3 }) {
        ASSERT_TRUE(visited2->GetAdjList().contains(vtx));
    }

    ASSERT_TRUE(visited2->GetAdjList().contains(v3));

    auto visited4 = objectsGraph->DirectedDFS(v4);
    ASSERT_TRUE(visited4->GetAdjList().size() == 2);
    ASSERT_TRUE(visited4->GetRoots().size() == 1);
    ASSERT_TRUE(visited4->GetRoots().contains(v5));

    auto visited5 = objectsGraph->DirectedDFS(v5);
    ASSERT_TRUE(visited5->GetAdjList().size() == 2);
    ASSERT_TRUE(visited5->GetRoots().size() == 1);
    ASSERT_TRUE(visited5->GetRoots().contains(v5));

    for (auto* vtx : { v4, v5 }) {
        ASSERT_TRUE(visited4->GetAdjList().contains(vtx));
        ASSERT_TRUE(visited5->GetAdjList().contains(vtx));
    }
}

TEST(GcGraphTest, WeaklyConnectedComponents)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    auto* v1 = new Vertex((Chunk*)0x1000);
    auto* v2 = new Vertex((Chunk*)0x1100);
    auto* v3 = new Vertex((Chunk*)0x1200);
    auto* v4 = new Vertex((Chunk*)0x1300);
    auto* v5 = new Vertex((Chunk*)0x1400);

    // First weakly-connected component: { v1, v2, v3 }
    objectsGraph->AddEdge(v1, v2);
    objectsGraph->AddEdge(v2, v3);

    // Second weakly-connected component: { v4, v5 }
    objectsGraph->AddEdge(v4, v5);
    objectsGraph->AddEdge(v5, v4);

    ASSERT_TRUE(objectsGraph->GetVerticesCount() == 5);

    auto components = objectsGraph->WeaklyConnectedComponents();
    ASSERT_TRUE(components.size() == 2);

    // Test first weakly-connected component
    auto& firstComponent = components[0];
    ASSERT_TRUE(firstComponent->GetAdjList().size() == 3);
    ASSERT_TRUE(firstComponent->GetVerticesCount() == 3);
    for (auto* vtx : { v1, v2, v3 }) {
        ASSERT_TRUE(firstComponent->GetAdjList().contains(vtx));
    }

    // Test second weakly-connected component
    auto& secondComponent = components[1];
    ASSERT_TRUE(secondComponent->GetAdjList().size() == 2);
    ASSERT_TRUE(secondComponent->GetVerticesCount() == 2);
    for (auto* vtx : { v4, v5 }) {
        ASSERT_TRUE(secondComponent->GetAdjList().contains(vtx));
    }
}

TEST(GcGraphTest, ReachableWeaklyConnectedComponents)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);

    auto* v1 = new Vertex((std::byte*)0x1000, false);
    auto* v2 = new Vertex((std::byte*)0x1100, true);
    auto* v3 = new Vertex((std::byte*)0x1200, true);
    auto* cycle = new Vertex((std::byte*)Chunk::GetHeaderPtr(Allocate(1024)), true);

    auto* v4 = new Vertex((std::byte*)0x1300, true);
    auto* v5 = new Vertex((std::byte*)0x1400, false);

    // First weakly-connected component: { v1, v2, v3 }
    objectsGraph->AddEdge(v1, v2);
    objectsGraph->AddEdge(v2, v3);
    objectsGraph->AddEdge(cycle, cycle);
    objectsGraph->AddEdge(cycle, v3);

    // Second weakly-connected component: { v4, v5 }
    objectsGraph->AddEdge(v4, v5);
    objectsGraph->AddEdge(v5, v4);

    ASSERT_TRUE(objectsGraph->GetVerticesCount() == 6);

    auto components = objectsGraph->ReachableWeaklyConnectedComponents();
    ASSERT_TRUE(components.size() == 2);

    // Test first weakly-connected component
    auto& firstComponent = components[0];
    ASSERT_TRUE(firstComponent->GetAdjList().size() == 3);
    ASSERT_TRUE(firstComponent->GetVerticesCount() == 3);
    for (auto* vtx : { v1, v2, v3 }) {
        ASSERT_TRUE(firstComponent->GetAdjList().contains(vtx));
    }

    // Test second weakly-connected component
    auto& secondComponent = components[1];
    ASSERT_TRUE(secondComponent->GetAdjList().size() == 2);
    ASSERT_TRUE(secondComponent->GetVerticesCount() == 2);
    for (auto* vtx : { v4, v5 }) {
        ASSERT_TRUE(secondComponent->GetAdjList().contains(vtx));
    }
}

TEST(GcGraphTest, SetOrderedCorrectly)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    auto* v1 = new Vertex((Chunk*)0x1000);
    auto* v2 = new Vertex((Chunk*)0x1100);
    auto* v3 = new Vertex((Chunk*)0x1200);
    auto* v4 = new Vertex((Chunk*)0x1300);

    objectsGraph->AddVertex(v3);
    objectsGraph->AddVertex(v1);
    objectsGraph->AddVertex(v4);
    objectsGraph->AddVertex(v2);
    objectsGraph->AddVertex(v1);

    ASSERT_TRUE(objectsGraph->GetVerticesCount() == 4);

    int32_t idx = 0;
    for (Vertex* v : objectsGraph->GetAdjList()) {
        switch (idx) {
            case 0:
                ASSERT_TRUE(v == v1);
                break;
            case 1:
                ASSERT_TRUE(v == v2);
                break;
            case 2:
                ASSERT_TRUE(v == v3);
                break;
            case 3:
                ASSERT_TRUE(v == v4);
                break;
        }
        idx++;
    }
}

TEST(GcGraphTest, FindVertex)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
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
    objectsGraph->AddVertex(v1);

    ASSERT_TRUE(v1 == objectsGraph->FindVertex(v1ch));
    ASSERT_TRUE(v2 == objectsGraph->FindVertex(v2ch));
    ASSERT_TRUE(v3 == objectsGraph->FindVertex(v3ch));
    ASSERT_TRUE(v4 == objectsGraph->FindVertex(v4ch));
}

TEST(GcGraphTest, GetAllOutgoingGcPtrs)
{
    using namespace mpp;
    g_memoryManager = std::make_unique<MemoryManager>();

    // <Second GcPtr
    //         <First GcPtr.........>>
    SharedGcPtr<SharedGcPtr<int32_t>> a =
        MakeShared<SharedGcPtr<int32_t>>(MakeShared<int32_t>(1337));

    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    for (auto* gcPtr : g_memoryManager->GetGC().GetGcPtrs()) {
        objectsGraph->AddObjectInfo(gcPtr);
    }
    ASSERT_EQ(objectsGraph->GetAdjList().size(), 3);
    ASSERT_EQ(g_memoryManager->GetGC().GetGcPtrs().size(), 2);

    void* firstGcPtrLocation = Chunk::GetHeaderPtr(a->GetVoid());
    void* secondGcPtrLocation = &a;
    ASSERT_NE(firstGcPtrLocation, secondGcPtrLocation);

    auto* firstVertex = objectsGraph->FindVertex((Chunk*)firstGcPtrLocation);
    auto* secondVertex = objectsGraph->FindVertex((Chunk*)secondGcPtrLocation);
    ASSERT_NE(firstVertex, nullptr);
    ASSERT_NE(secondVertex, nullptr);
    ASSERT_NE(firstVertex, secondVertex);
    ASSERT_EQ(
        firstVertex->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(
        secondVertex->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(),
        1);
}

TEST(GcGraphTest, GetAllOutgoingGcPtrs3)
{
    using namespace mpp;
    g_memoryManager = std::make_unique<MemoryManager>();

    struct Node
    {
        SharedGcPtr<int32_t> a;
        SharedGcPtr<int32_t> b;
        SharedGcPtr<int32_t> c;
    };

    SharedGcPtr<Node> nodePtr = MakeShared<Node>();
    nodePtr->a = MakeShared<int32_t>(1);
    nodePtr->b = MakeShared<int32_t>(2);
    nodePtr->c = MakeShared<int32_t>(3);
    SharedGcPtr<SharedGcPtr<Node>> ptrToNodePtr = MakeShared<SharedGcPtr<Node>>(nodePtr);

    nodePtr = nullptr;

    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    for (auto* gcPtr : g_memoryManager->GetGC().GetGcPtrs()) {
        objectsGraph->AddObjectInfo(gcPtr);
    }
    ASSERT_EQ(objectsGraph->GetRoots().size(), 1);
    ASSERT_EQ(objectsGraph->GetAdjList().size(), 6);
    ASSERT_EQ(objectsGraph->GetVerticesCount(), 6);
    ASSERT_EQ(g_memoryManager->GetGC().GetGcPtrs().size(), 5);

    auto* nodePtrVtx = objectsGraph->FindVertex((Chunk*)&nodePtr);
    ASSERT_EQ(nodePtrVtx, nullptr);

    auto* ptrToNodePtrVtx = objectsGraph->FindVertex((Chunk*)&ptrToNodePtr);
    ASSERT_NE(ptrToNodePtrVtx, nullptr);

    auto* nodePtrVtxValid =
        objectsGraph->FindVertex(g_memoryManager->GetGC().FindChunkInUse(ptrToNodePtr.GetVoid()));
    ASSERT_NE(nodePtrVtxValid, nullptr);

    ASSERT_EQ(objectsGraph->HasEdge(ptrToNodePtrVtx, nodePtrVtxValid), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodePtrVtxValid, ptrToNodePtrVtx), false);

    ASSERT_EQ(
        ptrToNodePtrVtx->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(),
        1);
    ASSERT_EQ(
        nodePtrVtxValid->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(),
        1);

    auto* nodeVtx = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(ptrToNodePtr.Get()->GetVoid()));
    ASSERT_NE(nodeVtx, nullptr);
    ASSERT_EQ(nodeVtx->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(),
              3);

    auto* aVtxTmp = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(&ptrToNodePtr.Get()->Get()->a));
    ASSERT_EQ(aVtxTmp, nodeVtx);
    auto* bVtxTmp = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(&ptrToNodePtr.Get()->Get()->b));
    ASSERT_EQ(bVtxTmp, nodeVtx);
    auto* cVtxTmp = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(&ptrToNodePtr.Get()->Get()->c));
    ASSERT_EQ(cVtxTmp, nodeVtx);

    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, aVtxTmp), false);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, bVtxTmp), false);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, cVtxTmp), false);

    auto* aVtx = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(ptrToNodePtr.Get()->Get()->a.GetVoid()));
    ASSERT_NE(aVtx, nullptr);
    auto* bVtx = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(ptrToNodePtr.Get()->Get()->b.GetVoid()));
    ASSERT_NE(bVtx, nullptr);
    auto* cVtx = objectsGraph->FindVertex(
        g_memoryManager->GetGC().FindChunkInUse(ptrToNodePtr.Get()->Get()->c.GetVoid()));
    ASSERT_NE(cVtx, nullptr);

    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, aVtx), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, bVtx), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, cVtx), true);

    ASSERT_EQ(aVtx->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(bVtx->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(cVtx->GetAllOutgoingGcPtrs(g_memoryManager->GetGC().BuildOrderedGcPtrs()).size(), 0);

    // Generate graphviz layout just to check that at least it doesn't segfault 🤷
    std::stringstream ss;
    objectsGraph->GenerateGraphvizLayoutSimple(ss);
    objectsGraph->GenerateGraphvizLayoutAdvanced(ss);
}

TEST(GcGraphTest, DISABLED_GenerateGraphvizLayout)
{
    // This test is disabled because it is unreliable and requires you to temporarily disable aslr.
    // If you still want to execute it do as follows:
    // setarch `uname -m` -R ./build/tests/unit_tests --gtest_also_run_disabled_tests
    using namespace mpp;

    struct Node
    {
        SharedGcPtr<int32_t> a;
        SharedGcPtr<int32_t> b;
        SharedGcPtr<int32_t> c;
    };

    SharedGcPtr<Node> nodePtr = MakeShared<Node>();
    nodePtr->a = MakeShared<int32_t>(1);
    nodePtr->b = MakeShared<int32_t>(2);
    nodePtr->c = MakeShared<int32_t>(3);
    SharedGcPtr<SharedGcPtr<Node>> ptrToNodePtr = MakeShared<SharedGcPtr<Node>>(nodePtr);

    nodePtr = nullptr;

    std::unique_ptr<GcGraph> objectsGraph =
        std::make_unique<GcGraph>(g_memoryManager->GetGC(), *g_memoryManager);
    for (auto* gcPtr : g_memoryManager->GetGC().GetGcPtrs()) {
        objectsGraph->AddObjectInfo(gcPtr);
    }

    std::string correctOutput =
        "digraph Objects {\n\tcompound=true;\n\tratio=expand;\n\tgraph [ranksep=1.5]\n\n\t// Draw "
        "flat heap layout\n\theap[ shape = none style = \"\" ];\n\theap[ label=<\n\t<table "
        "BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n\t\t<TR>\n\t\t\t<TD "
        "bgcolor=\"#ccebc5\" PORT=\"0x7ffff5a3c000\">3c000</TD>\n\t\t\t<TD bgcolor=\"#ccebc5\" "
        "PORT=\"0x7ffff5a3c060\">3c060</TD>\n\t\t\t<TD bgcolor=\"#ccebc5\" "
        "PORT=\"0x7ffff5a3c080\">3c080</TD>\n\t\t\t<TD bgcolor=\"#ccebc5\" "
        "PORT=\"0x7ffff5a3c0a0\">3c0a0</TD>\n\t\t\t<TD bgcolor=\"#ccebc5\" "
        "PORT=\"0x7ffff5a3c0c0\">3c0c0</TD>\n\t\t\t<TD bgcolor=\"#fed9a6\" "
        "PORT=\"0x7ffff5a3c100\">3c100</TD>\n\t\t\t<TD>.....</TD>\n\t\t</TR>\n\t</table>>];\n\n\t//"
        " Draw all chunks (begin)\n\tnode[ style=\"filled\" ];\n\tsubgraph "
        "\"cluster-0x7ffff5a3c000\" {\n\t\tlabel=\"chunk\\n0x7ffff5a3c000\\nsize = "
        "96\";\n\t\tstyle=\"rounded,filled\";\n\t\tfillcolor=\"#ccebc5\";\n\t\tsubgraph "
        "\"cluster\" {\n\t\t\tstyle=\"dashed\";\n\t\t\tlabel=\"\";\n\t\t\t\"0x7ffff5a3c010\" "
        "[style=\"filled,dashed\", fillcolor=\"#ccebc5\", shape=box, "
        "label=\"gcptr-1\"];\n\t\t\t\"0x7ffff5a3c028\" [style=\"filled,dashed\", "
        "fillcolor=\"#ccebc5\", shape=box, label=\"gcptr-2\"];\n\t\t\t\"0x7ffff5a3c040\" "
        "[style=\"filled,dashed\", fillcolor=\"#ccebc5\", shape=box, "
        "label=\"gcptr-3\"];\n\t\t}\n\t}\n\n\t// Draw connections between GC-pointers from current "
        "chunk 0x7ffff5a3c000 and chunks\n\t\"0x7ffff5a3c010\":s -> "
        "\"0x7ffff5a3c060\";\n\t\"0x7ffff5a3c028\":s -> "
        "\"0x7ffff5a3c080\";\n\t\"0x7ffff5a3c040\":s -> \"0x7ffff5a3c0a0\";\n\t\"0x7ffff5a3c060\" "
        "[fillcolor=\"#ccebc5\", label=\"chunk\\n0x7ffff5a3c060\\nsize = 32\"];\n\n\t// Draw "
        "connections between GC-pointers from current chunk 0x7ffff5a3c060 and "
        "chunks\n\t\"0x7ffff5a3c080\" [fillcolor=\"#ccebc5\", "
        "label=\"chunk\\n0x7ffff5a3c080\\nsize = 32\"];\n\n\t// Draw connections between "
        "GC-pointers from current chunk 0x7ffff5a3c080 and chunks\n\t\"0x7ffff5a3c0a0\" "
        "[fillcolor=\"#ccebc5\", label=\"chunk\\n0x7ffff5a3c0a0\\nsize = 32\"];\n\n\t// Draw "
        "connections between GC-pointers from current chunk 0x7ffff5a3c0a0 and chunks\n\tsubgraph "
        "\"cluster-0x7ffff5a3c0c0\" {\n\t\tlabel=\"chunk\\n0x7ffff5a3c0c0\\nsize = "
        "64\";\n\t\tstyle=\"rounded,filled\";\n\t\tfillcolor=\"#ccebc5\";\n\t\tsubgraph "
        "\"cluster\" {\n\t\t\tstyle=\"dashed\";\n\t\t\tlabel=\"\";\n\t\t\t\"0x7ffff5a3c0d0\" "
        "[style=\"filled,dashed\", fillcolor=\"#ccebc5\", shape=box, "
        "label=\"gcptr-4\"];\n\t\t}\n\t}\n\n\t// Draw connections between GC-pointers from current "
        "chunk 0x7ffff5a3c0c0 and chunks\n\t\"0x7ffff5a3c0d0\":s -> \"0x7ffff5a3c010\" "
        "[lhead=\"cluster-0x7ffff5a3c000\"];\n\t\"0x7ffff5a3c100\" [fillcolor=\"#fed9a6\", "
        "label=\"chunk\\n0x7ffff5a3c100\\nsize = 33554176\"];\n\t// Draw all chunks (end)\n\n\t// "
        "Draw connections between non-heap GC-pointers and chunks\n\t\"0x7fffffffd0f8\" "
        "[style=filled, fillcolor=\"#cccccc\", shape=rect, "
        "label=\"gcptr-5\"];\n\t\"0x7fffffffd0f8\":s -> \"0x7ffff5a3c0d0\" "
        "[lhead=\"cluster-0x7ffff5a3c0c0\"];\n\n\t// Draw connections from all chunks to the flat "
        "heap view\n\t\"0x7ffff5a3c010\" -> heap:\"0x7ffff5a3c000\" "
        "[ltail=\"cluster-0x7ffff5a3c000\", style=dashed, "
        "color=\"#bcbddc\"];\n\t\"0x7ffff5a3c060\" -> heap:\"0x7ffff5a3c060\" [style=dashed, "
        "color=\"#bcbddc\"];\n\t\"0x7ffff5a3c080\" -> heap:\"0x7ffff5a3c080\" [style=dashed, "
        "color=\"#bcbddc\"];\n\t\"0x7ffff5a3c0a0\" -> heap:\"0x7ffff5a3c0a0\" [style=dashed, "
        "color=\"#bcbddc\"];\n\t\"0x7ffff5a3c0d0\" -> heap:\"0x7ffff5a3c0c0\" "
        "[ltail=\"cluster-0x7ffff5a3c0c0\", style=dashed, "
        "color=\"#bcbddc\"];\n\t\"0x7ffff5a3c100\" -> heap:\"0x7ffff5a3c100\" [style=dashed, "
        "color=\"#bcbddc\"];\n}";

    std::stringstream ss;
    objectsGraph->GenerateGraphvizLayoutSimple(ss);
    ASSERT_EQ(ss.str(), correctOutput);
}

/* For ctrl+c, ctrl+v
TEST(GcGraphTest, "")
{
    using namespace mpp;

}
*/