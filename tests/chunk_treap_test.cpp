#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/memory_manager.hpp"

TEST(ChunkTreapTest, ChunkToDeleteLocatedInBetween)
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)MemoryManager::Allocate(50);
    Chunk* ch2 = (Chunk*)MemoryManager::Allocate(50);
    Chunk* ch3 = (Chunk*)MemoryManager::Allocate(50);

    ASSERT_TRUE((((std::size_t)ch1 < (std::size_t)ch2) && ((std::size_t)ch2 < (std::size_t)ch3)));

    ch1->SetSize(16);
    ch2->SetSize(16);
    ch3->SetSize(16);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);

    cTreap->RemoveChunk(ch2);

    if (cTreap->GetRootNode()->leftChild != nullptr) {
        ASSERT_TRUE(
            ((cTreap->GetRootNode()->chunk == ch1) || (cTreap->GetRootNode()->chunk == ch3)));
        ASSERT_TRUE(((cTreap->GetRootNode()->leftChild->chunk == ch1) ||
                     (cTreap->GetRootNode()->leftChild->chunk == ch3)));
    } else {
        ASSERT_TRUE(
            ((cTreap->GetRootNode()->chunk == ch1) || (cTreap->GetRootNode()->chunk == ch3)));
        ASSERT_TRUE(((cTreap->GetRootNode()->rightChild->chunk == ch1) ||
                     (cTreap->GetRootNode()->rightChild->chunk == ch3)));
    }
}

TEST(ChunkTreapTest, BigTree)
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

    ch1->SetSize(32);
    ch2->SetSize(64);
    ch3->SetSize(96);
    ch4->SetSize(128);
    ch5->SetSize(160);
    ch6->SetSize(192);
    ch7->SetSize(224);
    ch8->SetSize(256);
    ch9->SetSize(288);

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

    ASSERT_TRUE(cTreap->MaxSizeChunk()->GetSize() == 256);
    ASSERT_TRUE(cTreap->MinSizeChunk()->GetSize() == 64);
}

TEST(ChunkTreapTest, CorrectChunkInsertion)
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();
    Chunk* insertedChunk = (Chunk*)malloc(64);

    std::size_t insertedChunkSize = 128;
    insertedChunk->SetSize(insertedChunkSize);

    Chunk* result1 = cTreap->FirstGreaterOrEqualThan(insertedChunkSize);

    cTreap->InsertChunk(insertedChunk);

    Chunk* result2 = cTreap->FirstGreaterOrEqualThan(insertedChunkSize);

    ASSERT_TRUE((result1 == nullptr && result2 == insertedChunk));
}

TEST(ChunkTreapTest, NonexistingBigChunk)
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* chunk1 = (Chunk*)malloc(64);
    Chunk* chunk2 = (Chunk*)malloc(64);
    Chunk* chunk3 = (Chunk*)malloc(64);

    chunk1->SetSize(32);
    chunk2->SetSize(64);
    chunk3->SetSize(96);

    cTreap->InsertChunk(chunk1);
    cTreap->InsertChunk(chunk2);
    cTreap->InsertChunk(chunk3);

    std::size_t nonexistentSize{ 128 };

    Chunk* result = cTreap->FirstGreaterOrEqualThan(nonexistentSize);

    ASSERT_TRUE(result == nullptr);
}

TEST(ChunkTreapTest, BasicFunctions)
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(64);
    Chunk* ch2 = (Chunk*)malloc(64);
    Chunk* ch3 = (Chunk*)malloc(64);
    Chunk* ch4 = (Chunk*)malloc(64);

    ch1->SetSize(32);
    ch2->SetSize(32);
    ch3->SetSize(32);
    ch4->SetSize(32);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);
    cTreap->InsertChunk(ch4);

    ASSERT_TRUE(
        (cTreap->MaxSizeChunk()->GetSize() == 32 && cTreap->MinSizeChunk()->GetSize() == 32));
}

TEST(ChunkTreapTest, DeleteMany)
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);

    ch1->SetSize(32);
    ch2->SetSize(32);
    ch3->SetSize(32);
    ch4->SetSize(32);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);
    cTreap->InsertChunk(ch3);
    cTreap->InsertChunk(ch4);

    cTreap->RemoveChunk(ch2);
    cTreap->RemoveChunk(ch3);

    ASSERT_TRUE(
        (cTreap->MaxSizeChunk()->GetSize() == 32 && cTreap->MinSizeChunk()->GetSize() == 32));
}