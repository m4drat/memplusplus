#include "catch2/catch.hpp"

#include "mpplib/memory_allocator.hpp"
#include "mpplib/exception.hpp"
#include <cstring>

TEST_CASE("Test, that destructor/constructor gets called")
{
    using namespace mpp;

    class UserData
    {
    public:
        int data {0};
        int* ptr { nullptr };
        UserData(int t_var, int* t_ptr) :
            data(t_var), ptr(t_ptr)
        {};

        ~UserData()
        {
            *ptr = 0;
        };
    };
    int* ptr = new int(1488);
    UserData* uData = MemoryAllocator::Allocate<UserData>(1337, ptr);
    REQUIRE(uData->data == 1337);
    REQUIRE(uData->ptr == ptr);
    REQUIRE(*(uData->ptr) == 1488);

    MemoryAllocator::Deallocate<UserData>(uData);
    REQUIRE(*ptr == 0);
}

TEST_CASE("Test for no memory exception")
{
    using namespace mpp;
    bool flag {false};
    try 
    {
        MemoryAllocator::Allocate(1UL << 60UL);
    } catch (NoMemoryException& e)
    {
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

    void* ch1 = MemoryAllocator::Allocate(allocationSize);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    
    void* ch2 = MemoryAllocator::Allocate(allocationSize);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    
    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    
    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    REQUIRE(currentArena->chunksInUse.size() == 2);
    for (Chunk* chunk : currentArena->chunksInUse)
        REQUIRE(chunk->GetSize() == alignedAllocationSize);
    
    SECTION("Test double-linked list") {
        REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
        REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->topChunk);
        
        REQUIRE(Chunk::GetPrevChunk(currentArena->topChunk)   == Chunk::GetHeaderPtr(ch2));
        REQUIRE(Chunk::GetPrevChunk(Chunk::GetHeaderPtr(ch2)) == Chunk::GetHeaderPtr(ch1));
    }
    
    MemoryAllocator::Deallocate(ch1);
    REQUIRE(Chunk::GetUserDataPtr(currentArena->GetFirstGreaterOrEqualThanChunk(allocationSize)) == ch1);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 0);
    
    std::size_t beforeMergeTopSize = currentArena->topChunk->GetSize();

    MemoryAllocator::Deallocate(ch2);
    REQUIRE(beforeMergeTopSize + alignedAllocationSize * 2 == currentArena->topChunk->GetSize());
    REQUIRE(currentArena->chunksInUse.size() == 0);
}

TEST_CASE("ADT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    MemoryAllocator::Deallocate(ch2);
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

    void* ch1 = MemoryAllocator::Allocate(128);
    REQUIRE(ch1 != nullptr);
    
    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == currentArena->topChunk);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);

    MemoryAllocator::Deallocate(ch1);

    REQUIRE(currentArena->topChunk->IsUsed() == 1);
    REQUIRE(currentArena->topChunk->IsPrevInUse() == 1);

    REQUIRE(currentArena->chunksInUse.size() == 0);
}

TEST_CASE("T - Merging into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    
    REQUIRE((ch1 != nullptr && ch2 != nullptr));

    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    REQUIRE(Chunk::GetPrevChunk(currentArena->topChunk)->GetSize() == currentArena->topChunk->GetPrevSize());
    std::size_t topChhunkSizeBeforeMerging = currentArena->topChunk->GetSize();

    MemoryAllocator::Deallocate(ch1);
    MemoryAllocator::Deallocate(ch2);

    REQUIRE(currentArena->chunksInUse.size() == 0);
    REQUIRE(currentArena->topChunk->GetSize() == topChhunkSizeBeforeMerging + 160 * 2);
}

TEST_CASE("Allocating chunk exactly of size (g_DEFAULT_ARENA_SIZE - sizeof(metadata))")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE - sizeof(Chunk::ChunkHeader));
    
    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    
    REQUIRE(ch1 != nullptr);
    REQUIRE(currentArena->topChunk == nullptr);

    MemoryAllocator::Deallocate(ch1);
    REQUIRE(currentArena->topChunk != nullptr);
    
    constexpr std::size_t ARENA_SIZE{ MemoryManager::g_DEFAULT_ARENA_SIZE };
    REQUIRE(currentArena->topChunk->GetSize() == ARENA_SIZE);
}

TEST_CASE("Allocating chunk of size g_DEFAULT_ARENA_SIZE * 2")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE * 2);

    Arena* currentArena = MemoryManager::GetArenaList().at(0);

    REQUIRE(ch1 != nullptr);
    REQUIRE(currentArena->topChunk == nullptr);

    MemoryAllocator::Deallocate(ch1);
    REQUIRE(currentArena->topChunk != nullptr);
    REQUIRE(currentArena->topChunk->GetSize() == MemoryManager::g_DEFAULT_ARENA_SIZE * 2 + 0x1000);
}

// FIXME
TEST_CASE("FDF - Chunk that we deallocate located between two freed chunks")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(160);
    void* ch2 = MemoryAllocator::Allocate(160);
    void* ch3 = MemoryAllocator::Allocate(160);
    void* stub = MemoryAllocator::Allocate(1);
    
    MemoryAllocator::Deallocate(ch1);
    MemoryAllocator::Deallocate(ch3);
    MemoryAllocator::Deallocate(ch2);
    
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192*3); 
    REQUIRE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192*3);
    REQUIRE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
}

// FIXME
TEST_CASE("FDA - Chunk that we deallocate located between freed and used chunk")
{
    using namespace mpp;
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(160);
    void* ch2 = MemoryAllocator::Allocate(160);
    void* ch3 = MemoryAllocator::Allocate(160);

    MemoryAllocator::Deallocate(ch1);

    MemoryAllocator::Deallocate(ch2);

    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch1)->GetSize() == 192*2);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192*2);
}

TEST_CASE("ADF - Chunk that we deallocate located between used and freed chunk")
{
    using namespace mpp;
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(160);
    void* ch2 = MemoryAllocator::Allocate(160);
    void* ch3 = MemoryAllocator::Allocate(160);
    void* stub = MemoryAllocator::Allocate(1);
    MemoryAllocator::Deallocate(ch3);

    MemoryAllocator::Deallocate(ch2);
    
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(stub)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192*2);
    REQUIRE(Chunk::GetHeaderPtr(stub)->GetPrevSize() == 192*2);
    
}

// FIXME
TEST_CASE("ADA - Chunk that we deallocate located between two used chunks")
{
    using namespace mpp;    
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(160);
    void* ch2 = MemoryAllocator::Allocate(160);
    void* ch3 = MemoryAllocator::Allocate(160);
    void* stub = MemoryAllocator::Allocate(1);
    
    MemoryAllocator::Deallocate(ch2);

    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsUsed() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->IsPrevInUse() == 1);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->IsPrevInUse() == 0);
    REQUIRE(Chunk::GetHeaderPtr(ch2)->GetSize() == 192);
    REQUIRE(Chunk::GetHeaderPtr(ch3)->GetPrevSize() == 192);
    
}
/* For ctrl+c, ctrl-V
TEST_CASE("")
{
    using namespace mpp;
}
*/