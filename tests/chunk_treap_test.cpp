#include "gtest/gtest.h"
#include <memory>

#include "mpplib/chunk.hpp"
#include "mpplib/containers/chunk_treap.hpp"
#include "mpplib/memory_manager.hpp"

TEST(ChunkTreapTest, ChunkToDeleteLocatedInBetween)
{
    using namespace mpp;

    ChunkTreap cTreap;

    MM memMgr = MM();

    auto* ch1 = (Chunk*)memMgr.Allocate(50);
    auto* ch2 = (Chunk*)memMgr.Allocate(50);
    auto* ch3 = (Chunk*)memMgr.Allocate(50);

    ASSERT_TRUE((((std::size_t)ch1 < (std::size_t)ch2) && ((std::size_t)ch2 < (std::size_t)ch3)));

    ch1->SetSize(16);
    ch2->SetSize(16);
    ch3->SetSize(16);

    cTreap.InsertChunk(ch1);
    cTreap.InsertChunk(ch2);
    cTreap.InsertChunk(ch3);

    cTreap.RemoveChunk(ch2);

    if (cTreap.GetRootNode()->leftChild != nullptr) {
        ASSERT_TRUE(((cTreap.GetRootNode()->chunk == ch1) || (cTreap.GetRootNode()->chunk == ch3)));
        ASSERT_TRUE(((cTreap.GetRootNode()->leftChild->chunk == ch1) ||
                     (cTreap.GetRootNode()->leftChild->chunk == ch3)));
    } else {
        ASSERT_TRUE(((cTreap.GetRootNode()->chunk == ch1) || (cTreap.GetRootNode()->chunk == ch3)));
        ASSERT_TRUE(((cTreap.GetRootNode()->rightChild->chunk == ch1) ||
                     (cTreap.GetRootNode()->rightChild->chunk == ch3)));
    }

    memMgr.Deallocate(ch1);
    memMgr.Deallocate(ch2);
    memMgr.Deallocate(ch3);
}

TEST(ChunkTreapTest, CheckAllConstructorsAndAssignOperators)
{
    using namespace mpp;

    ChunkTreap cTreap;

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

    cTreap.InsertChunk(ch1);
    cTreap.InsertChunk(ch2);
    cTreap.InsertChunk(ch3);
    cTreap.InsertChunk(ch4);
    cTreap.InsertChunk(ch5);
    cTreap.InsertChunk(ch6);
    cTreap.InsertChunk(ch7);
    cTreap.InsertChunk(ch8);
    cTreap.InsertChunk(ch9);

    ASSERT_TRUE(cTreap.MinSizeChunk()->GetSize() == 32);
    ASSERT_TRUE(cTreap.MaxSizeChunk()->GetSize() == 288);
    ASSERT_EQ(cTreap.TotalFreeChunks(), 9);

    // Generate graphviz layout just to check that at least it doesn't segfault 🤷
    std::stringstream ss;
    cTreap.GenerateGraphvizLayout(ss);

    ASSERT_TRUE(cTreap.RemoveChunk(ch1));
    ASSERT_TRUE(cTreap.RemoveChunk(ch6));
    ASSERT_TRUE(cTreap.RemoveChunk(ch9));

    ASSERT_TRUE(cTreap.MaxSizeChunk()->GetSize() == 256);
    ASSERT_TRUE(cTreap.MinSizeChunk()->GetSize() == 64);
    ASSERT_EQ(cTreap.TotalFreeChunks(), 6);

    // Check move copy constructor
    ChunkTreap newTreap1 = std::move(cTreap);
    ASSERT_TRUE(newTreap1.MaxSizeChunk()->GetSize() == 256);
    ASSERT_TRUE(newTreap1.MinSizeChunk()->GetSize() == 64);
    ASSERT_EQ(newTreap1.TotalFreeChunks(), 6);

    ASSERT_EQ(newTreap1.FirstGreaterOrEqualTo(256), ch8);
    ASSERT_EQ(newTreap1.TotalFreeChunks(), 6);

    ASSERT_TRUE(newTreap1.RemoveChunk(ch8));
    ASSERT_EQ(newTreap1.TotalFreeChunks(), 5);
    ASSERT_EQ(cTreap.TotalFreeChunks(), 0);
    ASSERT_EQ(cTreap.TotalFreeMemory(), 0);

    // Check copy constructor
    ChunkTreap newTreap2 = newTreap1;
    ASSERT_TRUE(newTreap2.MaxSizeChunk()->GetSize() == 224);
    ASSERT_TRUE(newTreap2.MinSizeChunk()->GetSize() == 64);
    ASSERT_EQ(newTreap2.TotalFreeChunks(), 5);

    ASSERT_EQ(newTreap2.FirstGreaterOrEqualTo(224), ch7);
    ASSERT_EQ(newTreap2.TotalFreeChunks(), 5);

    ASSERT_TRUE(newTreap2.RemoveChunk(ch7));
    ASSERT_EQ(newTreap2.TotalFreeChunks(), 4);
    ASSERT_EQ(newTreap1.TotalFreeChunks(), 5);

    ASSERT_EQ(newTreap1.FirstGreaterOrEqualTo(224), ch7);
    ASSERT_TRUE(newTreap1.RemoveChunk(ch7));
    ASSERT_EQ(newTreap1.FirstGreaterOrEqualTo(224), nullptr);

    // Check copy assignment operator
    ChunkTreap newTreap3;
    newTreap3 = newTreap2;
    ASSERT_TRUE(newTreap3.MaxSizeChunk()->GetSize() == 160);
    ASSERT_TRUE(newTreap3.MinSizeChunk()->GetSize() == 64);
    ASSERT_EQ(newTreap3.TotalFreeChunks(), 4);

    ASSERT_EQ(newTreap3.FirstGreaterOrEqualTo(160), ch5);
    ASSERT_EQ(newTreap3.TotalFreeChunks(), 4);

    ASSERT_TRUE(newTreap3.RemoveChunk(ch5));
    ASSERT_EQ(newTreap3.TotalFreeChunks(), 3);
    ASSERT_EQ(newTreap2.TotalFreeChunks(), 4);
    ASSERT_EQ(newTreap2.FirstGreaterOrEqualTo(160), ch5);

    // Check move assignment operator
    ChunkTreap newTreap4;
    newTreap4 = std::move(newTreap3);
    ASSERT_TRUE(newTreap4.MaxSizeChunk()->GetSize() == 128);
    ASSERT_TRUE(newTreap4.MinSizeChunk()->GetSize() == 64);
    ASSERT_EQ(newTreap4.TotalFreeChunks(), 3);

    ASSERT_EQ(newTreap4.FirstGreaterOrEqualTo(128), ch4);
    ASSERT_EQ(newTreap4.TotalFreeChunks(), 3);

    ASSERT_TRUE(newTreap4.RemoveChunk(ch4));
    ASSERT_EQ(newTreap4.TotalFreeChunks(), 2);
    ASSERT_EQ(newTreap4.FirstGreaterOrEqualTo(128), nullptr);

    free(ch1);
    free(ch2);
    free(ch3);
    free(ch4);
    free(ch5);
    free(ch6);
    free(ch7);
    free(ch8);
    free(ch9);
}

TEST(ChunkTreapTest, CorrectChunkInsertion)
{
    using namespace mpp;

    ChunkTreap cTreap;
    Chunk* insertedChunk = (Chunk*)malloc(64);

    std::size_t insertedChunkSize = 128;
    insertedChunk->SetSize(insertedChunkSize);

    Chunk* result1 = cTreap.FirstGreaterOrEqualTo(insertedChunkSize);

    cTreap.InsertChunk(insertedChunk);

    Chunk* result2 = cTreap.FirstGreaterOrEqualTo(insertedChunkSize);

    ASSERT_TRUE((result1 == nullptr && result2 == insertedChunk));

    free(insertedChunk);
}

TEST(ChunkTreapTest, NonexistingBigChunk)
{
    using namespace mpp;

    ChunkTreap cTreap;

    Chunk* chunk1 = (Chunk*)malloc(64);
    Chunk* chunk2 = (Chunk*)malloc(64);
    Chunk* chunk3 = (Chunk*)malloc(64);

    chunk1->SetSize(32);
    chunk2->SetSize(64);
    chunk3->SetSize(96);

    cTreap.InsertChunk(chunk1);
    cTreap.InsertChunk(chunk2);
    cTreap.InsertChunk(chunk3);

    std::size_t nonexistentSize{ 128 };

    Chunk* result = cTreap.FirstGreaterOrEqualTo(nonexistentSize);

    ASSERT_TRUE(result == nullptr);

    free(chunk1);
    free(chunk2);
    free(chunk3);
}

TEST(ChunkTreapTest, BasicFunctions)
{
    using namespace mpp;

    ChunkTreap cTreap;

    Chunk* ch1 = (Chunk*)malloc(64);
    Chunk* ch2 = (Chunk*)malloc(64);
    Chunk* ch3 = (Chunk*)malloc(64);
    Chunk* ch4 = (Chunk*)malloc(64);

    ch1->SetSize(32);
    ch2->SetSize(32);
    ch3->SetSize(32);
    ch4->SetSize(32);

    cTreap.InsertChunk(ch1);
    cTreap.InsertChunk(ch2);
    cTreap.InsertChunk(ch3);
    cTreap.InsertChunk(ch4);

    ASSERT_TRUE((cTreap.MaxSizeChunk()->GetSize() == 32 && cTreap.MinSizeChunk()->GetSize() == 32));

    free(ch1);
    free(ch2);
    free(ch3);
    free(ch4);
}

TEST(ChunkTreapTest, CorrectDelete)
{
    using namespace mpp;

    ChunkTreap cTreap;

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);
    Chunk* ch5 = (Chunk*)malloc(128);

    ch1->SetSize(32);
    ch2->SetSize(64);
    ch3->SetSize(128);
    ch4->SetSize(256);
    ch5->SetSize(512);

    cTreap.InsertChunk(ch1);
    cTreap.InsertChunk(ch2);
    cTreap.InsertChunk(ch3);
    cTreap.InsertChunk(ch4);

    ASSERT_EQ(cTreap.MaxSizeChunk()->GetSize(), 256);
    ASSERT_EQ(cTreap.MinSizeChunk()->GetSize(), 32);
    ASSERT_EQ(cTreap.TotalFreeChunks(), 4);

    ASSERT_TRUE(cTreap.RemoveChunk(ch1));
    ASSERT_TRUE(cTreap.RemoveChunk(ch4));

    ASSERT_EQ(cTreap.MaxSizeChunk()->GetSize(), 128);
    ASSERT_EQ(cTreap.MinSizeChunk()->GetSize(), 64);
    ASSERT_EQ(cTreap.TotalFreeChunks(), 2);

    free(ch1);
    free(ch2);
    free(ch3);
    free(ch4);
    free(ch5);
}

TEST(ChunkTreapTest, DeleteMany)
{
    using namespace mpp;

    ChunkTreap cTreap;

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);

    ch1->SetSize(32);
    ch2->SetSize(32);
    ch3->SetSize(32);
    ch4->SetSize(32);

    cTreap.InsertChunk(ch1);
    cTreap.InsertChunk(ch2);
    cTreap.InsertChunk(ch3);
    cTreap.InsertChunk(ch4);

    cTreap.RemoveChunk(ch2);
    cTreap.RemoveChunk(ch3);

    ASSERT_TRUE((cTreap.MaxSizeChunk()->GetSize() == 32 && cTreap.MinSizeChunk()->GetSize() == 32));

    free(ch1);
    free(ch2);
    free(ch3);
    free(ch4);
}