#include "catch2/catch.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/chunk.hpp"

TEST_CASE("Check that chunk to delete is in the middle of another chunks")
{
    using namespace mpp;
    
    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);

    assert(((std::size_t)ch1 < (std::size_t)ch2) && 
           ((std::size_t)ch2 < (std::size_t)ch3));

    ch1->SetSize(16);
    ch2->SetSize(16);
    ch3->SetSize(16);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);

    cTreap->RemoveChunk(ch2);

    if (cTreap->GetRootNode()->leftChild != nullptr)
    {
        REQUIRE(((cTreap->GetRootNode()->chunk == ch1) ||
                 (cTreap->GetRootNode()->chunk == ch3))); 
        REQUIRE(((cTreap->GetRootNode()->leftChild->chunk == ch1) || 
                 (cTreap->GetRootNode()->leftChild->chunk == ch3))); 
    } else {
        REQUIRE(((cTreap->GetRootNode()->chunk == ch1) ||
                 (cTreap->GetRootNode()->chunk == ch3))); 
        REQUIRE(((cTreap->GetRootNode()->rightChild->chunk == ch1) || 
                 (cTreap->GetRootNode()->rightChild->chunk == ch3))); 
    }
}

TEST_CASE("Check big tree")
{
    using namespace mpp;
    
    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);
    Chunk* ch5 = (Chunk*)malloc(128);
    Chunk* ch6 = (Chunk*)malloc(128);
    Chunk* ch7 = (Chunk*)malloc(128);
    Chunk* ch8 = (Chunk*)malloc(128);
    Chunk* ch9 = (Chunk*)malloc(128);
    
    ch1->SetSize(16);
    ch2->SetSize(32);
    ch3->SetSize(48);
    ch4->SetSize(64);
    ch5->SetSize(80);
    ch6->SetSize(96);
    ch7->SetSize(112);
    ch8->SetSize(128);
    ch9->SetSize(144);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);
    cTreap->InsertChunk(ch4);
    cTreap->InsertChunk(ch5);
    cTreap->InsertChunk(ch6);
    cTreap->InsertChunk(ch7);
    cTreap->InsertChunk(ch8);
    cTreap->InsertChunk(ch9);

    cTreap->RemoveChunk(ch1);
    cTreap->RemoveChunk(ch9);

    REQUIRE(cTreap->MaxSizeChunk()->GetSize() == 128); 
    REQUIRE(cTreap->MinSizeChunk()->GetSize() == 32);
}

TEST_CASE("Check for correct chunk insertion")
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();     
    Chunk* insertedChunk = (Chunk*)malloc(64);

    std::size_t insertedChunkSize = 128;
    insertedChunk->SetSize(insertedChunkSize);

    Chunk* result1 = cTreap->FirstGreaterOrEqualThan(insertedChunkSize);

    cTreap->InsertChunk(insertedChunk);

    Chunk* result2 = cTreap->FirstGreaterOrEqualThan(insertedChunkSize);

    REQUIRE((result1 == nullptr && result2 == insertedChunk));
}

TEST_CASE("Check for nonexistent large chunk")
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap(); 
    
    Chunk* chunk1 = (Chunk*)malloc(64);
    Chunk* chunk2 = (Chunk*)malloc(64);
    Chunk* chunk3 = (Chunk*)malloc(64);

    chunk1->SetSize(16);
    chunk2->SetSize(32);
    chunk3->SetSize(64);

    cTreap->InsertChunk(chunk1);
    cTreap->InsertChunk(chunk2);
    cTreap->InsertChunk(chunk3);

    std::size_t nonexistentSize{ 128 };

    Chunk* result = cTreap->FirstGreaterOrEqualThan(nonexistentSize);

    REQUIRE(result == nullptr);
}

TEST_CASE("Check basic functions")
{
    using namespace mpp;
    
    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(64);
    Chunk* ch2 = (Chunk*)malloc(64);
    Chunk* ch3 = (Chunk*)malloc(64);
    Chunk* ch4 = (Chunk*)malloc(64);
    
    ch1->SetSize(16);
    ch2->SetSize(16);
    ch3->SetSize(16);
    ch4->SetSize(16);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);
    cTreap->InsertChunk(ch4);

    REQUIRE((cTreap->MaxSizeChunk()->GetSize() == 16 && cTreap->MinSizeChunk()->GetSize() == 16 ));
}

TEST_CASE("Check delete many")
{
    using namespace mpp;
    
    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);
    
    ch1->SetSize(16);
    ch2->SetSize(16);
    ch3->SetSize(16);
    ch4->SetSize(16);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);
    cTreap->InsertChunk(ch4);

    cTreap->RemoveChunk(ch2);
    cTreap->RemoveChunk(ch3);

    REQUIRE((cTreap->MaxSizeChunk()->GetSize() == 16 && cTreap->MinSizeChunk()->GetSize() == 16 ));
}