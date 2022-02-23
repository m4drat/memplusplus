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
     * @brief Memory allocator class. Provides methods such as Allocate and Deallocate.
     */
    class MemoryAllocator : public MemoryManager
    {
    private:
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
        
        friend class GC;
        friend class Arena;

    public:
        /**
         * @brief Function that make number dividable by alignment.
         * @param t_size is number to align
         * @param t_alignment is alignment
         * @return std::size_t Aligned number
         */
        static std::size_t Align(std::size_t t_size, int32_t t_alignment);

        /**
         * @brief Default Allocate method. Allocates chunk with size at least
         * t_userDataSize.
         * @param t_userDataSize request size.
         * @return void* pointer to user data in allocated chunk
         */
        static void* Allocate(std::size_t t_userDataSize);

        /**
         * @brief Deallocates chunk of memory.
         * @param t_chunkPtr pointer to start of user data.
         * @return true, if chunk was deallocated successfully, false if chunk
         * doesn't belong to any arena
         */
        static bool Deallocate(void* t_chunkPtr);

        /**
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

            return new (Allocate(sizeof(T))) T(std::forward<Args>(t_args)...);
        }

        /**
         * @brief Template version of Deallocate to call object destructor.
         * @tparam T actual type of object.
         * @param t_objPtr pointer to object of type T.
         * @return true, if chunk was deallocated successfully, false if chunk
         * doesn't belong to any arena
         */
        template<class T>
        static bool Deallocate(T* t_objPtr)
        {
            PROFILE_FUNCTION();
            
            if (std::is_destructible<T>::value) {
                t_objPtr->~T();
            }
            return Deallocate(reinterpret_cast<void*>(t_objPtr));
        }

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
    };
}