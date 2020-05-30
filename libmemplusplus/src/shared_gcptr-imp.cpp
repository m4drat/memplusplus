#pragma once

#include "mpplib/shared_gcptr.hpp"

#include <iostream>
#include <type_traits>

namespace mpp {
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(Type* obj)
    try : m_objectPtr {
        obj
    }
    , m_references{ new uint32_t(1) }
    {
#ifdef DEBUG
        std::cout << "[SharedGcPtr] Ptr created! References: " << *m_references
                  << std::endl;
#endif
        // TODO: add current GcPtr eto vector with GcPtrs
    }
    catch (...)
    {
        // exception occured (e.g. new throwed std::bad_alloc)
        // TODO: call free method on m_objectPtr

        if (m_objectPtr && std::is_destructible<Type>::value)
            m_objectPtr->~Type();

        throw;
    }

    template<class Type>
    SharedGcPtr<Type>::~SharedGcPtr()
    {
        if (m_references) {
            --(*m_references);
#ifdef DEBUG
            std::cout << "[SharedGcPtr] Ptr destroyed! References: "
                      << *m_references << std::endl;
#endif
            // Destroy shared ptr and object
            if (*m_references == 0) {
                delete m_references;
                // TODO: remove current GcPtr from vector with active GcPtrs
                // TODO: call "free" on object

                if (m_objectPtr && std::is_destructible<Type>::value)
                    m_objectPtr->~Type();

                m_references = nullptr;
                m_objectPtr = nullptr;
            }
        }
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(const SharedGcPtr<Type>& another)
        : m_objectPtr{ another.m_objectPtr }
        , m_references{ another.m_references }
    {
        if (m_references) {
            ++(*m_references);

#ifdef DEBUG
            std::cout << "[SharedGcPtr] Ptr copied! References: "
                      << *m_references << std::endl;
#endif
            // TODO: add copied GcPtr to vector with GcPtrs
        }
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(SharedGcPtr other)
    {
        other.swap(*this);
        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(
      SharedGcPtr&& other) noexcept
    {
        swap(other);
        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(Type* newData)
    {
        SharedGcPtr tmp(newData);
        tmp.swap(*this);
        return *this;
    }

    template<class Type>
    void SharedGcPtr<Type>::swap(SharedGcPtr& other) noexcept
    {
        std::swap(m_objectPtr, other.m_objectPtr);
        std::swap(m_references, other.m_references);
    }

    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args)
    {
        // TODO
        // return new (malloc(sizeof(T))) T(std::forward<Args>(args)...);
        return SharedGcPtr<T>();
    }
}