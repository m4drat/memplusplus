#pragma once

#include "mpplib/gcptr.hpp"

#include <type_traits>

namespace mpp {
    template<class Type>
    class SharedGcPtr : public GcPtr
    {
    private:
        Type* m_objectPtr{ nullptr };
        unsigned int* m_references{ nullptr };

    public:

        // Define explicit constructor 
        explicit SharedGcPtr(Type* obj)
        try {
            : m_objectPtr(obj)
            , m_references(new int(1))
            {
                // TODO: add current GcPtr eto vector with GcPtrs
            }
        } catch (...) {
            // exception occured (e.g. new throwed std::bad_alloc)
            // TODO: call free method on m_objectPtr

            // if (std::is_destructible<Type>::value)
            m_objectPtr->~Type();
            throw;
        }

        ~SharedGcPtr()
        {
            --(*m_references);

            // Destroy shared ptr and object
            if (*m_references == 0) {
                delete m_references;
                // TODO: remove current GcPtr from vector with active GcPtrs
                // TODO: call "free" on object
                
                // if (std::is_destructible<Type>::value)
                m_objectPtr->~Type();
            }
        }

        // Define copy constructor
        SharedGcPtr(SharedGcPtr const& another)
            : m_objectPtr{ another.m_objectPtr }
            , m_references{ another.m_references }
        {
            ++(*m_references);
            // TODO: add copied GcPtr to vector with GcPtrs
        }
    };

    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args);
};

// include templates implementation
// only in this case it's ok to include .cpp file
#include "shared_gcptr-imp.cpp"