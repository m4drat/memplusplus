#pragma once

#include "mpplib/memory_allocator.hpp"

#include <new>

namespace mpp {
    template<class T> 
    struct MppStlAllocator {
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T value_type;

        MppStlAllocator() = default;

        // template <class U> struct rebind { typedef MppStlAllocator<U> other; };
        template <class U> 
        MppStlAllocator(const MppStlAllocator<U>&){}

        pointer address(reference x) const {return &x;}
        const_pointer address(const_reference x) const {return &x;}
        size_type max_size() const throw() {return size_t(-1) / sizeof(value_type);}

        pointer allocate(size_type n)
        {
            return static_cast<pointer>(mpp::MemoryAllocator::Allocate(n*sizeof(T)));
        }

        void deallocate(pointer p, size_type n)
        {
            mpp::MemoryAllocator::Deallocate(static_cast<void*>(p));
        }

        void construct(pointer p, const T& val)
        {
            new(static_cast<void*>(p)) T(val);
        }

        void construct(pointer p)
        {
            new(static_cast<void*>(p)) T();
        }

        void destroy(pointer p)
        {
            p->~T();
        }
    };

    template <class T, class U>
    bool operator==(const MppStlAllocator <T>&, const MppStlAllocator <U>&) { return true; }
    template <class T, class U>
    bool operator!=(const MppStlAllocator <T>&, const MppStlAllocator <U>&) { return false; }
}