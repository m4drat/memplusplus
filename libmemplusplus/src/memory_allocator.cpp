#include "mpplib/memory_allocator.hpp"
#include "mpplib/exception.hpp"

#include <sys/mman.h>

namespace mpp {

    std::size_t MemoryAllocator::Align(std::size_t t_size, int32_t t_alignment)
    {
        return t_size + (t_allignment - (t_size % t_allignment));
    };

    void* MemoryAllocator::SysAlloc(std::size_t t_size)
    {
        void* rawPtr =
          mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
        if (rawPtr == MAP_FAILED) {
            throw NoMemoryException();
        }
        return rawPtr;
    };

    bool MemoryAllocator::SysDealloc(void* ptr, std::size_t pageSize)
    {
        if (bool result = munmap(ptr, pageSize) != -1) {
            throw UnmapMemoryException();
        };

        return true;
    };

    Arena* MemoryAllocator::CreateArena(std::size_t t_arenaSize)
    {
        void* arenaSpace = SysAlloc(t_arenaSize);
        Arena* arena = new Arena(t_arenaSize, arenaSpace);
        s_ArenaList.push_back(arena);

        return arena;
    }

    // TODO
    Chunk* MemoryAllocator::GetSuitableChunk(std::size_t t_realSize)
    {
        // If we have enough space in topChunk
        for (auto* arena : s_ArenaList) {
            // check if arena->topChunk != nullptr, in this case, we still have
            // some space in the right side
            if (arena->topChunk && t_realSize <= arena->topChunk->GetSize()) {
                return arena->AllocateFromTopChunk(t_realSize);
            }
        }

        // If we cant find arena with enough right space, we will
        // iterate through ChunkTreap to find chunk to reuse
        for (auto* arena : s_ArenaList)
        {
            Chunk* chunk = arena->GetFirstGreaterOrEqualThanChunk(t_realSize);
            if (chunk == nullptr) 
            { 
                continue;
            }
            return arena->AllocateFromFreeList(chunk, t_realSize); 
        }
        
        return nullptr;
    }

    // WARNING: it doesn't work
    void* MemoryAllocator::AllocateBigChunk(std::size_t t_userDataSize)
    {
        std::size_t realSize =
          Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_PAGE_SIZE);
        Arena* arena = CreateArena(realSize);
        return (arena->topChunk + sizeof(Chunk::ChunkHeader));
    }

    void* MemoryAllocator::Allocate(std::size_t t_userDataSize)
    {
        std::size_t realChunkSize =
          Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_MIN_CHUNK_SIZE);

        if (realChunkSize > g_DEFAULT_ARENA_SIZE) {
            return AllocateBigChunk(realChunkSize);
        }

        if (s_ArenaList.empty()) {
            CreateArena(g_DEFAULT_ARENA_SIZE);
        }

        Chunk* chunk = GetSuitableChunk(realChunkSize);
        if (chunk != nullptr) {
            return chunk;
        }
        
        // arena = CreateArena(g_DEFAULT_ARENA_SIZE);
        // return (arena->AllocateChunk(realChunkSize) +
        //        sizeof(Chunk::ChunkHeader));
    };

    // TODO
    void MemoryAllocator::Deallocate(void* t_chunkPtr)
    {}
}