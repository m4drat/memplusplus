#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include <catch2/catch_all.hpp>
#include <memory>

TEST_CASE("Check, that set is correctly ordered")
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

    REQUIRE(objectsGraph->GetGraphVerticesCount() == 4);

    int32_t idx = 0;
    for (Vertex* v : objectsGraph->GetAdjList()) {
        switch (idx) {
            case 0:
                REQUIRE(v == v1);
                break;
            case 1:
                REQUIRE(v == v2);
                break;
            case 2:
                REQUIRE(v == v3);
                break;
            case 3:
                REQUIRE(v == v4);
                break;
        }
        idx++;
    }
}

TEST_CASE("Check workability of FindVertex method of gc_graph")
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

    REQUIRE(v1 == objectsGraph->FindVertex(v1ch));
    REQUIRE(v2 == objectsGraph->FindVertex(v2ch));
    REQUIRE(v3 == objectsGraph->FindVertex(v3ch));
    REQUIRE(v4 == objectsGraph->FindVertex(v4ch));
}

/* For ctrl+c, ctrl+v
TEST_CASE("")
{
    using namespace mpp;

}
*/