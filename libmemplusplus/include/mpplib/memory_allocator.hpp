#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"

#include <cmath>
#include <cstdint>
#include <new>
#include <type_traits>

namespace mpp {
    class Arena;
    class MemoryAllocator : public MemoryManager
    {
    private:
        /**
         * Function that make number dividable by alignment.
         * @param t_size is number to align
         * @param t_alignment is alignment
         * @return Aligned number
         */
        static std::size_t Align(std::size_t t_size, int32_t t_alignment);
        
        /**
         * mmap(2) wrapper, that map readble and writable, not shared
         * memory page of given size.
         * @param t_size Size of mapped memory
         * @return pointer to mapped memory.
         */
        static void* SysAlloc(std::size_t t_size);

        /**
         * munmap(2) wrapper, that unmap memory pages of given size.
         * @param ptr is pointer to memory, that will be unmapped.
         * @param pageSize size of memory, that will be unmapped.
         * @return That's all OK.
         */
        static bool SysDealloc(void* t_ptr, std::size_t t_pageSize);
        
        /**
         * Creates arena of given size and update global arenas list.
         * @param t_arenaSize is size of arena, that will be created.
         * @return newly created arena.
         */
        static Arena* CreateArena(std::size_t t_arenaSize);
        
        /**
         * Function that allocate chunk with user data bigger than 16MB.
         * It creates new arena and allocate chunk to it.
         * @param t_userDataSize is size of user data, that will be allocated.
         * @return void pointer to newly allocated chunk.
         */
        static void* AllocateBigChunk(std::size_t t_userDataSize);

        /**
         * 
         */
        static Chunk* GetSuitableChunk(std::size_t t_realSize);
        friend class GC;
        friend class Arena;

    public:
        static void* Allocate(std::size_t t_userDataSize);
        static void Deallocate(void* t_chunkPtr);

        template<class T, class... Args>
        static T* Allocate(Args&&... t_args)
        {
            return new (Allocate(sizeof(T))) T(std::forward<Args>(t_args)...);
        }

        template<class T>
        static void Deallocate(T* t_objPtr)
        {
            if (std::is_destructible<T>::value)
                t_objPtr->~T();
            Deallocate(reinterpret_cast<void*>(t_objPtr));
        }
    };
}