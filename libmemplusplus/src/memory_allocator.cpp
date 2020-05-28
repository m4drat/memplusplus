#include "mpplib/memory_allocator.hpp"
#include "mpplib/exception.hpp"
#include <sys/mman.h>

namespace mpp {

    size_t MemoryAllocator::Align(std::size_t t_size, int t_allignment)
    {
        return t_size + (t_allignment - (t_size % t_allignment));
    };

    void* MemoryAllocator::SysAlloc(std::size_t t_size)
    {
        void* rawPtr = mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
        if (rawPtr == -1)
        { 
            throw NoMemoryException();
        }
        return rawPtr;
    };

    void MemoryAllocator::SysDealloc(void* ptr)
    {

    };

    Arena* MemoryAllocator::CreateArena(std::size_t t_arenaSize)
    {
        void* arenaSpace = SysAlloc(t_arenaSize);
        Arena* arena = new Arena(t_arenaSize, 
                                    arenaSpace, 
                                    arenaSpace + t_arenaSize);
        s_ArenaList.push_back(arena);
        return arena;
    }

    Arena* MemoryAllocator::GetSuitableArena(std::size_t t_realSize)
    {   ///////////////////////////////////////
        //               WARNING             //
        ///////////////////////////////////////
        for (auto* arena : s_ArenaList) 
        {
            if (arena->freeSpace >= t_realSize)
            {
                return arena
            }
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
    
    void MemoryAllocator::Deallocate(void* chunkPtr)
    {
        // unsigned int ChunkSize  
    }
}