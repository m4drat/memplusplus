#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#if MPP_STATS == 1
#include "mpplib/utils/statistics.hpp"
#endif

#include <cmath>
#include <cstdint>
#include <cstring>
#include <new>
#include <type_traits>

namespace mpp {
    class Arena;
    /**
     * @brief Memory allocator class. Performs raw memoty allocation/deallocation as well as objects
     * construction/destruction.
     */

    template<class T>
    class SharedGcPtr;

    class MemoryManager
    {
    private:
        template<class T>
        friend class SharedGcPtr;
        template<class Type, class... Args>
        friend SharedGcPtr<Type> MakeShared(Args&&... t_args);
        template<class Type, class... Args>
        friend SharedGcPtr<Type[]> MakeSharedN(uint32_t t_size, Args&&... t_args);

        friend class GC;
        friend class Arena;

        MemoryManager() = delete;

        /**
         * @brief Initializes random seed for chunk treap.
         */
        static __attribute__((constructor)) void InitAllocatorState();

        // TODO: refactor to work with std::unique_ptr
        /**
         * @brief All existing arenas.
         */
        static std::vector<Arena*> s_arenaList;

        /**
         * @brief Generate MMAP hint.
         * @return std::intptr_t base address for new page.
         */
        static std::uintptr_t MmapHint();

        /**
         * @brief mmap(2) wrapper, that maps readble and writable, not shared
         * memory page of given size.
         * @throw NoMemoryException, if system cannot map new memory.
         * @param t_size Size of mapped memory
         * @return void* pointer to mapped memory.
         */
        static void* SysAlloc(std::size_t t_size);

        /**
         * @brief munmap(2) wrapper, that unmaps memory page of given size.
         * @param ptr is pointer to memory, that will be unmapped.
         * @param pageSize size of memory, that will be unmapped.
         * @throw UnmapMemoryException, if cannot unmap memory.
         * @return true if everything is fine, otherwise it will throw exception
         */
        static bool SysDealloc(void* t_ptr, std::size_t t_pageSize);

        /**
         * @brief Creates arena of given size and update global arenas list.
         * @param t_arenaSize is size of arena, that will be created.
         * @return newly created arena.
         */
        static Arena* CreateArena(std::size_t t_arenaSize);

        /**
         * @brief Function that allocate chunk with user data bigger than 32MB.
         *
         * It creates new arena and allocate chunk in it.
         * @param t_userDataSize is the size of user data, that will be allocated.
         * @return void* pointer to newly allocated chunk.
         */
        static void* AllocateBigChunk(std::size_t t_userDataSize);

        /**
         * @brief Finds suitable chunk of requested size from somwhere (top/freelist).
         * @param t_realSize already aligned size of request.
         * @return Chunk* allocated chunk, or nullptr
         */
        static Chunk* GetSuitableChunk(std::size_t t_realSize);

        /**
         * @brief User specified hook to call before Allocate
         */
        static std::function<void*(std::size_t)> g_mppAllocateHook;

        /**
         * @brief User specified hook to call before Deallocate
         */
        static std::function<bool(void*)> g_mppDeallocateHook;

        /**
         * @brief Construct objects at t_objectPtr using params provided in t_args
         * @param t_objectPtr pointer to memory location where to construct the object
         * @param t_args arguments to T's constructor
         * @return T* memory location where constructed object is stored
         */
        template<class T, class... Args>
        static T* Construct(T* t_objectPtr, Args&&... t_args)
        {
            return ::new (t_objectPtr) T(std::forward<Args>(t_args)...);
        }

        /**
         * @brief Destroys single object
         * @tparam T user parameter type
         * @param t_objectPtr pointer to object
         * @return T* pointer to the destroyed object
         */
        template<class T>
        static inline T* DestroyObject(T* t_objectPtr)
        {
            if (std::is_destructible<T>::value) {
                t_objectPtr->~T();
            }

            return t_objectPtr;
        }

        /**
         * @brief Destroys all objects inside array
         * @tparam T user parameter type
         * @param t_objectPtr pointer to the array start
         * @param t_arraySize array size
         * @return T* pointer to the array beginning
         */
        template<class T>
        static T* DestroyArray(T* t_objectPtr, std::size_t t_arraySize)
        {
            for (uint32_t i = 0; i < t_arraySize; i++) {
                DestroyObject(t_objectPtr + i);
            }

            return t_objectPtr;
        }

    public:
        /**
         * @deprecated instead of using Allocate use @sa MakeShared<T> / @sa MakeSharedN<T>
         * @brief Default Allocate method. Allocates chunk with size at least
         * t_userDataSize.
         * @param t_userDataSize request size.
         * @return void* pointer to user data in allocated chunk
         */
        static void* Allocate(std::size_t t_userDataSize);

        /**
         * @deprecated this method is deprecated and will be private in a future version
         * because we don't operate with raw pointers anymore.
         * @brief Deallocates chunk of memory.
         * @param t_chunkPtr pointer to start of user data.
         * @return true, if chunk was deallocated successfully, false if chunk
         * doesn't belong to any arena
         */
        static bool Deallocate(void* t_chunkPtr);

        /**
         * @deprecated instead of using Allocate<T> use @sa MakeShared<T> / @sa MakeSharedN<T>
         * @brief Template version of Allocate to call object constructor.
         * @tparam T object to allocate type.
         * @tparam Args list of arguments to pass to object constructor.
         * @param t_args actual arguments to object constructor.
         * @return T* constructed object
         */
        template<class T, class... Args>
        static T* Allocate(Args&&... t_args)
        {
            PROFILE_FUNCTION();

            return Construct(static_cast<T*>(Allocate(sizeof(T))), std::forward<Args>(t_args)...);
        }

        /**
         * @deprecated this method is deprecated and will be private in a future version
         * because we don't operate with raw pointers anymore.
         * @brief Template version of Deallocate to call object destructor.
         * @tparam T actual type of the object.
         * @param t_objPtr pointer to object of type T.
         * @return true, if chunk was deallocated successfully, false if chunk
         * doesn't belong to any arena
         */
        template<class T>
        static bool Deallocate(T* t_objPtr)
        {
            PROFILE_FUNCTION();

            return Deallocate(reinterpret_cast<void*>(DestroyObject(t_objPtr)));
        }

        /**
         * @brief Ceils number (t_size) to the nearest number such that this number divided by
         * t_alignment has no remainder.
         * @param t_size is number to align
         * @param t_alignment is alignment
         * @return std::size_t Aligned number
         */
        static std::size_t Align(std::size_t t_size, int32_t t_alignment);

        /**
         * @brief Sets hook for Allocate method
         * @param t_allocateHook std::function to set as hook
         */
        static void SetAllocateHook(const std::function<void*(std::size_t)>& t_allocateHook);

        /**
         * @brief Sets hook for DeAllocate method
         * @param t_deallocateHook std::function to set as hook
         */
        static void SetDeallocateHook(const std::function<bool(void*)>& t_deallocateHook);

#if MPP_STATS == 1 || MPP_DEBUG == 1
        /**
         * @brief Visualizes heap layout.
         * @param t_out output stream to write to.
         * @return std::ostream& stream reference
         */
        static std::ostream& VisHeapLayout(std::ostream& t_out, void* t_ptr);
#endif

        /**
         * @brief Get reference to vector of arenas.
         * @return const std::vector<Arena*>& to arenas
         */
        static const std::vector<Arena*>& GetArenaList()
        {
            return s_arenaList;
        }

        /**
         * @brief Finds inside which arena t_ptr points.
         * @param t_ptr heap pointer.
         * @return Arena* if pointer points into arena, nullptr otherwise
         */
        static Arena* GetArenaByPtr(void* t_ptr);

        /**
         * @brief Finds inside which chunk t_ptr points.
         * @param t_ptr heap pointer.
         * @return Chunk* if pointer points into some chunk, nullptr otherwise
         */
        static Chunk* GetInUseChunkByPtr(void* t_ptr);

        /**
         * @brief Resets allocator state by destroying all arenas.
         * @return true if everything is fine, false otherwise
         */
        static bool ResetAllocatorState();

        /**
         * @brief Minimum allowed chunk size. Chunk size less than that will be extended.
         */
        static const std::size_t g_MIN_CHUNK_SIZE = 32;

        /**
         * @brief Size of chunk header.
         */
        static const std::size_t g_CHUNK_HEADER_SIZE = sizeof(Chunk::ChunkHeader_t);

        /**
         * @brief Default arena size.
         */
        static const std::size_t g_DEFAULT_ARENA_SIZE = 32 * (1 << 20);

        /**
         * @brief Page size for mmap request.
         */
        static const std::size_t g_PAGE_SIZE = 4096;

        /**
         * @brief Defines base location of all arenas. Allocator
         * will try to allocate memory from this address + random offset.
         * If it isn't possible to allocate memory at desired address, just
         * call mmap(NULL, ...).
         */
        static const std::uintptr_t g_MMAP_START = 1ull << 40;

#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
        /**
         * @brief fill char, to fill allocated chunks in debug mode or secure mode.
         */
        static const uint8_t g_FILL_CHAR = MPP_FILL_CHAR;
#endif
    };

    using MM = MemoryManager;
}