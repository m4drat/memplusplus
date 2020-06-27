#include "mpplib/memory_manager.hpp"

#include <string>

namespace mpp {
    std::vector<Arena*> MemoryManager::s_ArenaList;

    std::ostream& MemoryManager::DumpStats(std::ostream& t_out)
    {
        t_out << "MIN_CHUNK_SIZE: " << g_MIN_CHUNK_SIZE << std::endl;
        t_out << "CHUNK_HEADER_SIZE: " << g_MIN_CHUNK_SIZE << std::endl;
        t_out << "DEFAULT_ARENA_SIZE: " << g_DEFAULT_ARENA_SIZE << std::endl;
        t_out << "PAGE_SIZE: " << g_PAGE_SIZE << std::endl;
        for (auto* arena : s_ArenaList) {
            Arena::DumpArena(t_out, arena) << std::endl;
        }

        return t_out;
    }

    std::ostream& MemoryManager::VisHeapLayout(std::ostream& t_out)
    {
        for (auto* arena : s_ArenaList) {
            t_out << "Arena: " << reinterpret_cast<void*>(arena) << ":" << std::endl;
            for (std::size_t pos = reinterpret_cast<std::size_t>(arena->begin);
                 pos < reinterpret_cast<std::size_t>(arena->end);
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                Chunk* currChunk = reinterpret_cast<Chunk*>(pos);
                t_out << "[" << currChunk->GetPrevSize() << "/" << currChunk->GetSize()
                      << "/P:" << currChunk->IsPrevInUse() << "/U:" << currChunk->IsUsed()
                      << "]";
            }
        }
        return t_out;
    }

    // TODO: make it work better (probably add smart pointers memory managment)
    // This is just ugly thing to reset allocator state
    // exists only to make possible running of unit-tests
    bool MemoryManager::ResetAllocatorState()
    {
        for (int32_t i = 0; i < s_ArenaList.size(); ++i) {
            delete s_ArenaList.at(i);
        }
        s_ArenaList.clear();
    }

    Arena* MemoryManager::GetArenaByPtr(void* t_ptr)
    {
        for (auto* arena : s_ArenaList) {
            if (t_ptr >= arena->begin && t_ptr <= arena->end) {
                return arena;
            }
        }

        return nullptr;
    }

    Chunk* MemoryManager::GetInUseChunkByPtr(void* t_chunk)
    {
        Arena* arena = GetArenaByPtr(t_chunk);
        if (arena != nullptr) {
            return arena->GetInUseChunkByPtr(t_chunk);
        }

        return nullptr;
    }

}
