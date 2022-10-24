#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/shared_gcptr.hpp"
#include <cstddef>
#include <memory>
#include <sstream>

TEST(GcGraphTest, SetOrderedCorrectly)
{
    using namespace mpp;
    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    Vertex* v1 = new Vertex((Chunk*)0x1000);
    Vertex* v2 = new Vertex((Chunk*)0x1100);
    Vertex* v3 = new Vertex((Chunk*)0x1200);
    Vertex* v4 = new Vertex((Chunk*)0x1300);

    objectsGraph->AddVertex(v3);
    objectsGraph->AddVertex(v1);
    objectsGraph->AddVertex(v4);
    objectsGraph->AddVertex(v2);
    objectsGraph->AddVertex(v1);

    ASSERT_TRUE(objectsGraph->GetGraphVerticesCount() == 4);

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
    objectsGraph->AddVertex(v1);

    ASSERT_TRUE(v1 == objectsGraph->FindVertex(v1ch));
    ASSERT_TRUE(v2 == objectsGraph->FindVertex(v2ch));
    ASSERT_TRUE(v3 == objectsGraph->FindVertex(v3ch));
    ASSERT_TRUE(v4 == objectsGraph->FindVertex(v4ch));
}

TEST(GcGraphTest, GetAllOutgoingGcPtrs)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    // <Second GcPtr
    //         <First GcPtr.........>>
    SharedGcPtr<SharedGcPtr<int32_t>> a =
        MakeShared<SharedGcPtr<int32_t>>(MakeShared<int32_t>(1337));

    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    for (auto* gcPtr : GC::GetInstance().GetGcPtrs()) {
        objectsGraph->AddObjectInfo(gcPtr);
    }
    ASSERT_EQ(objectsGraph->GetAdjList().size(), 3);
    ASSERT_EQ(GC::GetInstance().GetGcPtrs().size(), 2);

    void* firstGcPtrLocation = Chunk::GetHeaderPtr(a->GetVoid());
    void* secondGcPtrLocation = &a;
    ASSERT_NE(firstGcPtrLocation, secondGcPtrLocation);

    auto* firstVertex = objectsGraph->FindVertex((Chunk*)firstGcPtrLocation);
    auto* secondVertex = objectsGraph->FindVertex((Chunk*)secondGcPtrLocation);
    ASSERT_NE(firstVertex, nullptr);
    ASSERT_NE(secondVertex, nullptr);
    ASSERT_NE(firstVertex, secondVertex);
    ASSERT_EQ(firstVertex->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(secondVertex->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 1);
}

TEST(GcGraphTest, GetAllOutgoingGcPtrs3)
{
    using namespace mpp;
    MM::ResetAllocatorState();

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

    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    for (auto* gcPtr : GC::GetInstance().GetGcPtrs()) {
        objectsGraph->AddObjectInfo(gcPtr);
    }
    ASSERT_EQ(objectsGraph->GetAdjList().size(), 6);
    ASSERT_EQ(objectsGraph->GetGraphVerticesCount(), 6);
    ASSERT_EQ(GC::GetInstance().GetGcPtrs().size(), 5);

    auto* nodePtrVtx = objectsGraph->FindVertex((Chunk*)&nodePtr);
    ASSERT_EQ(nodePtrVtx, nullptr);

    auto* ptrToNodePtrVtx = objectsGraph->FindVertex((Chunk*)&ptrToNodePtr);
    ASSERT_NE(ptrToNodePtrVtx, nullptr);

    auto* nodePtrVtxValid =
        objectsGraph->FindVertex(MM::GetInUseChunkByPtr(ptrToNodePtr.GetVoid()));
    ASSERT_NE(nodePtrVtxValid, nullptr);

    ASSERT_EQ(objectsGraph->HasEdge(ptrToNodePtrVtx, nodePtrVtxValid), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodePtrVtxValid, ptrToNodePtrVtx), false);

    ASSERT_EQ(ptrToNodePtrVtx->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(),
              1);
    ASSERT_EQ(nodePtrVtxValid->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(),
              1);

    auto* nodeVtx = objectsGraph->FindVertex(MM::GetInUseChunkByPtr(ptrToNodePtr.Get()->GetVoid()));
    ASSERT_NE(nodeVtx, nullptr);
    ASSERT_EQ(nodeVtx->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 3);

    auto* aVtxTmp = objectsGraph->FindVertex(MM::GetInUseChunkByPtr(&ptrToNodePtr.Get()->Get()->a));
    ASSERT_EQ(aVtxTmp, nodeVtx);
    auto* bVtxTmp = objectsGraph->FindVertex(MM::GetInUseChunkByPtr(&ptrToNodePtr.Get()->Get()->b));
    ASSERT_EQ(bVtxTmp, nodeVtx);
    auto* cVtxTmp = objectsGraph->FindVertex(MM::GetInUseChunkByPtr(&ptrToNodePtr.Get()->Get()->c));
    ASSERT_EQ(cVtxTmp, nodeVtx);

    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, aVtxTmp), false);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, bVtxTmp), false);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, cVtxTmp), false);

    auto* aVtx =
        objectsGraph->FindVertex(MM::GetInUseChunkByPtr(ptrToNodePtr.Get()->Get()->a.GetVoid()));
    ASSERT_NE(aVtx, nullptr);
    auto* bVtx =
        objectsGraph->FindVertex(MM::GetInUseChunkByPtr(ptrToNodePtr.Get()->Get()->b.GetVoid()));
    ASSERT_NE(bVtx, nullptr);
    auto* cVtx =
        objectsGraph->FindVertex(MM::GetInUseChunkByPtr(ptrToNodePtr.Get()->Get()->c.GetVoid()));
    ASSERT_NE(cVtx, nullptr);

    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, aVtx), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, bVtx), true);
    ASSERT_EQ(objectsGraph->HasEdge(nodeVtx, cVtx), true);

    ASSERT_EQ(aVtx->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(bVtx->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 0);
    ASSERT_EQ(cVtx->GetAllOutgoingGcPtrs(GC::GetInstance().GetOrderedGcPtrs()).size(), 0);

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

    std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();
    for (auto* gcPtr : GC::GetInstance().GetGcPtrs()) {
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