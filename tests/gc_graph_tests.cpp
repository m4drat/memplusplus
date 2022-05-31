#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include <memory>

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

/* For ctrl+c, ctrl+v
TEST(GcGraphTest, "")
{
    using namespace mpp;

}
*/