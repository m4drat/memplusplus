#include "mpplib/memory_manager.hpp"

#include <string>

namespace mpp {
    std::vector<Arena*> MemoryManager::s_ArenaList;

    void MemoryManager::InitAllocatorState()
    {
#if MPP_FUZZER_INSECURE == 1 || MPP_DEBUG == 1
        std::srand(0);
#else
        // Random that is used only inside ChunkTreap to balance it
        std::srand(std::time(NULL));
#endif
    }

#if MPP_STATS == 1
    std::ostream& MemoryManager::VisHeapLayout(std::ostream& t_out, void* t_ptr = nullptr)
    {
        PROFILE_FUNCTION(); 

        for (auto* arena : s_ArenaList) {
            t_out << "-------------- Arena: " << reinterpret_cast<void*>(arena) << " --------------"
                  << std::endl;
            for (std::size_t pos = reinterpret_cast<std::size_t>(arena->begin);
                 pos < reinterpret_cast<std::size_t>(arena->end);
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                Chunk* currChunk = reinterpret_cast<Chunk*>(pos);

                bool currentChunkPtr = ((t_ptr >= currChunk) && (t_ptr < (reinterpret_cast<char*>(currChunk) + currChunk->GetSize())));

#if MPP_COLOUR == 1
                if (t_ptr != nullptr && currentChunkPtr) {
                    t_out << col::MAGENTA << "<(";
                } else {
                    t_out << col::BLUE << "[";
                }

                if (currChunk->IsUsed()) {
                    t_out << col::GREEN << "PTR:" << static_cast<void*>(currChunk) << col::RESET << "/"
                          << col::GREEN << "PS:" << currChunk->GetPrevSize() << col::RESET << "/"
                          << col::GREEN << "CS:"<< currChunk->GetSize() << col::RESET << "/";
                } else {
                    t_out <<   col::RED << "PTR:" << static_cast<void*>(currChunk) << col::RESET << "/"
                          << col::GREEN << "PS:" << currChunk->GetPrevSize() << col::RESET << "/"
                          << col::GREEN << "CS:"<< currChunk->GetSize() << col::RESET << "/";
                }
                if (currChunk->IsPrevInUse()) {
                    t_out << col::GREEN << "P:" << currChunk->IsPrevInUse() << col::RESET << "/";
                } else {
                    t_out << col::RED << "P:" << currChunk->IsPrevInUse() << col::RESET << "/";
                }
                if (currChunk->IsUsed()) {
                    t_out << col::GREEN << "U:" << currChunk->IsUsed();
                } else {
                    t_out << col::RED << "U:" << currChunk->IsUsed();
                }
                
                if (t_ptr != nullptr && currentChunkPtr) {
                    t_out << col::MAGENTA << ")>" << col::RESET;
                } else {
                    t_out << col::BLUE << "]" << col::RESET;
                }
#else
                if (t_ptr != nullptr && currentChunkPtr) {
                    t_out << "<(";
                } else {
                    t_out << "[";
                }
                t_out << "PTR:" << static_cast<void*>(currChunk) << "/PS:" << currChunk->GetPrevSize() << "/CS:" << currChunk->GetSize()
                      << "/P:" << currChunk->IsPrevInUse() << "/U:" << currChunk->IsUsed();
                
                if (t_ptr != nullptr && currentChunkPtr) {
                    t_out << ")>";
                } else {
                    t_out << "]";
                }
#endif
            }
            t_out << std::endl;
        }
        return t_out;
    }
#endif

    // TODO: make it work better (probably add smart pointers memory managment)
    // This is just ugly thing to reset allocator state
    // exists only to make possible running of unit-tests
    bool MemoryManager::ResetAllocatorState()
    {
        PROFILE_FUNCTION();
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
        PROFILE_FUNCTION();
        for (auto* arena : s_ArenaList) {
            if (t_ptr >= arena->begin && t_ptr <= arena->end) {
                return arena;
            }
        }

        return nullptr;
    }

    Chunk* MemoryManager::GetInUseChunkByPtr(void* t_chunk)
    {
        PROFILE_FUNCTION();

        Arena* arena = GetArenaByPtr(t_chunk);
        if (arena != nullptr) {
            return arena->GetInUseChunkByPtr(t_chunk);
        }

        return nullptr;
    }

}
