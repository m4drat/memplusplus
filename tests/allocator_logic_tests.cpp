#include <catch2/catch_all.hpp>

#include "mpplib/exception.hpp"
#include "mpplib/memory_manager.hpp"
#include <cstring>

TEST_CASE("Test, that destructor/constructor gets called")
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
    int* ptr = new int(1488);
    UserData* uData = MemoryManager::Allocate<UserData>(1337, ptr);
    REQUIRE(uData->data == 1337);
    REQUIRE(uData->ptr == ptr);
    REQUIRE(*(uData->ptr) == 1488);

    MemoryManager::Deallocate<UserData>(uData);
    REQUIRE(*ptr == 0);
}

TEST_CASE("Test for no memory exception")
{
    using namespace mpp;
    bool flag{ false };
    try {
        MemoryManager::Allocate(1UL << 60UL);
    } catch (NoMemoryException& e) {
        flag = true;
    }
    REQUIRE(flag == true);
}

TEST_CASE("FDT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    constexpr std::size_t allocationSize{ 128 };
    constexpr std::size_t alignedAllocationSize{ 160 };

    void* ch1 = MemoryManager::Allocate(allocationSize);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    void* ch2 = MemoryManager::Allocate(allocationSize);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    REQUIRE(currentArena->chunksInUse.size() == 2);
    for (Chunk* chunk : currentArena->chunksInUse)
        REQUIRE(chunk->GetSize() == alignedAllocationSize);

    SECTION("Test double-linked list")
    {
        REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
        REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->topChunk);

        REQUIRE(Chunk::GetPrevChunk(currentArena->topChunk) == Chunk::GetHeaderPtr(ch2));
        REQUIRE(Chunk::GetPrevChunk(Chunk::GetHeaderPtr(ch2)) == Chunk::GetHeaderPtr(ch1));
    }

    MemoryManager::Deallocate(ch1);
    REQUIRE(Chunk::GetUserDataPtr(currentArena->GetFirstGreaterOrEqualThanChunk(allocationSize)) ==
            ch1);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 0);

    std::size_t beforeMergeTopSize = currentArena->topChunk->GetSize();

    MemoryManager::Deallocate(ch2);
    REQUIRE(beforeMergeTopSize + alignedAllocationSize * 2 == currentArena->topChunk->GetSize());
    REQUIRE(currentArena->chunksInUse.size() == 0);
}

TEST_CASE("ADT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    void* ch2 = MemoryManager::Allocate(128);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    MemoryManager::Deallocate(ch2);
    REQUIRE(currentArena->topChunk->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    REQUIRE(Chunk::GetPrevChunk(currentArena->topChunk) == Chunk::GetHeaderPtr(ch1));

    REQUIRE(currentArena->chunksInUse.size() == 1);
}

TEST_CASE("DT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    REQUIRE(ch1 != nullptr);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == currentArena->topChunk);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    MemoryManager::Deallocate(ch1);

    REQUIRE(currentArena->topChunk->IsUsed() == 1);
    REQUIRE(currentArena->topChunk->IsPrevInUse() == 1);

    REQUIRE(currentArena->chunksInUse.size() == 0);
}

TEST_CASE("T - Merging into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(128);
    void* ch2 = MemoryManager::Allocate(128);

    REQUIRE((ch1 != nullptr && ch2 != nullptr));

    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    REQUIRE(Chunk::GetPrevChunk(currentArena->topChunk)->GetSize() ==
            currentArena->topChunk->GetPrevSize());
    std::size_t topChhunkSizeBeforeMerging = currentArena->topChunk->GetSize();

    MemoryManager::Deallocate(ch1);
    MemoryManager::Deallocate(ch2);

    REQUIRE(currentArena->chunksInUse.size() == 0);
    REQUIRE(currentArena->topChunk->GetSize() == topChhunkSizeBeforeMerging + 160 * 2);
}

TEST_CASE("Allocating chunk exactly of size (g_DEFAULT_ARENA_SIZE - sizeof(metadata))")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 =
        MemoryManager::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE - sizeof(Chunk::ChunkHeader));

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE(ch1 != nullptr);
    REQUIRE(currentArena->topChunk == nullptr);

    MemoryManager::Deallocate(ch1);
    REQUIRE(currentArena->topChunk != nullptr);

    constexpr std::size_t ARENA_SIZE{ MemoryManager::g_DEFAULT_ARENA_SIZE };
    REQUIRE(currentArena->topChunk->GetSize() == ARENA_SIZE);
}

TEST_CASE("Allocating chunk of size g_DEFAULT_ARENA_SIZE * 2")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE * 2);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE(ch1 != nullptr);
    REQUIRE(currentArena->topChunk == nullptr);

    MemoryManager::Deallocate(ch1);
    REQUIRE(currentArena->topChunk != nullptr);
    REQUIRE(currentArena->topChunk->GetSize() == MemoryManager::g_DEFAULT_ARENA_SIZE * 2 + 0x1000);
}

TEST_CASE("FDF - Chunk that we deallocate located between two freed chunks")
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

    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 3);
    REQUIRE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 3);
    REQUIRE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
}

TEST_CASE("FDA - Chunk that we deallocate located between freed and used chunk")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);

    MemoryManager::Deallocate(ch1);
    MemoryManager::Deallocate(ch2);

    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192 * 2);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192 * 2);
}

TEST_CASE("ADF - Chunk that we deallocate located between used and freed chunk")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);
    void* stub = MemoryManager::Allocate(1);
    MemoryManager::Deallocate(ch3);

    MemoryManager::Deallocate(ch2);

    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192 * 2);
    REQUIRE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192 * 2);
}

TEST_CASE("ADA - Chunk that we deallocate located between two used chunks")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryManager::Allocate(160);
    void* ch2 = MemoryManager::Allocate(160);
    void* ch3 = MemoryManager::Allocate(160);
    void* stub = MemoryManager::Allocate(1);

    MemoryManager::Deallocate(ch2);

    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192);
}

TEST_CASE("Linked list checks")
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

    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                              sizeof(Chunk::ChunkHeader) + 160)) ==
            Chunk::GetHeaderPtr(p6));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                              sizeof(Chunk::ChunkHeader))) ==
            Chunk::GetHeaderPtr(p5));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p5) -
                                                              sizeof(Chunk::ChunkHeader) + 159)) ==
            Chunk::GetHeaderPtr(p5));

    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p1) -
                                                              sizeof(Chunk::ChunkHeader))) ==
            Chunk::GetHeaderPtr(p1));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p1) -
                                                              sizeof(Chunk::ChunkHeader) + 159)) ==
            Chunk::GetHeaderPtr(p1));

    REQUIRE(arena->GetInUseChunkByPtr(p6) == Chunk::GetHeaderPtr(p6));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                              sizeof(Chunk::ChunkHeader))) ==
            Chunk::GetHeaderPtr(p6));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                              sizeof(Chunk::ChunkHeader) - 1)) ==
            Chunk::GetHeaderPtr(p5));
    REQUIRE(arena->GetInUseChunkByPtr(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p6) -
                                                              sizeof(Chunk::ChunkHeader) + 159)) ==
            Chunk::GetHeaderPtr(p6));
}

TEST_CASE("Check that new arena alloacate chunks correctly")
{
    using namespace mpp;

    const std::size_t allocaSize = 65520;
    const std::size_t realChunkSize = MemoryManager::Align(
        allocaSize + sizeof(Chunk::ChunkHeader), MemoryManager::g_MIN_CHUNK_SIZE);
    const std::size_t allocationsCount = MemoryManager::g_DEFAULT_ARENA_SIZE / realChunkSize;

    std::vector<void*> ptrs;
    for (uint32_t i = 0; i < allocationsCount; ++i) {
        ptrs.push_back(MemoryManager::Allocate(allocaSize));
    }

    void* newArenaChunk = MemoryManager::Allocate(allocaSize);
    MemoryManager::Deallocate(newArenaChunk);
}

/* For ctrl+c, ctrl-V
TEST_CASE("")
{
    using namespace mpp;
}
*/