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

/*
General case:
    FDF
    FDA
    ADF
    ADA

Starting case:
    DA
    DF

Top case:
    FDT
    ADT
    DT
    T
*/

TEST_CASE("FDT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    
    Arena* currentArena = MemoryManager::GetArenaList().at(0);
    
    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    REQUIRE(currentArena->chunksInUse.size() == 2);
    for (Chunk* chunk : currentArena->chunksInUse)
        REQUIRE(chunk->GetSize() == 160);
    REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch1)) == Chunk::GetHeaderPtr(ch2));
    REQUIRE(Chunk::GetNextChunk(Chunk::GetHeaderPtr(ch2)) == currentArena->topChunk);

    MemoryAllocator::Deallocate(ch1);
    MemoryAllocator::Deallocate(ch2);
}

TEST_CASE("ADT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);

    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    REQUIRE(ch1 < ch2);

    MemoryAllocator::Deallocate(ch2);
}

TEST_CASE("DT - Merge into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    REQUIRE(ch1 != nullptr);
    
    MemoryAllocator::Deallocate(ch1);
}

TEST_CASE("T - Merging into top")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    
    REQUIRE((ch1 != nullptr && ch2 != nullptr));
    
    MemoryAllocator::Deallocate(ch1);
    MemoryAllocator::Deallocate(ch2);
}

TEST_CASE("Allocating chunk exactly of size (g_DEFAULT_ARENA_SIZE - sizeof(metadata))")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE - sizeof(Chunk::ChunkHeader));
    REQUIRE(ch1 != nullptr);

    MemoryAllocator::Deallocate(ch1);
}

TEST_CASE("Allocating chunk of size g_DEFAULT_ARENA_SIZE * 2")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(MemoryManager::g_DEFAULT_ARENA_SIZE * 2);
    REQUIRE(ch1 != nullptr);

    MemoryAllocator::Deallocate(ch1);
}

TEST_CASE("FDF - Chunk that we deallocate located between two freed chunks")
{
    using namespace mpp;

    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    void* ch3 = MemoryAllocator::Allocate(128);
    void* ch4 = MemoryAllocator::Allocate(128);
    
    MemoryAllocator::Deallocate(ch1);
    MemoryAllocator::Deallocate(ch3);
    MemoryAllocator::Deallocate(ch2);
    
    void* ch5 = MemoryAllocator::Allocate((128 + 16)*3);
    
    void* endOfCh5 = (void*)((size_t)ch5 + 128*3 + 16);
    void* begOfCh4 = Chunk::GetHeaderPtr(ch4);
    REQUIRE(endOfCh5 == begOfCh4);
}

TEST_CASE("FDA - Chunk that we deallocate located between freed and used chunk")
{
    using namespace mpp;
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    void* ch3 = MemoryAllocator::Allocate(128);
    MemoryAllocator::Deallocate(ch1);

    MemoryAllocator::Deallocate(ch2);
    void* ch4 = MemoryAllocator::Allocate(128*2);

    void* endOfCh4 = (void*)((size_t)ch4 + 128*3 + 16);
    void* begOfCh3 = Chunk::GetHeaderPtr(ch3);
    REQUIRE(endOfCh4 == begOfCh3);
}

TEST_CASE("ADF - Chunk that we deallocate located between used and freed chunk")
{
    using namespace mpp;
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    void* ch3 = MemoryAllocator::Allocate(128);
    MemoryAllocator::Deallocate(ch3);

    MemoryAllocator::Deallocate(ch2);
    void* ch4 = MemoryAllocator::Allocate(128*2);

    void* endOfCh1 = (void*)((size_t)ch1 + 128 + 16);
    void* begOfCh4 = Chunk::GetHeaderPtr(ch4);
    REQUIRE(endOfCh1 == begOfCh4);
}

TEST_CASE("ADA - Chunk that we deallocate located between two used chunks")
{
    using namespace mpp;    
    
    MemoryManager::ResetAllocatorState();

    void* ch1 = MemoryAllocator::Allocate(128);
    void* ch2 = MemoryAllocator::Allocate(128);
    void* ch3 = MemoryAllocator::Allocate(128);
    
    MemoryAllocator::Deallocate(ch2);
    void* ch4 = MemoryAllocator::Allocate(128);
    
    void* endOfCh4 = (void*)((size_t)ch4 + 128 + 16);
    void* begOfCh4 = Chunk::GetHeaderPtr(ch4);
    void* begOfCh3 = Chunk::GetHeaderPtr(ch3);
    void* endOfCh1 = (void*)((size_t)ch1 + 128 + 16);
    REQUIRE((endOfCh1 == begOfCh4 && endOfCh4 == begOfCh3));
}
/*
TEST_CASE("")
{
    using namespace mpp;
}

TEST_CASE("")
{
    using namespace mpp;
}
*/