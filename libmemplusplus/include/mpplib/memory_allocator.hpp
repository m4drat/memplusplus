#pragma once

#include "mpplib/memory_manager.hpp"
#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"

#include <cmath>
#include <cstdint>
#include <new>
#include <type_traits>

namespace mpp {
    class MemoryAllocator : public MemoryManager
    {
    private:
        //////////////////////////////////////////////////////////////
        //                        WARNING                           //
        //////////////////////////////////////////////////////////////
        /**/static inline std::size_t Align(std::size_t t_size,   /**/
        /**/                                int32_t t_alignment);/**/
        //////////////////////////////////////////////////////////////
        static void* SysAlloc(std::size_t t_size);
        static bool SysDealloc(void* ptr, std::size_t pageSize);
        static Arena* CreateArena(std::size_t t_arenaSize);
        static void* AllocateBigChunk(std::size_t t_userDataSize);
        static Chunk* GetSuitableChunk(std::size_t t_realSize);

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
            Deallocate(static_cast<void*>(t_objPtr));
        }
    };
}