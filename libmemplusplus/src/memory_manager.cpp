#include "mpplib/memory_manager.hpp"
#include "mpplib/exception.hpp"
#include "mpplib/utils/random.hpp"
#include "mpplib/utils/utils.hpp"

#include <sys/mman.h>

namespace mpp {
    std::function<void*(std::size_t)> MemoryManager::g_mppAllocateHook{ nullptr };
    std::function<bool(void*)> MemoryManager::g_mppDeallocateHook{ nullptr };
    std::vector<Arena*> MemoryManager::s_arenaList;

    std::uintptr_t MemoryManager::MmapHint()
    {
        std::uintptr_t randOffset = static_cast<std::uintptr_t>(
            Random::GetInstance()()); // generates random value [0, (2 << 63) - 1]

        // Min value: 0x10000000000
        // Max value: 0x40ffffc00000
        // User can allocate memory in this range: [0, 0x0007fffffffffff]
        // In theory, hint can overlap with an existing allocation, because default arena size is
        // 32mb, and we use only 6mb as an offset between maps. But that still should be sufficient,
        // cause probability of this event is negligible. Using 0xFFFFFF as a random mask we should
        // have 24 random bits, which will give us enough entropy.
        std::uintptr_t mmapHint =
            MemoryManager::g_MMAP_START + (6 * 1024 * 1024) * (randOffset & 0xFFFFFF);
        return mmapHint;
    }

    std::size_t MemoryManager::Align(std::size_t t_size, int32_t t_alignment)
    {
        PROFILE_FUNCTION();

        if (t_size != 0 && (t_size % t_alignment == 0))
            return t_size;
        return t_size + (t_alignment - (t_size % t_alignment));
    }

    std::byte* MemoryManager::SysAlloc(std::size_t t_size)
    {
        PROFILE_FUNCTION();

        // In secure build try to randomize mmap base (to protect against attacks like
        // Offset-to-lib) If attemp failed, just call mmap(NULL, ...)
#if MPP_SECURE == 1
        std::byte* rawPtr = static_cast<std::byte*>(mmap(reinterpret_cast<void*>(MmapHint()),
                                                         t_size,
                                                         PROT_READ | PROT_WRITE,
                                                         MAP_PRIVATE | MAP_ANONYMOUS,
                                                         -1,
                                                         0));
        if (rawPtr == MAP_FAILED) { // This time try to allocate without any hints
            rawPtr = static_cast<std::byte*>(
                mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
        }
#else
        void* rawPtr = static_cast<std::byte*>(
            mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
#endif
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

    bool MemoryManager::SysDealloc(void* t_ptr, std::size_t t_pageSize)
    {
        PROFILE_FUNCTION();

        if (munmap(t_ptr, t_pageSize) == -1) {
            throw UnmapMemoryException();
        }

        return true;
    }

    Arena* MemoryManager::CreateArena(std::size_t t_arenaSize)
    {
        PROFILE_FUNCTION();

        // Allocate memory for arena
        std::byte* arenaSpace = SysAlloc(t_arenaSize);

        // TODO - smart pointers memory management
        Arena* arena = new Arena(t_arenaSize, arenaSpace);

        // Add newly created arena to vector of active arenas
        s_arenaList.push_back(arena);

        return arena;
    }

    Chunk* MemoryManager::GetSuitableChunk(std::size_t t_realSize)
    {
        PROFILE_FUNCTION();

        Chunk* chunkToReturn = nullptr;

        // Try iterating through all available arenas
        // to try to find enough space for user-requested chunk
        // in top chunk
        for (auto* arena : s_arenaList) {
            // check if arena->topChunk != nullptr, in this case, we still have
            // some space in the right side
            if (arena->topChunk && (t_realSize <= arena->topChunk->GetSize())) {
                chunkToReturn = arena->AllocateFromTopChunk(t_realSize);
            } else { // Check if current arena has enough free space
                chunkToReturn = arena->GetFirstGreaterOrEqualThanChunk(t_realSize);

                // If we are here, current arena doesn't have any free space,
                // proceed to the next one
                if (chunkToReturn == nullptr) {
                    continue;
                }
                chunkToReturn = arena->AllocateFromFreeList(chunkToReturn, t_realSize);
            }
#if MPP_STATS == 1
            if (chunkToReturn->GetSize() > arena->arenaStats->biggestAllocation) {
                arena->arenaStats->biggestAllocation = chunkToReturn->GetSize();
            }
            if (chunkToReturn->GetSize() < arena->arenaStats->smallestAllocation) {
                arena->arenaStats->smallestAllocation = chunkToReturn->GetSize();
            }
#endif

            return chunkToReturn;
        }

        // If we still cant find chunk, we will return nullptr
        // to show that we dont have arena, to allocate from
        return nullptr;
    }

    void* MemoryManager::AllocateBigChunk(std::size_t t_userDataSize)
    {
        PROFILE_FUNCTION();

        // Create new arena with requested size
        Arena* arena = CreateArena(t_userDataSize);
#if MPP_STATS == 1
        arena->arenaStats->bigArena = true;
#endif

        // Allocate chunk from right space of that arena
        Chunk* bigChungus = arena->AllocateFromTopChunk(t_userDataSize);
        return Chunk::GetUserDataPtr(bigChungus);
    }

    void* MemoryManager::Allocate(std::size_t t_userDataSize)
    {
        PROFILE_FUNCTION();

        // User placed hook to call before actual Allocate
        if (g_mppAllocateHook != nullptr) {
            return g_mppAllocateHook(t_userDataSize);
        }

        // Align, because we want to have metadata bits
        std::size_t realChunkSize =
            Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_MIN_CHUNK_SIZE);

        // If allocation size is bigger than default arena size
        // we will allocate new arena with chunk, which size is
        // equal to requested size, aligned to g_PAGE_SIZE
        if (realChunkSize > g_DEFAULT_ARENA_SIZE) {
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
            void* bigChunk = AllocateBigChunk(Align(realChunkSize, g_PAGE_SIZE));
            std::memset(bigChunk,
                        g_FILL_CHAR,
                        Align(realChunkSize, g_PAGE_SIZE) - sizeof(Chunk::ChunkHeader));
            return bigChunk;
#else
            return AllocateBigChunk(Align(realChunkSize, g_PAGE_SIZE));
#endif
        }

        // If we dont have active arenas yet
        // we will create new one
        if (s_arenaList.empty()) {
            CreateArena(g_DEFAULT_ARENA_SIZE);
        }

        // Try to get chunk from any suitable arena (by searching in free list
        // or by splitting top chunk)
        Chunk* chunk = GetSuitableChunk(realChunkSize);
        if (chunk != nullptr) {
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
            std::memset(Chunk::GetUserDataPtr(chunk),
                        g_FILL_CHAR,
                        realChunkSize - sizeof(Chunk::ChunkHeader));
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

    bool MemoryManager::Deallocate(void* t_chunkPtr)
    {
        PROFILE_FUNCTION();

        // User placed hook to call before actual Allocate
        if (g_mppDeallocateHook != nullptr) {
            return g_mppDeallocateHook(t_chunkPtr);
        }

        // If given pointer is nullptr just return false
        // because we dont want to waste time, trying to search
        // for arena
        if (t_chunkPtr == nullptr) {
            return false;
        }

        // iterating through all the areas in an attempt
        // to find the one that the chunk belongs to
        for (auto* arena : s_arenaList) {
            if (t_chunkPtr >= arena->begin && t_chunkPtr <= arena->end) {
                // In this case, we still can free invalid pointer, so
                // add additional checks inside DeallocateChunk
                arena->DeallocateChunk(Chunk::GetHeaderPtr(t_chunkPtr));
                return true;
                break;
            }
        }

        // If we reached this point, we should be in some kind of error
        // state, because, we've tried to free invalid/non-existing chunk
        // Always abort program, because we don't have any performance impact.
        utils::ErrorAbort("MemoryManager::Deallocate(): Invalid pointer deallocation detected!\n");

        // The given pointer doesn't belong to any active arena
        return false;
    }

    void MemoryManager::SetAllocateHook(const std::function<void*(std::size_t)>& t_allocateHook)
    {
        g_mppAllocateHook = t_allocateHook;
    }

    void MemoryManager::SetDeallocateHook(const std::function<bool(void*)>& t_deallocateHook)
    {
        g_mppDeallocateHook = t_deallocateHook;
    }

    void MemoryManager::InitAllocatorState()
    {
#if MPP_FUZZER_INSECURE == 1 || MPP_DEBUG == 1
        std::srand(0);
#else
        // Random that is used only inside ChunkTreap to balance it
        std::srand(std::time(NULL));
#endif
    }

#if MPP_STATS == 1 || MPP_DEBUG == 1
    std::ostream& MemoryManager::VisHeapLayout(std::ostream& t_out, void* t_ptr = nullptr)
    {
        PROFILE_FUNCTION();

        for (auto* arena : s_arenaList) {
            t_out << "-------------- Arena: " << reinterpret_cast<void*>(arena) << " --------------"
                  << std::endl;
            Chunk* currChunk = reinterpret_cast<Chunk*>(arena->begin);
            for (std::byte* pos = arena->begin; pos < arena->end; pos += currChunk->GetSize()) {
                currChunk = reinterpret_cast<Chunk*>(pos);

                bool currentChunkPtr =
                    ((t_ptr >= currChunk) && (t_ptr < (currChunk + currChunk->GetSize())));

#if MPP_COLOUR == 1
                if (t_ptr != nullptr && currentChunkPtr) {
                    t_out << col::MAGENTA << "<(";
                } else {
                    t_out << col::BLUE << "[";
                }

                if (currChunk->IsUsed()) {
                    t_out << col::GREEN << "PTR:" << static_cast<void*>(currChunk) << col::RESET
                          << "/" << col::GREEN << "PS:" << currChunk->GetPrevSize() << col::RESET
                          << "/" << col::GREEN << "CS:" << currChunk->GetSize() << col::RESET
                          << "/";
                } else {
                    t_out << col::RED << "PTR:" << static_cast<void*>(currChunk) << col::RESET
                          << "/" << col::GREEN << "PS:" << currChunk->GetPrevSize() << col::RESET
                          << "/" << col::GREEN << "CS:" << currChunk->GetSize() << col::RESET
                          << "/";
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
                t_out << "PTR:" << static_cast<void*>(currChunk)
                      << "/PS:" << currChunk->GetPrevSize() << "/CS:" << currChunk->GetSize()
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

    // TODO: make it work better (probably add smart pointers memory management)
    // This is just ugly thing to reset allocator state
    // exists only to supprot unit-tests execution
    bool MemoryManager::ResetAllocatorState()
    {
        PROFILE_FUNCTION();

        auto it = s_arenaList.begin();
        while (it != s_arenaList.end()) {
            delete *it;
            *it = nullptr;
            it = s_arenaList.erase(it);
        }

        return true;
    }

    Arena* MemoryManager::GetArenaByPtr(void* t_ptr)
    {
        PROFILE_FUNCTION();

        for (auto* arena : s_arenaList) {
            if (t_ptr >= arena->begin && t_ptr <= arena->end) {
                return arena;
            }
        }

        return nullptr;
    }

    Chunk* MemoryManager::GetInUseChunkByPtr(void* t_ptr)
    {
        PROFILE_FUNCTION();

        Arena* arena = GetArenaByPtr(t_ptr);
        if (arena != nullptr) {
            return arena->GetInUseChunkByPtr(t_ptr);
        }

        return nullptr;
    }
}
