#pragma once

#include "mpplib/gc.hpp"
#include "mpplib/memory_allocator.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

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
    PROFILE_FUNCTION();
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
SharedGcPtr<Type>::SharedGcPtr(const SharedGcPtr<Type>& t_other)
    : m_objectPtr{ t_other.m_objectPtr }
    , m_references{ t_other.m_references }
{
    PROFILE_FUNCTION();

    // Shared ptr copied. Increase references count.
    if (m_references) {
        ++(*m_references);
    }

    // Insert newly created shared ptr to list of all
    // active gc ptrs
    if (m_objectPtr != nullptr) {
        AddToGcList();
    }
}

template<class Type>
SharedGcPtr<Type>::SharedGcPtr(SharedGcPtr<Type>&& t_other)
{
    PROFILE_FUNCTION();
    Swap(t_other);
}

// Destructors
template<class Type>
SharedGcPtr<Type>::~SharedGcPtr()
{
    PROFILE_FUNCTION();
    DeleteReference();
}

template<class Type>
SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(SharedGcPtr<Type>&& t_other) noexcept
{
    PROFILE_FUNCTION();
    if (this != &t_other) {
        Swap(t_other);
    }

    return *this;
}

template<class Type>
SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(const SharedGcPtr<Type>& t_other)
{
    PROFILE_FUNCTION();
    if (this == &t_other) {
        return *this;
    }

    // Delete reference
    DeleteReference();

    // Update fileds of assigned object
    m_objectPtr = t_other.m_objectPtr;
    m_references = t_other.m_references;

    // If needed add to list of all active gc ptr
    if (m_objectPtr != nullptr)
        AddToGcList();

    // Increase references count
    if (m_references)
        ++(*m_references);

    return *this;
}

template<class Type>
SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(Type* t_newData)
{
    PROFILE_FUNCTION();
    // Create temp object
    SharedGcPtr tmp(t_newData);

    // Swap with temp object
    tmp.Swap(*this);
    return *this;
}

template<class Type>
SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(std::nullptr_t t_newData)
{
    PROFILE_FUNCTION();
    // Just delete reference
    this->DeleteReference();
    return *this;
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
    GC::GetInstance().GetGcPtrs().push_back(this);
    return true;
}

template<class Type>
bool SharedGcPtr<Type>::DeleteFromGcList()
{
    PROFILE_FUNCTION();
    // If current object points to nullptr do nothing
    if (m_objectPtr == nullptr)
        return false;

    // Delete shared ptr from list of all active gc ptrs
    auto toErase =
      std::find(GC::GetInstance().GetGcPtrs().begin(), GC::GetInstance().GetGcPtrs().end(), this);
    if (toErase != GC::GetInstance().GetGcPtrs().end()) {
        GC::GetInstance().GetGcPtrs().erase(toErase);
        return true;
    }
    return false;
}

template<class Type>
void SharedGcPtr<Type>::Reset()
{
    PROFILE_FUNCTION();
    Reset(nullptr);
}

template<class Type>
void SharedGcPtr<Type>::Reset(std::nullptr_t const)
{
    PROFILE_FUNCTION();
    DeleteReference();

    m_references = new uint32_t(1);
    m_objectPtr = nullptr;
}

template<class Type>
void SharedGcPtr<Type>::DeleteReference()
{
    PROFILE_FUNCTION();
    DeleteFromGcList();

    // If m_references isn't nullptr
    if (m_references) {
        // Decrease references count
        --(*m_references);

        // Destroy shared ptr and object
        if (*m_references <= 0) {
            // Delete references variable
            delete m_references;
            m_references = nullptr;

            // TODO: shoud we really deallocate data, or we just need to delete it
            // from chunksInUse + call object destructor
            if (m_objectPtr) {
                MemoryAllocator::Deallocate<Type>(m_objectPtr);
            }
        }
    }

    m_references = nullptr;
    m_objectPtr = nullptr;
}

template<class Type>
void SharedGcPtr<Type>::Swap(SharedGcPtr& t_other)
{
    PROFILE_FUNCTION();
    // Current object ptr is nullptr
    // t_other's object ptr isn't nullptr
    if (m_objectPtr == nullptr && t_other.m_objectPtr != nullptr) {
        t_other.DeleteFromGcList();
        AddToGcList();
    }

    // Current object ptr isn't nullptr
    // t_other's object ptr is nullptr
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
    if (m_objectPtr) {
        t_out << reinterpret_cast<void*>(m_objectPtr);
    } else {
        t_out << "nullptr";
    }
    if (m_references != nullptr) {
        t_out << ", " << *m_references << ")";
    } else {
        t_out << ", nullptr)";
    }
    return t_out;
}

template<class Type, class... Args>
SharedGcPtr<Type> MakeSharedGcPtr(Args&&... t_args)
{
    PROFILE_FUNCTION();
    return SharedGcPtr<Type>(MemoryAllocator::Allocate<Type>(std::forward<Args>(t_args)...));
}
}