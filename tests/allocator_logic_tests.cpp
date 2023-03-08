#include "gtest/gtest.h"

#include "gtest_fixtures.hpp"
#include "mpplib/exception.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"

#include <cstring>

TEST_F(AllocatorTest, IterateSimple)
{
    using namespace mpp;

    std::vector<std::size_t> sizes = { 128, 256, 512,  16,  128, 256, 512,  1024,
                                       128, 128, 2048, 128, 128, 128, 16384 }; // NOLINT
    std::vector<void*> ptrs;
    ptrs.reserve(sizes.size());

    for (auto& size : sizes) {
        ptrs.push_back(Allocate(size));
    }

    std::size_t idx = 0;
    for (auto& chunk : *g_memoryManager->GetArenaList()[0]) {
        if ((std::byte*)Chunk::GetNextChunk(&chunk) ==
            g_memoryManager->GetArenaList()[0]->EndPtr()) {
            break;
        }
        ASSERT_EQ(chunk.GetUserData(), ptrs[idx]);
        idx++;
    }
}

TEST_F(AllocatorTest, CtorDtorCalled)
{
    using namespace mpp;

    class UserData
    {
    public:
        int data{ 0 };
        int* ptr{ nullptr };
        UserData(int t_var, int* t_ptr)
            : data(t_var)
            , ptr(t_ptr){};

        ~UserData()
        {
            *ptr = 0;
        };
    };
    int* ptr = new int(1338);
    UserData* uData = Allocate<UserData>(1337, ptr);
    ASSERT_TRUE(uData->data == 1337);
    ASSERT_TRUE(uData->ptr == ptr);
    ASSERT_TRUE(*(uData->ptr) == 1338);

    Deallocate<UserData>(uData);
    ASSERT_TRUE(*ptr == 0);
}

TEST_F(AllocatorTest, NoMemoryException)
{
    using namespace mpp;
    bool flag{ false };

    try {
        Allocate(1UL << 60UL);
    } catch (NoMemoryException& e) {
        flag = true;
    }
    ASSERT_TRUE(flag == true);
}

TEST_F(AllocatorTest, FDT_merge_into_top)
{
    using namespace mpp;

    constexpr std::size_t allocationSize{ 128 };
    constexpr std::size_t alignedAllocationSize{ 160 };

    void* ch1 = Allocate(allocationSize);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    void* ch2 = Allocate(allocationSize);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));
    ASSERT_TRUE(ch1 < ch2);

    EXPECT_TRUE(currentArena->ConstructChunksInUse().size() == 2);
    for (Chunk* chunk : currentArena->ConstructChunksInUse())
        ASSERT_TRUE(chunk->GetSize() == alignedAllocationSize);

    // "Test double-linked list"
    {
        ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
        ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->TopChunk());

        ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->TopChunk()) == Chunk::GetHeaderPtr(ch2));
        ASSERT_TRUE(Chunk::GetPrevChunk(Chunk::GetHeaderPtr(ch2)) == Chunk::GetHeaderPtr(ch1));
    }

    Deallocate(ch1);
    ASSERT_TRUE(
        Chunk::GetUserDataPtr(currentArena->GetFirstGreaterOrEqualToChunk(allocationSize)) == ch1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 0);

    std::size_t beforeMergeTopSize = currentArena->TopChunk()->GetSize();

    Deallocate(ch2);
    ASSERT_TRUE(beforeMergeTopSize + alignedAllocationSize * 2 ==
                currentArena->TopChunk()->GetSize());

    EXPECT_TRUE(currentArena->ConstructChunksInUse(true).empty());
}

TEST_F(AllocatorTest, ADT_merge_into_top)
{
    using namespace mpp;

    void* ch1 = Allocate(128);
    void* ch2 = Allocate(128);

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));
    ASSERT_TRUE(ch1 < ch2);

    Deallocate(ch2);
    ASSERT_TRUE(currentArena->TopChunk()->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->TopChunk()) == Chunk::GetHeaderPtr(ch1));

    ASSERT_TRUE(currentArena->ConstructChunksInUse().size() == 1);
}

TEST_F(AllocatorTest, DT_merge_into_top)
{
    using namespace mpp;

    void* ch1 = Allocate(128);
    ASSERT_TRUE(ch1 != nullptr);

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);
    ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == currentArena->TopChunk());
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    Deallocate(ch1);

    ASSERT_TRUE(currentArena->TopChunk()->IsUsed() == 1);
    ASSERT_TRUE(currentArena->TopChunk()->IsPrevInUse() == 1);

    ASSERT_TRUE(currentArena->ConstructChunksInUse().empty());
}

TEST_F(AllocatorTest, T_merge_into_top)
{
    using namespace mpp;

    void* ch1 = Allocate(128);
    void* ch2 = Allocate(128);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);
    ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->TopChunk())->GetSize() ==
                currentArena->TopChunk()->GetPrevSize());
    std::size_t topChunkSizeBeforeMerging = currentArena->TopChunk()->GetSize();

    Deallocate(ch1);
    Deallocate(ch2);

    ASSERT_TRUE(currentArena->ConstructChunksInUse().empty());
    ASSERT_TRUE(currentArena->TopChunk()->GetSize() == topChunkSizeBeforeMerging + 160 * 2);
}

TEST_F(AllocatorTest, ChunkOfArenaSizeMinusMetadata)
{
    using namespace mpp;

    MemoryManager memMgr = MemoryManager();

    void* ch1 = Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE - sizeof(Chunk::ChunkHeader));

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);

    ASSERT_TRUE(ch1 != nullptr);
    ASSERT_TRUE(currentArena->TopChunk() == nullptr);

    Deallocate(ch1);
    ASSERT_TRUE(currentArena->TopChunk() != nullptr);

    constexpr std::size_t ARENA_SIZE{ MemoryManager::g_DEFAULT_ARENA_SIZE };
    ASSERT_TRUE(currentArena->TopChunk()->GetSize() == ARENA_SIZE);
}

TEST_F(AllocatorTest, ChunkWithDoubleTheArenaSize)
{
    using namespace mpp;

    MemoryManager memMgr = MemoryManager();

    void* ch1 = Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE * 2);

    Arena* currentArena = g_memoryManager->GetArenaList().at(0);

    ASSERT_TRUE(ch1 != nullptr);
    ASSERT_TRUE(currentArena->TopChunk() == nullptr);

    Deallocate(ch1);
    ASSERT_TRUE(currentArena->TopChunk() != nullptr);
    ASSERT_TRUE(currentArena->TopChunk()->GetSize() ==
                MemoryManager::g_DEFAULT_ARENA_SIZE * 2 + 0x1000);
}

TEST_F(AllocatorTest, FDF_deallocated_chunk_amid_freed_chunks)
{
    using namespace mpp;

    MemoryManager memMgr = MemoryManager();

    void* ch1 = Allocate(160);
    void* ch2 = Allocate(160);
    void* ch3 = Allocate(160);
    void* stub = Allocate(1);

    Deallocate(ch1);
    Deallocate(ch3);
    Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 3);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 3);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
}

TEST_F(AllocatorTest, FDA_deallocated_chunk_amid_freed_and_allocated_chunk)
{
    using namespace mpp;

    void* ch1 = Allocate(160);
    void* ch2 = Allocate(160);
    void* ch3 = Allocate(160);

    Deallocate(ch1);
    Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 2);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192 * 2);
}

TEST_F(AllocatorTest, ADF_deallocated_chunk_amid_allocated_and_freed_chunk)
{
    using namespace mpp;

    void* ch1 = Allocate(160);
    void* ch2 = Allocate(160);
    void* ch3 = Allocate(160);
    void* stub = Allocate(1);
    Deallocate(ch3);

    Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192 * 2);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 2);
}

TEST_F(AllocatorTest, ADA_deallocated_chunk_amid_allocated_chunks)
{
    using namespace mpp;

    void* ch1 = Allocate(160);
    void* ch2 = Allocate(160);
    void* ch3 = Allocate(160);
    void* stub = Allocate(1);

    Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192);
}

TEST_F(AllocatorTest, LinkedListChecks)
{
    using namespace mpp;

    void* p1 = Allocate(144);
    void* p2 = Allocate(144);
    void* p3 = Allocate(144);
    void* p4 = Allocate(144);
    void* p5 = Allocate(144);
    void* p6 = Allocate(144);

    Deallocate(p2);
    Deallocate(p4);

    Arena* arena = g_memoryManager->GetArenaByPtr(p1);

    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                           sizeof(Chunk::ChunkHeader) + 160)) ==
                Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                           sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p5));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                           sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p5));

    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p1) -
                                                           sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p1));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p1) -
                                                           sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p1));

    ASSERT_TRUE(GC::FindChunkInUse(p6) == Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                           sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                           sizeof(Chunk::ChunkHeader) - 1)) ==
                Chunk::GetHeaderPtr(p5));
    ASSERT_TRUE(GC::FindChunkInUse(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                           sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p6));
}

TEST_F(AllocatorTest, NewArenaAllocatesChunksCorrectly)
{
    using namespace mpp;

    const std::size_t allocaSize = 65520;
    const std::size_t realChunkSize = MemoryManager::Align(allocaSize + sizeof(Chunk::ChunkHeader),
                                                           MemoryManager::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = MemoryManager::g_DEFAULT_ARENA_SIZE / realChunkSize;

    std::vector<void*> ptrs;
    for (uint32_t i = 0; i < allocationsCount; ++i) {
        ptrs.push_back(Allocate(allocaSize));
    }

    void* newArenaChunk = Allocate(allocaSize);
    Deallocate(newArenaChunk);
}

TEST_F(AllocatorTest, FreeListAllocation)
{
    using namespace mpp;

    void* p1 = Allocate(512);
    void* p2 = Allocate(512);
    void* p3 = Allocate(512);
    void* p4 = Allocate(MM::g_DEFAULT_ARENA_SIZE - 2048);

    Deallocate(p1);
    Deallocate(p2);

    ASSERT_EQ(g_memoryManager->GetArenaList().size(), 1);
    ASSERT_EQ((*g_memoryManager->GetArenaList().begin())->GetFreedChunks().TotalFreeChunks(), 1);
    Chunk* chunkToReturn = nullptr;
    chunkToReturn =
        (*g_memoryManager->GetArenaList().begin())->GetFreedChunks().FirstGreaterOrEqualTo(964);

    void* p5 = Allocate(964);
    ASSERT_EQ(Chunk::GetHeaderPtr(p5), chunkToReturn);
    ASSERT_EQ(g_memoryManager->GetArenaList().size(), 1);
    ASSERT_EQ((*g_memoryManager->GetArenaList().begin())->GetFreedChunks().TotalFreeChunks(), 1);
}

TEST_F(AllocatorTest, FreeListAllocationWithSplit)
{
    using namespace mpp;
    std::stringstream ss;

    void* p1 = Allocate(512);
    void* p2 = Allocate(512);
    void* p3 = Allocate(512);
    void* p4 = Allocate(512);
    void* p5 = Allocate(MM::g_DEFAULT_ARENA_SIZE - 2256);

    Deallocate(p2);
    Deallocate(p3);

    // Visualize heap layout just to check that at least it doesn't segfault 🤷
    g_memoryManager->VisHeapLayout(ss, nullptr);

    ASSERT_EQ(g_memoryManager->GetArenaList().size(), 1);
    ASSERT_EQ((*g_memoryManager->GetArenaList().begin())->GetFreedChunks().TotalFreeChunks(), 1);
    Chunk* chunkToReturn = nullptr;
    chunkToReturn =
        (*g_memoryManager->GetArenaList().begin())->GetFreedChunks().FirstGreaterOrEqualTo(964);

    void* p6 = Allocate(750);
    ASSERT_EQ(Chunk::GetHeaderPtr(p6), chunkToReturn);
    ASSERT_EQ(g_memoryManager->GetArenaList().size(), 1);
    ASSERT_EQ((*g_memoryManager->GetArenaList().begin())->GetFreedChunks().TotalFreeChunks(), 1);

    // Trigger code at arena.cpp:142
    Deallocate(p1);

    chunkToReturn =
        (*g_memoryManager->GetArenaList().begin())->GetFreedChunks().FirstGreaterOrEqualTo(520);
    void* p7 = Allocate(520);
    ASSERT_EQ(Chunk::GetHeaderPtr(p7), chunkToReturn);

    // Dump arena just to check that at least it doesn't segfault 🤷
    Arena::DumpArena(ss, *g_memoryManager->GetArenaList().begin(), true, true);
}

/* For ctrl+c, ctrl-V
TEST_F(AllocatorTest, "")
{
    using namespace mpp;
}
*/