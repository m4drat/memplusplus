#include "gtest/gtest.h"

#include "mpplib/exception.hpp"
#include "mpplib/memory_manager.hpp"
#include <cstring>

TEST(AllocatorLogicTest, CtorDtorCalled)
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
    UserData* uData = MemoryManager::Allocate<UserData>(1337, ptr);
    ASSERT_TRUE(uData->data == 1337);
    ASSERT_TRUE(uData->ptr == ptr);
    ASSERT_TRUE(*(uData->ptr) == 1338);

    MemoryManager::Deallocate<UserData>(uData);
    ASSERT_TRUE(*ptr == 0);
}

TEST(AllocatorLogicTest, NoMemoryException)
{
    using namespace mpp;
    bool flag{ false };
    try {
        MemoryManager::Allocate(1UL << 60UL);
    } catch (NoMemoryException& e) {
        flag = true;
    }
    ASSERT_TRUE(flag == true);
}

TEST(AllocatorLogicTest, FDT_merge_into_top)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    constexpr std::size_t allocationSize{ 128 };
    constexpr std::size_t alignedAllocationSize{ 160 };

    void* ch1 = MemoryManager::Allocate(allocationSize);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    void* ch2 = MemoryManager::Allocate(allocationSize);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));
    ASSERT_TRUE(ch1 < ch2);

    ASSERT_TRUE(currentArena->chunksInUse.size() == 2);
    for (Chunk* chunk : currentArena->chunksInUse)
        ASSERT_TRUE(chunk->GetSize() == alignedAllocationSize);

    // "Test double-linked list"
    {
        ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
        ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->topChunk);

        ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->topChunk) == Chunk::GetHeaderPtr(ch2));
        ASSERT_TRUE(Chunk::GetPrevChunk(Chunk::GetHeaderPtr(ch2)) == Chunk::GetHeaderPtr(ch1));
    }

    MemoryManager::Deallocate(ch1);
    ASSERT_TRUE(
        Chunk::GetUserDataPtr(currentArena->GetFirstGreaterOrEqualToChunk(allocationSize)) == ch1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 0);

    std::size_t beforeMergeTopSize = currentArena->topChunk->GetSize();

    MemoryManager::Deallocate(ch2);
    ASSERT_TRUE(beforeMergeTopSize + alignedAllocationSize * 2 ==
                currentArena->topChunk->GetSize());
    ASSERT_TRUE(currentArena->chunksInUse.size() == 0);
}

TEST(AllocatorLogicTest, ADT_merge_into_top)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    void* ch2 = MemoryManager::Allocate(128);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));
    ASSERT_TRUE(ch1 < ch2);

    MemoryManager::Deallocate(ch2);
    ASSERT_TRUE(currentArena->topChunk->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->topChunk) == Chunk::GetHeaderPtr(ch1));

    ASSERT_TRUE(currentArena->chunksInUse.size() == 1);
}

TEST(AllocatorLogicTest, DT_merge_into_top)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    ASSERT_TRUE(ch1 != nullptr);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    ASSERT_TRUE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == currentArena->topChunk);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    MemoryManager::Deallocate(ch1);

    ASSERT_TRUE(currentArena->topChunk->IsUsed() == 1);
    ASSERT_TRUE(currentArena->topChunk->IsPrevInUse() == 1);

    ASSERT_TRUE(currentArena->chunksInUse.size() == 0);
}

TEST(AllocatorLogicTest, T_merge_into_top)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    void* ch2 = MemoryManager::Allocate(128);

    ASSERT_TRUE((ch1 != nullptr && ch2 != nullptr));

    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    ASSERT_TRUE(Chunk::GetPrevChunk(currentArena->topChunk)->GetSize() ==
                currentArena->topChunk->GetPrevSize());
    std::size_t topChunkSizeBeforeMerging = currentArena->topChunk->GetSize();

    MemoryManager::Deallocate(ch1);
    MemoryManager::Deallocate(ch2);

    ASSERT_TRUE(currentArena->chunksInUse.size() == 0);
    ASSERT_TRUE(currentArena->topChunk->GetSize() == topChunkSizeBeforeMerging + 160 * 2);
}

TEST(AllocatorLogicTest, ChunkOfArenaSizeMinusMetadata)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 =
        MemoryManager::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE - sizeof(Chunk::ChunkHeader));

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    ASSERT_TRUE(ch1 != nullptr);
    ASSERT_TRUE(currentArena->topChunk == nullptr);

    MemoryManager::Deallocate(ch1);
    ASSERT_TRUE(currentArena->topChunk != nullptr);

    constexpr std::size_t ARENA_SIZE{ MemoryManager::g_DEFAULT_ARENA_SIZE };
    ASSERT_TRUE(currentArena->topChunk->GetSize() == ARENA_SIZE);
}

TEST(AllocatorLogicTest, ChunkWithDoubleTheArenaSize)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE * 2);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    ASSERT_TRUE(ch1 != nullptr);
    ASSERT_TRUE(currentArena->topChunk == nullptr);

    MemoryManager::Deallocate(ch1);
    ASSERT_TRUE(currentArena->topChunk != nullptr);
    ASSERT_TRUE(currentArena->topChunk->GetSize() ==
                MemoryManager::g_DEFAULT_ARENA_SIZE * 2 + 0x1000);
}

TEST(AllocatorLogicTest, FDF_deallocated_chunk_amid_freed_chunks)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);
    void* stub = MemoryManager::Allocate(1);

    MemoryManager::Deallocate(ch1);
    MemoryManager::Deallocate(ch3);
    MemoryManager::Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 3);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 3);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
}

TEST(AllocatorLogicTest, FDA_deallocated_chunk_amid_freed_and_allocated_chunk)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);

    MemoryManager::Deallocate(ch1);
    MemoryManager::Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 2);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192 * 2);
}

TEST(AllocatorLogicTest, ADF_deallocated_chunk_amid_allocated_and_freed_chunk)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);
    void* stub = MemoryManager::Allocate(1);
    MemoryManager::Deallocate(ch3);

    MemoryManager::Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192 * 2);
    ASSERT_TRUE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 2);
}

TEST(AllocatorLogicTest, ADA_deallocated_chunk_amid_allocated_chunks)
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);
    void* stub = MemoryManager::Allocate(1);

    MemoryManager::Deallocate(ch2);

    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192);
    ASSERT_TRUE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192);
}

TEST(AllocatorLogicTest, LinkedListChecks)
{
    using namespace mpp;

    void* p1 = MemoryManager::Allocate(144);
    void* p2 = MemoryManager::Allocate(144);
    void* p3 = MemoryManager::Allocate(144);
    void* p4 = MemoryManager::Allocate(144);
    void* p5 = MemoryManager::Allocate(144);
    void* p6 = MemoryManager::Allocate(144);

    MemoryManager::Deallocate(p2);
    MemoryManager::Deallocate(p4);

    Arena* arena = MemoryManager::GetArenaByPtr(p1);

    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p5) - sizeof(Chunk::ChunkHeader) + 160)) ==
                Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p5) - sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p5));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p5) - sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p5));

    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p1) - sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p1));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p1) - sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p1));

    ASSERT_TRUE(arena->GetInUseChunkByPtr(p6) == Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p6) - sizeof(Chunk::ChunkHeader))) ==
                Chunk::GetHeaderPtr(p6));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p6) - sizeof(Chunk::ChunkHeader) - 1)) ==
                Chunk::GetHeaderPtr(p5));
    ASSERT_TRUE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(p6) - sizeof(Chunk::ChunkHeader) + 159)) ==
                Chunk::GetHeaderPtr(p6));
}

TEST(AllocatorLogicTest, NewArenaAllocatesChunksCorrectly)
{
    using namespace mpp;

    const std::size_t allocaSize = 65520;
    const std::size_t realChunkSize = MemoryManager::Align(allocaSize + sizeof(Chunk::ChunkHeader),
                                                           MemoryManager::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = MemoryManager::g_DEFAULT_ARENA_SIZE / realChunkSize;

    std::vector<void*> ptrs;
    for (uint32_t i = 0; i < allocationsCount; ++i) {
        ptrs.push_back(MemoryManager::Allocate(allocaSize));
    }

    void* newArenaChunk = MemoryManager::Allocate(allocaSize);
    MemoryManager::Deallocate(newArenaChunk);
}

TEST(AllocatorLogicTest, FreeListAllocation)
{
    using namespace mpp;

    MM::ResetAllocatorState();
    void* p1 = MM::Allocate(512);
    void* p2 = MM::Allocate(512);
    void* p3 = MM::Allocate(512);
    void* p4 = MM::Allocate(MM::g_DEFAULT_ARENA_SIZE - 2048);

    MM::Deallocate(p1);
    MM::Deallocate(p2);

    ASSERT_EQ(MM::GetArenaList().size(), 1);
    ASSERT_EQ((*MM::GetArenaList().begin())->freedChunks.TotalFreeChunks(), 1);
    Chunk* chunkToReturn = nullptr;
    chunkToReturn = (*MM::GetArenaList().begin())->freedChunks.FirstGreaterOrEqualTo(964);

    void* p5 = MemoryManager::Allocate(964);
    ASSERT_EQ(Chunk::GetHeaderPtr(p5), chunkToReturn);
    ASSERT_EQ(MM::GetArenaList().size(), 1);
    ASSERT_EQ((*MM::GetArenaList().begin())->freedChunks.TotalFreeChunks(), 1);
}

TEST(AllocatorLogicTest, FreeListAllocationWithSplit)
{
    using namespace mpp;
    std::stringstream ss;

    MM::ResetAllocatorState();
    void* p1 = MM::Allocate(512);
    void* p2 = MM::Allocate(512);
    void* p3 = MM::Allocate(512);
    void* p4 = MM::Allocate(512);
    void* p5 = MM::Allocate(MM::g_DEFAULT_ARENA_SIZE - 2256);

    MM::Deallocate(p2);
    MM::Deallocate(p3);

    // Visualize heap layout just to check that at least it doesn't segfault 🤷
    MM::VisHeapLayout(ss, nullptr);

    ASSERT_EQ(MM::GetArenaList().size(), 1);
    ASSERT_EQ((*MM::GetArenaList().begin())->freedChunks.TotalFreeChunks(), 1);
    Chunk* chunkToReturn = nullptr;
    chunkToReturn = (*MM::GetArenaList().begin())->freedChunks.FirstGreaterOrEqualTo(964);

    void* p6 = MemoryManager::Allocate(750);
    ASSERT_EQ(Chunk::GetHeaderPtr(p6), chunkToReturn);
    ASSERT_EQ(MM::GetArenaList().size(), 1);
    ASSERT_EQ((*MM::GetArenaList().begin())->freedChunks.TotalFreeChunks(), 1);

    // Trigger code at arena.cpp:142
    MM::Deallocate(p1);

    chunkToReturn = (*MM::GetArenaList().begin())->freedChunks.FirstGreaterOrEqualTo(520);
    void* p7 = MemoryManager::Allocate(520);
    ASSERT_EQ(Chunk::GetHeaderPtr(p7), chunkToReturn);

    // Dump arena just to check that at least it doesn't segfault 🤷
    Arena::DumpArena(ss, *MM::GetArenaList().begin(), true, true);
}

/* For ctrl+c, ctrl-V
TEST(AllocatorLogicTest, "")
{
    using namespace mpp;
}
*/