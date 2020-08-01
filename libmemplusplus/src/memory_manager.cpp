#include "mpplib/memory_manager.hpp"

#include <string>

#ifdef MPP_COLOUR
#include "mpplib/utils/colours.hpp"
namespace col = mpp::utils::colours;
#endif

namespace mpp {
    std::vector<Arena*> MemoryManager::s_ArenaList;

    std::ostream& MemoryManager::DumpStats(std::ostream& t_out)
    {
        t_out << "MIN_CHUNK_SIZE: " << g_MIN_CHUNK_SIZE << std::endl;
        t_out << "CHUNK_HEADER_SIZE: " << sizeof(Chunk::ChunkHeader) << std::endl;
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

#ifdef MPP_COLOUR
                if (currChunk->IsUsed()) {
                    t_out << "[" << col::GREEN << currChunk->GetPrevSize() << "/"
                          << currChunk->GetSize() << "/P:" << currChunk->IsPrevInUse()
                          << "/U:" << currChunk->IsUsed() << col::RESET << "]";
                } else {
                    t_out << "[" << col::RED << currChunk->GetPrevSize() << "/"
                          << currChunk->GetSize() << "/P:" << currChunk->IsPrevInUse()
                          << "/U:" << currChunk->IsUsed() << col::RESET << "]";
                }
#else
                t_out << "[" << currChunk->GetPrevSize() << "/" << currChunk->GetSize()
                      << "/P:" << currChunk->IsPrevInUse() << "/U:" << currChunk->IsUsed() << "]";
#endif
            }
        }
        return t_out;
    }

    // TODO: make it work better (probably add smart pointers memory managment)
    // This is just ugly thing to reset allocator state
    // exists only to make possible running of unit-tests
    bool MemoryManager::ResetAllocatorState()
    {
        auto it = s_ArenaList.begin();
        while (it != s_ArenaList.end()) {
            delete *it;
            *it = nullptr;
            it = s_ArenaList.erase(it);
        }

        return true;
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
