#include "mpplib/memory_allocator.hpp"
#include "mpplib/exception.hpp"
#include "mpplib/utils/utils.hpp"

#include <sys/mman.h>

namespace mpp {

std::size_t MemoryAllocator::Align(std::size_t t_size, int32_t t_alignment)
{
    PROFILE_FUNCTION();

    if (t_size != 0 && (t_size % t_alignment == 0))
        return t_size;
    return t_size + (t_alignment - (t_size % t_alignment));
}

void* MemoryAllocator::SysAlloc(std::size_t t_size)
{
    PROFILE_FUNCTION();

    void* rawPtr = mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (rawPtr == MAP_FAILED) {

    // If we are using fuzzer just ignore out-of-memory errors and exit 
#if MPP_FUZZER_INSECURE == 1
        exit(0);
#else
        throw NoMemoryException();
#endif
    }

    return rawPtr;
}

bool MemoryAllocator::SysDealloc(void* t_ptr, std::size_t t_pageSize)
{
    PROFILE_FUNCTION();

    if (munmap(t_ptr, t_pageSize) == -1) {
        throw UnmapMemoryException();
    }

    return true;
}

Arena* MemoryAllocator::CreateArena(std::size_t t_arenaSize)
{
    PROFILE_FUNCTION();

    // Allocate memory for arena
    void* arenaSpace = SysAlloc(t_arenaSize);

    // TODO - smart pointers memory managment
    Arena* arena = new Arena(t_arenaSize, arenaSpace);

    // Add newly created arena to vector of active arenas
    s_ArenaList.push_back(arena);

    return arena;
}

Chunk* MemoryAllocator::GetSuitableChunk(std::size_t t_realSize)
{
    PROFILE_FUNCTION();

    // Try iterating through all available arenas
    // to try to find enought space for user-requested chunk
    // in top chunk
    for (auto* arena : s_ArenaList) {
        // check if arena->topChunk != nullptr, in this case, we still have
        // some space in the right side
        if (arena->topChunk && (t_realSize <= arena->topChunk->GetSize())) {
            Chunk* chunkToReturn = arena->AllocateFromTopChunk(t_realSize);
#if MPP_STATS == 1
            if (chunkToReturn->GetSize() > arena->m_ArenaStats->biggestAllocation) {
                arena->m_ArenaStats->biggestAllocation = chunkToReturn->GetSize();
            }
            if (chunkToReturn->GetSize() < arena->m_ArenaStats->smallestAllocation) {
                arena->m_ArenaStats->smallestAllocation = chunkToReturn->GetSize();
            }
#endif
            return chunkToReturn;
        }
    }

    // If we cant find arena with enough right space (aka topchunk size),
    // we will iterate through ChunkTreap to find chunk to reuse
    for (Arena* arena : s_ArenaList) {
        Chunk* chunk = arena->GetFirstGreaterOrEqualThanChunk(t_realSize);
        if (chunk == nullptr) {
            continue;
        }
        Chunk* chunkToReturn = arena->AllocateFromFreeList(chunk, t_realSize);
#if MPP_STATS == 1
        if (chunkToReturn->GetSize() > arena->m_ArenaStats->biggestAllocation) {
            arena->m_ArenaStats->biggestAllocation = chunkToReturn->GetSize();
        }
        if (chunkToReturn->GetSize() < arena->m_ArenaStats->smallestAllocation) {
            arena->m_ArenaStats->smallestAllocation = chunkToReturn->GetSize();
        }
#endif
        return chunkToReturn;
    }

    // If we still cant find chunk, we will return nullptr
    // to show that we dont have arena, to allocate from
    return nullptr;
}

void* MemoryAllocator::AllocateBigChunk(std::size_t t_userDataSize)
{
    PROFILE_FUNCTION();

    // Create new arena with requested size
    Arena* arena = CreateArena(t_userDataSize);
#if MPP_STATS == 1
    arena->m_ArenaStats->bigArena = true;
#endif

    // Allocate chunk from right space of that arena
    Chunk* bigChungus = arena->AllocateFromTopChunk(t_userDataSize);
    return Chunk::GetUserDataPtr(bigChungus);
}

void* MemoryAllocator::Allocate(std::size_t t_userDataSize)
{
    PROFILE_FUNCTION();
    
    // Align, because we want to have metadata bits
    std::size_t realChunkSize =
      Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_MIN_CHUNK_SIZE);

    // If allocation size is bigger than default arena size
    // we will allocate new arena with chunk, which size is
    // equal to requested size, aligned to g_PAGE_SIZE
    if (realChunkSize > g_DEFAULT_ARENA_SIZE) {
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
        void* bigChunk = AllocateBigChunk(Align(realChunkSize, g_PAGE_SIZE));
        std::memset(bigChunk, g_FILL_CHAR, Align(realChunkSize, g_PAGE_SIZE) - sizeof(Chunk::ChunkHeader));
        return bigChunk;
#else
        return AllocateBigChunk(Align(realChunkSize, g_PAGE_SIZE));
#endif
    }

    // If we dont have active arenas yet
    // we will create new one
    if (s_ArenaList.empty()) {
        CreateArena(g_DEFAULT_ARENA_SIZE);
    }

    // Try to get chunk from any suitable arena (by searching in free list
    // or by splitting top chunk)
    Chunk* chunk = GetSuitableChunk(realChunkSize);
    if (chunk != nullptr) {
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
        std::memset(Chunk::GetUserDataPtr(chunk), g_FILL_CHAR, realChunkSize - sizeof(Chunk::ChunkHeader));
        return Chunk::GetUserDataPtr(chunk);
#else
        return Chunk::GetUserDataPtr(chunk);
#endif
    }

    // finally, if there is no available space for chunk
    // create new arena and allocate from it
    Arena* arena = CreateArena(g_DEFAULT_ARENA_SIZE);
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
    void* userChunk = Chunk::GetUserDataPtr(arena->AllocateFromTopChunk(realChunkSize));
    std::memset(userChunk, g_FILL_CHAR, realChunkSize - sizeof(Chunk::ChunkHeader));
    return userChunk;
#else
    return Chunk::GetUserDataPtr(arena->AllocateFromTopChunk(realChunkSize));
#endif
}

bool MemoryAllocator::Deallocate(void* t_chunkPtr)
{
    PROFILE_FUNCTION();

    // If given pointer is nullptr just return false
    // because we dont want to waste time, trying to search
    // for arena
    if (t_chunkPtr == nullptr) {
        return false;
    }

    // iterating through all the areas in an attempt
    // to find the one that the chunk belongs to
    for (auto* arena : s_ArenaList) {
        if (t_chunkPtr >= arena->begin && t_chunkPtr <= arena->end) {
            arena->DeallocateChunk(Chunk::GetHeaderPtr(t_chunkPtr));
            return true;
            break;
        }
    }

    // If we reached this point, we should be in some kind of error
    // state, because, we've tried to free invalid/non-existing chunk
    // In FULL_DEBUG/SECURE mode terminate the program, otherwise silently 
    // return false 
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
    utils::ErrorAbort("MemoryAllocator::Deallocate(): Invalid pointer deallocation detected!\n");
#endif

    // The given pointer doens't belong to any active arena
    return false;
}
}