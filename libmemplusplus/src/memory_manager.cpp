#include "mpplib/memory_manager.hpp"

#include <string>

namespace mpp {
    std::vector<Arena*> MemoryManager::s_ArenaList;

#if MPP_STATS == 1
    std::ostream& MemoryManager::VisHeapLayout(std::ostream& t_out)
    {
        for (auto* arena : s_ArenaList) {
            t_out << "-------------- Arena: " << reinterpret_cast<void*>(arena) << " --------------"
                  << std::endl;
            for (std::size_t pos = reinterpret_cast<std::size_t>(arena->begin);
                 pos < reinterpret_cast<std::size_t>(arena->end);
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                Chunk* currChunk = reinterpret_cast<Chunk*>(pos);

#if MPP_COLOUR == 1
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
#endif

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
