#pragma once

#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/profiler_definitions.hpp"
#include "mpplib/utils/utils.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

namespace mpp {
    // Constructors
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr()
        : m_references{ nullptr }
    {
        this->m_objectPtr = nullptr;
        static_assert(offsetof(SharedGcPtr<Type>, m_objectPtr) == 8,
                      "this->m_objectPtr must be at offset 8");
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(std::nullptr_t t_newData)
        : SharedGcPtr()
    {
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(ElementType* obj)
    try : m_references{ new uint32_t(1) } {
        static_assert(offsetof(SharedGcPtr<Type>, m_objectPtr) == 8,
                      "this->m_objectPtr must be at offset 8");

        PROFILE_FUNCTION();

        this->m_objectPtr = obj;

        // In secure build add check for invalid Initialization.
        // This check should prevent ability for use-after-free
        // Due to invalid initialization (2 different SPs initialized
        // with the same pointer)
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
        CheckInvalidInitialization(obj);
#endif

        AddToGcList();
    } catch (...) {
        // exception occurred (e.g. new throwed std::bad_alloc)
        // Delete object, and call it's destructor
        // MemoryManager::Deallocate<Type>(this->m_objectPtr);
        throw;
    }

    // Copy-Constructors
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(const SharedGcPtr<Type>& t_other)
        : m_references{ t_other.m_references }
    {
        PROFILE_FUNCTION();

        this->m_objectPtr = t_other.m_objectPtr;

        // Shared ptr copied. Increase references count.
        if (m_references) {
            ++(*m_references);
        }

        // Insert newly created shared ptr to the list of all active gc ptrs.
        if (this->m_objectPtr != nullptr) {
            AddToGcList();
        }

        // Update size if array.
        if constexpr (std::is_array<Type>::value) {
            this->m_arraySize = t_other.m_arraySize;
        }
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(SharedGcPtr<Type>&& t_other) noexcept
    {
        PROFILE_FUNCTION();

        Swap(t_other);
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(Type t_obj, uint32_t t_arraySize)
        : SharedGcPtr<Type>(static_cast<ElementType*>(t_obj))
    {
        PROFILE_FUNCTION();
        static_assert(std::is_array<Type>::value,
                      "mpp::SharedGcPtr<T>::SharedGcPtr(Type* t_obj, uint32_t t_arraySize) is only "
                      "valid when T is an array type.");

        this->m_arraySize = t_arraySize;
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

        bool isActiveGcPtr = this->m_objectPtr != nullptr;
        bool otherIsActiveGcPtr = t_other.m_objectPtr != nullptr;

        // Copy t_other fields, so that if DecrementRefCounter is going to delete the object, the
        // fields will still be valid.
        auto* newObjectPtr = t_other.m_objectPtr;
        auto* newReferences = t_other.m_references;

        // Copy array size if we are working with an array.
        uint32_t arraySize = 0;
        if constexpr (std::is_array<Type>::value) {
            arraySize = t_other.m_arraySize;
        }

        // Increase t_other references count.
        if (t_other.m_references)
            ++(*t_other.m_references);

        // Decrement current shared pointer references count.
        // WARNING: This must be done after increasing t_other references count, and after copying
        // t_other fields!
        DecrementRefCounter();

        // Update fields of the assigned object.
        this->m_objectPtr = newObjectPtr;
        m_references = newReferences;

        // Update size if array.
        if constexpr (std::is_array<Type>::value) {
            this->m_arraySize = arraySize;
        }

        // Fast path: If both are active gc ptrs, or both are not active gc ptrs, then just
        // return a pointer with updated fields. No need to remove from/insert to the gc list.
        bool skipGcListUpdates =
            (isActiveGcPtr && otherIsActiveGcPtr) || (!isActiveGcPtr && !otherIsActiveGcPtr);
        if (skipGcListUpdates) {
            return *this;
        }

        // Slow path: If current pointer was an active gc ptr, but the other is not, or vice versa,
        // remove it from the gc list.
        if (isActiveGcPtr)
            DeleteFromGcList();

        // If required add to list of all active gc ptrs.
        if (this->m_objectPtr != nullptr)
            AddToGcList();

        return *this;
    }

    template<class Type>
    SharedGcPtr<Type>& SharedGcPtr<Type>::operator=(Type* t_newData)
    {
        PROFILE_FUNCTION();

        // In secure build add check for invalid Initialization.
        // This check should prevent ability for use-after-free
        // Due to invalid initialization (2 different SPs initialized
        // with the same pointer)
#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
        CheckInvalidInitialization(t_newData);
#endif

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
    typename SharedGcPtr<Type>::ElementType* SharedGcPtr<Type>::operator->() const noexcept
    {
        static_assert(!std::is_array<Type>::value,
                      "mpp::SharedGcPtr<T>::operator-> is only valid when T is not an array type.");
        return this->m_objectPtr;
    }

    template<class Type>
    typename SharedGcPtr<Type>::ElementType& SharedGcPtr<Type>::operator*() const noexcept
    {
        return *this->m_objectPtr;
    }

    template<class Type>
    SharedGcPtr<Type>::operator bool() const
    {
        return Get() != nullptr;
    }

    template<class Type>
    std::ptrdiff_t SharedGcPtr<Type>::operator-(const SharedGcPtr<Type>& t_other) const noexcept
    {
        return Get() - t_other.Get();
    }

    template<class Type>
    typename SharedGcPtr<Type>::ElementType& SharedGcPtr<Type>::operator[](
        std::ptrdiff_t t_index) const noexcept
    {
        static_assert(std::is_array<Type>::value,
                      "mpp::SharedGcPtr<T>::operator[] is only valid when T is an array type.");

        if (static_cast<uint32_t>(t_index) >= this->m_arraySize) [[unlikely]] {
            utils::ErrorAbort(std::string(__func__) + " - index out of range!\n");
        }

        return Get()[t_index];
    }

    template<class Type>
    void SharedGcPtr<Type>::AddToGcList()
    {
        g_memoryManager->GetGC().AddGcPtr(this);
    }

    template<class Type>
    bool SharedGcPtr<Type>::DeleteFromGcList()
    {
        PROFILE_FUNCTION();

        auto& gcPtrs = g_memoryManager->GetGC().GetGcPtrs();

        // Delete shared ptr from list of all active gc ptrs
        auto toErase = std::find(gcPtrs.begin(), gcPtrs.end(), this);
        if (toErase != gcPtrs.end()) {
            gcPtrs.erase(toErase);
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
    void SharedGcPtr<Type>::Reset(std::nullptr_t)
    {
        PROFILE_FUNCTION();

        DeleteReference();

        m_references = new uint32_t(1);
        this->m_objectPtr = nullptr;
    }

    template<class Type>
    void SharedGcPtr<Type>::Destroy()
    {
        if constexpr (std::is_array<Type>::value) {
            MM::DestroyArray(static_cast<ElementType*>(this->m_objectPtr), this->m_arraySize);
        } else {
            MM::DestroyObject(this->m_objectPtr);
        }
        Deallocate(static_cast<void*>(this->m_objectPtr));
    }

    template<class Type>
    void SharedGcPtr<Type>::DeleteReference()
    {
        PROFILE_FUNCTION();

        // Remove current object from list of all active gc ptrs.
        // If current object pointer is nullptr - do nothing.
        if (this->m_objectPtr)
            DeleteFromGcList();

        // Decrement reference counter.
        DecrementRefCounter();

        m_references = nullptr;
        this->m_objectPtr = nullptr;
    }

    template<class Type>
    void SharedGcPtr<Type>::DecrementRefCounter()
    {
        // If m_references isn't nullptr
        if (m_references) {
            // De
            --(*m_references);

            // Destroy shared ptr and the object
            if (*m_references <= 0) {
                // Delete references variable
                delete m_references;
                m_references = nullptr;

                // If we have a pointer to an object, while m_references is 0 or less, we should
                // deallocate this object as no one is pointing to it, so it's not used anymore.
                if (this->m_objectPtr) {
                    Destroy();
                }
            }
        }
    }

    template<class Type>
    void SharedGcPtr<Type>::Swap(SharedGcPtr& t_other)
    {
        PROFILE_FUNCTION();
        // Current object ptr is nullptr
        // t_other's object ptr isn't nullptr
        if (this->m_objectPtr == nullptr && t_other.m_objectPtr != nullptr) {
            t_other.DeleteFromGcList();
            AddToGcList();
        }

        // Current object ptr isn't nullptr
        // t_other's object ptr is nullptr
        if (this->m_objectPtr != nullptr && t_other.m_objectPtr == nullptr) {
            DeleteFromGcList();
            t_other.AddToGcList();
        }

        std::swap(this->m_objectPtr, t_other.m_objectPtr);
        std::swap(m_references, t_other.m_references);

        if constexpr (std::is_array<Type>::value) {
            std::swap(this->m_arraySize, t_other.m_arraySize);
        }
    }

    template<class Type>
    typename SharedGcPtr<Type>::ElementType* SharedGcPtr<Type>::Get() const noexcept
    {
        return this->m_objectPtr;
    }

    template<class Type>
    void* SharedGcPtr<Type>::GetVoid() const noexcept
    {
        return this->m_objectPtr;
    }

    template<class Type>
    void SharedGcPtr<Type>::UpdatePtr(void* t_newPtr)
    {
        this->m_objectPtr = reinterpret_cast<ElementType*>(t_newPtr);
    }

    template<class Type>
    uint32_t SharedGcPtr<Type>::UseCount()
    {
        if (!m_references)
            return 0;

        return *m_references;
    }

    template<class Type>
    uint32_t SharedGcPtr<Type>::GetArraySize()
    {
        static_assert(std::is_array<Type>::value,
                      "mpp::SharedGcPtr<T>::operator[] is only valid when T is an array type.");

        return this->m_arraySize;
    }

    template<class Type>
    std::ostream& SharedGcPtr<Type>::Print(std::ostream& t_out) const
    {
        t_out << "|SP|[" << this << "]"
              << "(";
        if (this->m_objectPtr) {
            t_out << reinterpret_cast<void*>(this->m_objectPtr);
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

    template<class Type>
    void SharedGcPtr<Type>::CheckInvalidInitialization(ElementType* t_obj)
    {
        // Iterate through all GcPtrs, and check where they point.
        for (auto* gcPtr : g_memoryManager->GetGC().GetGcPtrs()) {
            if (gcPtr->GetVoid() == t_obj)
                utils::ErrorAbort("SharedGcPtr<Type>: Invalid initialization!\n");
        }
    }
}