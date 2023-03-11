#include "mpplib/memory_manager.hpp"
#include "mpplib/exception.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/random.hpp"
#include "mpplib/utils/utils.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <sys/mman.h>

namespace mpp {
    std::unique_ptr<MemoryManager> g_memoryManager{ nullptr }; // NOLINT

    std::uintptr_t MemoryManager::MmapHint()
    {
        // generates random value [0, (2 << 63) - 1]
        auto randOffset = static_cast<std::uintptr_t>(Random::GetInstance()());

        // Min value: 0x10000000000
        // Max value: 0x40ffffc00000
        // User can allocate memory in this range: [0, 0x0007fffffffffff]
        // In theory, hint can overlap with an existing allocation, because default arena size is
        // 32mb, and we use only 6mb as an offset between maps. But that still should be sufficient,
        // cause probability of this event is negligible. Using 0xFFFFFF as a random mask we should
        // have 24 random bits, which will give us enough entropy.
        const uint64_t megabyte = 1024 * 1024;
        const uint64_t randomMask = 0xFFFFFF;
        const uint64_t mapOffsetMb = 6 * megabyte;
        std::uintptr_t mmapHint =
            MemoryManager::g_MMAP_START + mapOffsetMb * (randOffset & randomMask);
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
        auto* rawPtr = static_cast<std::byte*>(mmap(reinterpret_cast<void*>(MmapHint()),
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
        std::byte* rawPtr = static_cast<std::byte*>(
            mmap(NULL, t_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
#endif
        if (rawPtr == MAP_FAILED) {
            throw NoMemoryException();
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

    std::unique_ptr<Arena>& MemoryManager::CreateArena(std::size_t t_arenaSize)
    {
        PROFILE_FUNCTION();

        // Allocate memory for arena
        std::byte* arenaSpace = SysAlloc(t_arenaSize);

        // Add newly created arena to vector of active arenas
        m_arenaList.emplace_back(std::make_unique<Arena>(t_arenaSize, arenaSpace));

        return m_arenaList.back();
    }

    Chunk* MemoryManager::GetSuitableChunk(std::size_t t_realSize)
    {
        PROFILE_FUNCTION();

        Chunk* chunkToReturn = nullptr;

        // Try iterating through all available arenas to try to
        // find enough space for user-requested chunk in top chunk
        for (auto& arena : m_arenaList) {
            // check if arena->topChunk != nullptr, in this case, we still have
            // some space in the "right side" of the arena
            if (arena->TopChunk() && (t_realSize <= arena->TopChunk()->GetSize())) {
                chunkToReturn = arena->AllocateFromTopChunk(t_realSize);
            } else { // Check if current arena has enough free space
                chunkToReturn = arena->GetFirstGreaterOrEqualToChunk(t_realSize);

                // If we are here, current arena doesn't have any free space,
                // proceed to the next one
                if (chunkToReturn == nullptr) {
                    continue;
                }
                chunkToReturn = arena->AllocateFromFreeList(chunkToReturn, t_realSize);
            }
#if MPP_STATS == 1
            arena->GetArenaStats()->UpdateBiggestAllocation(chunkToReturn->GetSize());
            arena->GetArenaStats()->UpdateSmallestAllocation(chunkToReturn->GetSize());
#endif

            return chunkToReturn;
        }

        // If we still cant find a chunk, we will return a nullptr
        // to show that we dont have an arena, to allocate from
        return nullptr;
    }

    Chunk* MemoryManager::AllocateBigChunk(std::size_t t_userDataSize)
    {
        PROFILE_FUNCTION();

        // Create new arena with requested size
        auto& arena = CreateArena(t_userDataSize);
#if MPP_STATS == 1
        arena->GetArenaStats()->bigArena = true;
#endif

        // Allocate chunk from right space of that arena
        Chunk* bigChungus = arena->AllocateFromTopChunk(t_userDataSize);
        return bigChungus;
    }

    void* MemoryManager::Allocate(std::size_t t_userDataSize)
    {
        PROFILE_FUNCTION();

        // User placed hook to call before actual Allocate
        if (m_allocateHook != nullptr) {
            return m_allocateHook(t_userDataSize);
        }

        // Align, because we want to have metadata bits
        std::size_t realChunkSize =
            Align(t_userDataSize + sizeof(Chunk::ChunkHeader), g_MIN_CHUNK_SIZE);

        // If allocation size is bigger than default arena size
        // we will allocate new arena with chunk, which size is
        // equal to requested size, aligned to g_PAGE_SIZE
        if (realChunkSize > g_DEFAULT_ARENA_SIZE) {
            Chunk* bigChunk = AllocateBigChunk(Align(realChunkSize, g_PAGE_SIZE));
            MPP_SECURE_WIPE_CHUNK(bigChunk);
            return Chunk::GetUserDataPtr(bigChunk);
        }

        // If we dont have any active arena yet. Create a new one.
        if (m_arenaList.empty()) {
            CreateArena(g_DEFAULT_ARENA_SIZE);
        }

        // Try to get chunk from any suitable arena (by searching in free list
        // or by splitting top chunk)
        Chunk* chunk = GetSuitableChunk(realChunkSize);
        if (chunk != nullptr) {
            MPP_SECURE_WIPE_CHUNK(chunk);
            return Chunk::GetUserDataPtr(chunk);
        }

        // finally, if there is no available space for chunk
        // create new arena and allocate from it
        auto& arena = CreateArena(g_DEFAULT_ARENA_SIZE);
        Chunk* userChunk = arena->AllocateFromTopChunk(realChunkSize);
        MPP_SECURE_WIPE_CHUNK(userChunk);
        return Chunk::GetUserDataPtr(userChunk);
    }

    bool MemoryManager::Deallocate(void* t_chunkPtr)
    {
        PROFILE_FUNCTION();

        // User placed hook to call before actual Allocate
        if (m_deallocateHook != nullptr) {
            return m_deallocateHook(t_chunkPtr);
        }

        // If a given pointer is a nullptr - return false
        // We dont want to waste time, searching for the arena
        if (t_chunkPtr == nullptr) {
            return false;
        }

        // Find arena that chunk belongs to
        for (auto& arena : m_arenaList) {
            if (t_chunkPtr >= arena->BeginPtr() && t_chunkPtr <= arena->EndPtr()) {
                // In this case, we still can free invalid pointer, so
                // add additional checks inside DeallocateChunk
                arena->DeallocateChunk(Chunk::GetHeaderPtr(t_chunkPtr));
                MPP_POISON_USER_DATA_INSIDE_CHUNK(Chunk::GetHeaderPtr(t_chunkPtr));
                return true;
            }
        }

        // We've tried to free invalid/non-existing chunk. Always abort the program in this case.
        utils::ErrorAbort("MemoryManager::Deallocate(): Invalid pointer deallocation detected!\n");

        // The given pointer doesn't belong to any active arena
        return false;
    }

    void MemoryManager::SetAllocateHook(const std::function<void*(std::size_t)>& t_allocateHook)
    {
        m_allocateHook = t_allocateHook;
    }

    void MemoryManager::SetDeallocateHook(const std::function<bool(void*)>& t_deallocateHook)
    {
        m_deallocateHook = t_deallocateHook;
    }

    MemoryManager::MemoryManager()
        : m_allocateHook{ nullptr }
        , m_deallocateHook{ nullptr }
    {
#if MPP_FUZZER_INSECURE == 1 || MPP_DEBUG == 1
        std::srand(0); // NOLINT
#else
        // Random that is used only inside ChunkTreap to balance it
        std::srand(std::time(NULL));
#endif
    }

#if MPP_STATS == 1 || MPP_DEBUG == 1
    std::ostream& MemoryManager::VisHeapLayout(std::ostream& t_out, void* t_ptr = nullptr)
    {
        PROFILE_FUNCTION();

        for (auto& arena : m_arenaList) {
            t_out << "-------------- Arena: " << reinterpret_cast<void*>(arena.get())
                  << " --------------" << std::endl;
            for (Chunk& chunk : *arena) {
                Chunk* currChunkPtr = &chunk;

                bool isPtrInsideCurrChunk =
                    ((t_ptr >= currChunkPtr) && (t_ptr < (currChunkPtr + currChunkPtr->GetSize())));

#if MPP_COLOUR == 1
                if (t_ptr != nullptr && isPtrInsideCurrChunk) {
                    t_out << col::MAGENTA << "<(";
                } else {
                    t_out << col::BLUE << "[";
                }

                if (currChunkPtr->IsUsed()) {
                    t_out << col::GREEN << "PTR:" << static_cast<void*>(currChunkPtr) << col::RESET
                          << "/" << col::GREEN << "PS:" << currChunkPtr->GetPrevSize() << col::RESET
                          << "/" << col::GREEN << "CS:" << currChunkPtr->GetSize() << col::RESET
                          << "/";
                } else {
                    t_out << col::RED << "PTR:" << static_cast<void*>(currChunkPtr) << col::RESET
                          << "/" << col::GREEN << "PS:" << currChunkPtr->GetPrevSize() << col::RESET
                          << "/" << col::GREEN << "CS:" << currChunkPtr->GetSize() << col::RESET
                          << "/";
                }
                if (currChunkPtr->IsPrevInUse()) {
                    t_out << col::GREEN << "P:" << currChunkPtr->IsPrevInUse() << col::RESET << "/";
                } else {
                    t_out << col::RED << "P:" << currChunkPtr->IsPrevInUse() << col::RESET << "/";
                }
                if (currChunkPtr->IsUsed()) {
                    t_out << col::GREEN << "U:" << currChunkPtr->IsUsed();
                } else {
                    t_out << col::RED << "U:" << currChunkPtr->IsUsed();
                }

                if (t_ptr != nullptr && isPtrInsideCurrChunk) {
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

    MemoryManager::~MemoryManager()
    {
        PROFILE_FUNCTION();

        m_arenaList.clear();

        // FIXME: It's time to completely revamp this method!
        GC::GetInstance().GetGcPtrs().clear();
    }

    std::optional<std::reference_wrapper<std::unique_ptr<Arena>>> MemoryManager::GetArenaByPtr(
        void* t_ptr)
    {
        PROFILE_FUNCTION();

        for (auto& arena : m_arenaList) {
            if (t_ptr >= arena->BeginPtr() && t_ptr <= arena->EndPtr()) {
                return arena;
            }
        }

        return std::nullopt;
    }

    void* Allocate(std::size_t t_userDataSize)
    {
        return g_memoryManager->Allocate(t_userDataSize);
    }

    bool Deallocate(void* t_chunkPtr)
    {
        return g_memoryManager->Deallocate(t_chunkPtr);
    }

    void SetAllocateHook(const std::function<void*(std::size_t)>& t_allocateHook)
    {
        g_memoryManager->SetAllocateHook(t_allocateHook);
    }

    void SetDeallocateHook(const std::function<bool(void*)>& t_deallocateHook)
    {
        g_memoryManager->SetDeallocateHook(t_deallocateHook);
    }

    std::vector<std::unique_ptr<Arena>>& GetArenaList()
    {
        return g_memoryManager->GetArenaList();
    }
}
