#pragma once

#include "mpplib/gc.hpp"
#include "mpplib/memory_allocator.hpp"
#include "mpplib/shared_gcptr.hpp"

#include <algorithm>
#include <iostream>
#include <type_traits>

namespace mpp {
    // Constructors
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr()
    try : m_objectPtr {
        nullptr
    }
    , m_references{ new uint32_t(1) }
    {}
    catch (...)
    {
        // exception occured (e.g. new throwed std::bad_alloc)
        throw;
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(std::nullptr_t t_newData)
        : SharedGcPtr()
    {}

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(Type* obj)
    try : m_objectPtr {
        obj
    }
    , m_references{ new uint32_t(1) }
    {
        AddToGcList();
    }
    catch (...)
    {
        // exception occured (e.g. new throwed std::bad_alloc)
        // Delete object, and call it's destructor
        MemoryAllocator::Deallocate<Type>(m_objectPtr);
        throw;
    }

    // Copy-Constructors
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(const SharedGcPtr<Type>& t_another)
        : m_objectPtr{ t_another.m_objectPtr }
        , m_references{ t_another.m_references }
    {
        if (m_references) {
            ++(*m_references);
        }

        if (m_objectPtr != nullptr)
            AddToGcList();
    }

    // Destructors
    template<class Type>
    SharedGcPtr<Type>::~SharedGcPtr()
    {
        DeleteFromGcList();
        Reset();
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(SharedGcPtr&& t_other) noexcept
    {
        Swap(t_other);
        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(const SharedGcPtr& t_other)
    {
        if (this == &t_other)
            return *this;

        if (t_other.m_objectPtr == nullptr)
            DeleteFromGcList();
        if (m_objectPtr == nullptr && t_other.m_objectPtr != nullptr)
            AddToGcList();

        Reset();

        m_objectPtr = t_other.m_objectPtr;
        m_references = t_other.m_references;

        if (m_references)
            ++(*m_references);

        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(Type* t_newData)
    {
        SharedGcPtr tmp(t_newData);
        tmp.Swap(*this);
        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(std::nullptr_t t_newData)
    {
        DeleteFromGcList();
        this->Reset();
    }

    // comparisons operators
    template<class Type>
    bool SharedGcPtr<Type>::operator==(const SharedGcPtr& t_other) noexcept
    {
        return Get() == t_other.Get();
    }

    template<class Type>
    bool SharedGcPtr<Type>::operator!=(const SharedGcPtr& t_other) noexcept
    {
        return Get() != t_other.Get();
    }

    template<class Type>
    bool SharedGcPtr<Type>::operator<=(const SharedGcPtr& t_other) noexcept
    {
        return Get() <= t_other.Get();
    }

    template<class Type>
    bool SharedGcPtr<Type>::operator<(const SharedGcPtr& t_other) noexcept
    {
        return Get() < t_other.Get();
    }

    template<class Type>
    bool SharedGcPtr<Type>::operator>=(const SharedGcPtr& t_other) noexcept
    {
        return Get() >= t_other.Get();
    }

    template<class Type>
    bool SharedGcPtr<Type>::operator>(const SharedGcPtr& t_other) noexcept
    {
        return Get() > t_other.Get();
    }

    template<class Type>
    Type* SharedGcPtr<Type>::operator->() const noexcept
    {
        return m_objectPtr;
    }

    template<class Type>
    Type& SharedGcPtr<Type>::operator*() const noexcept
    {
        return *m_objectPtr;
    }

    template<class Type>
    bool SharedGcPtr<Type>::AddToGcList()
    {
        GC::GetGcPtrs().push_back(this);
        return true;
    }

    template<class Type>
    bool SharedGcPtr<Type>::DeleteFromGcList()
    {
        if (m_objectPtr == nullptr)
            return false;

        auto toErase = std::find(GC::GetGcPtrs().begin(), GC::GetGcPtrs().end(), this);
        if (toErase != GC::GetGcPtrs().end()) {
            GC::GetGcPtrs().erase(toErase);
            return true;
        }
        return false;
    }

    template<class Type>
    void SharedGcPtr<Type>::Reset()
    {
        Reset(nullptr);
    }

    template<class Type>
    void SharedGcPtr<Type>::Reset(std::nullptr_t const)
    {
        if (m_references) {
            --(*m_references);
            // Destroy shared ptr and object
            if (*m_references <= 0) {
                delete m_references;
                // TODO: shoud we really deallocate data, or we just need to delete it
                // from chunksInUse + call object destructor
                if (m_objectPtr)
                    MemoryAllocator::Deallocate<Type>(m_objectPtr);

                m_references = nullptr;
                m_objectPtr = nullptr;
            }
        }
    }

    template<class Type>
    void SharedGcPtr<Type>::Swap(SharedGcPtr& t_other)
    {
        if (m_objectPtr == nullptr && t_other.m_objectPtr != nullptr) {
            t_other.DeleteFromGcList();
            AddToGcList();
        }

        if (m_objectPtr != nullptr && t_other.m_objectPtr == nullptr) {
            DeleteFromGcList();
            t_other.AddToGcList();
        }

        std::swap(m_objectPtr, t_other.m_objectPtr);
        std::swap(m_references, t_other.m_references);
    }

    template<class Type>
    Type* SharedGcPtr<Type>::Get() const
    {
        return m_objectPtr;
    }

    template<class Type>
    void* SharedGcPtr<Type>::GetVoid() const
    {
        return m_objectPtr;
    }

    template<class Type>
    void SharedGcPtr<Type>::UpdatePtr(void* t_newPtr)
    {
        m_objectPtr = reinterpret_cast<Type*>(t_newPtr);
    }

    template<class Type>
    uint32_t SharedGcPtr<Type>::UseCount()
    {
        return *m_references;
    }

    template<class Type>
    std::ostream& SharedGcPtr<Type>::Print(std::ostream& t_out) const
    {
        t_out << "|SP|[" << this << "]"
              << "(";
        if (m_objectPtr)
            t_out << reinterpret_cast<void*>(m_objectPtr);
        else
            t_out << "nullptr";
        return t_out << ", " << *m_references << ")";
    }

    template<class Type, class... Args>
    SharedGcPtr<Type> MakeSharedGcPtr(Args&&... t_args)
    {
        return SharedGcPtr<Type>(
          MemoryAllocator::Allocate<Type>(std::forward<Args>(t_args)...));
    }
}