#include "mpplib/memory_allocator.hpp"
#include "mpplib/exception.hpp"
#include <sys/mman.h>

namespace mpp {

    std::size_t MemoryAllocator::Align(std::size_t t_size, int32_t t_allignment)
    {
        return t_size + (t_allignment - (t_size % t_allignment));
    };

    void* MemoryAllocator::SysAlloc(std::size_t t_size)
    {
        void* rawPtr = mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
        if (rawPtr == MAP_FAILED)
        { 
            throw NoMemoryException();
        }
        return rawPtr;
    };

    bool MemoryAllocator::SysDealloc(void* ptr, std::size_t pageSize)
    {
        if (bool result = munmap(ptr, pageSize) != -1)
        {
            throw UnmapMemoryException();
        };

        return true;
    };

    Arena* MemoryAllocator::CreateArena(std::size_t t_arenaSize)
    {
        void* arenaSpace = SysAlloc(t_arenaSize);
        Arena* arena = new Arena(t_arenaSize, 
                                    arenaSpace, 
                                    reinterpret_cast<void*>((std::size_t)arenaSpace + t_arenaSize));
        s_ArenaList.push_back(arena);
        return arena;
    }

    // TODO
    Arena* MemoryAllocator::GetSuitableArena(std::size_t t_realSize)
    {   ////////////////////////////GetSuit///////////
        //               WARNING             //
        ///////////////////////////////////////
        for (auto* arena : s_ArenaList) 
        {
            if (arena->rightSpace >= t_realSize || arena->maxBetweenSpace >= t_realSize)
            {
                return arena;
            };
        }
        return nullptr;
        ////////////////////////////////////////
    }

    void* MemoryAllocator::AllocateBigChunk(std::size_t t_userDataSize)
    {
        size_t realSize = Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_PAGE_SIZE);
        Arena* arena = CreateArena(realSize);
        return (arena->AllocateChunk(realSize) + sizeof(Chunk::ChunkHeader));
    }

    void* MemoryAllocator::Allocate(std::size_t t_userDataSize)
    {
        std::size_t realChunkSize = Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_MIN_CHUNK_SIZE);
        
        if (realChunkSize > g_DEFAULT_ARENA_SIZE) 
        {
            return AllocateBigChunk(realChunkSize);
        }
        
        if (s_ArenaList.empty()) 
        {
            CreateArena(g_DEFAULT_ARENA_SIZE);     
        }
        
        Arena* arena = GetSuitableArena(realChunkSize);
        if (arena != nullptr)
        {
            return (arena->AllocateChunk(realChunkSize) + sizeof(Chunk::ChunkHeader));
        }
        arena = CreateArena(g_DEFAULT_ARENA_SIZE);
        return (arena->AllocateChunk(realChunkSize) + sizeof(Chunk::ChunkHeader));
    };
    
    // TODO
    void MemoryAllocator::Deallocate(void* t_chunkPtr)
    {
        
    }
}