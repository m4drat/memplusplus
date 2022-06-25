#pragma once

#include "mpplib/gc.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/profiler_definitions.hpp"
#include "mpplib/utils/utils.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>

namespace mpp {
    // Constructors
    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr()
    try : m_objectPtr{ nullptr }, m_references{ new uint32_t(1) } {
    } catch (...) {
        // exception occurred (e.g. new throwed std::bad_alloc)
        throw;
    }

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(std::nullptr_t t_newData)
        : SharedGcPtr()
    {}

    template<class Type>
    SharedGcPtr<Type>::SharedGcPtr(ElementType* obj)
    try : m_objectPtr{ obj }, m_references{ new uint32_t(1) } {
        PROFILE_FUNCTION();

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
        // MemoryManager::Deallocate<Type>(m_objectPtr);
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

        // Delete reference
        DeleteReference();

        // Update fields of assigned object
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
        return m_objectPtr;
    }

    template<class Type>
    typename SharedGcPtr<Type>::ElementType& SharedGcPtr<Type>::operator*() const noexcept
    {
        return *m_objectPtr;
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
    bool SharedGcPtr<Type>::AddToGcList()
    {
        GC::GetInstance().GetGcPtrs().insert(this);
        return true;
    }

    template<class Type>
    bool SharedGcPtr<Type>::DeleteFromGcList()
    {
        PROFILE_FUNCTION();

        // If current object points to nullptr do nothing
        if (m_objectPtr == nullptr)
            return false;

        auto& gcPtrs = GC::GetInstance().GetGcPtrs();

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
    void SharedGcPtr<Type>::Reset(std::nullptr_t const)
    {
        PROFILE_FUNCTION();

        DeleteReference();

        m_references = new uint32_t(1);
        m_objectPtr = nullptr;
    }

    template<class Type>
    void SharedGcPtr<Type>::Destroy()
    {
        if constexpr (std::is_array<Type>::value) {
            MM::DestroyArray(static_cast<ElementType*>(m_objectPtr), this->m_arraySize);
        } else {
            MM::DestroyObject(m_objectPtr);
        }
        MemoryManager::Deallocate(static_cast<void*>(m_objectPtr));
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

                // TODO: should we really deallocate data, or we just need to delete it
                // from chunksInUse + call object destructor
                if (m_objectPtr) {
                    Destroy();
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

        if constexpr (std::is_array<Type>::value) {
            std::swap(this->m_arraySize, t_other.m_arraySize);
        }
    }

    template<class Type>
    typename SharedGcPtr<Type>::ElementType* SharedGcPtr<Type>::Get() const noexcept
    {
        return m_objectPtr;
    }

    template<class Type>
    void* SharedGcPtr<Type>::GetVoid() const noexcept
    {
        return m_objectPtr;
    }

    template<class Type>
    void SharedGcPtr<Type>::UpdatePtr(void* t_newPtr)
    {
        m_objectPtr = reinterpret_cast<ElementType*>(t_newPtr);
    }

    template<class Type>
    uint32_t SharedGcPtr<Type>::UseCount()
    {
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

    template<class Type>
    void SharedGcPtr<Type>::CheckInvalidInitialization(ElementType* t_obj)
    {
        // Iterate through all GcPtrs, and check where they point.
        for (auto* gcPtr : GC::GetInstance().GetGcPtrs()) {
            if (gcPtr->GetVoid() == t_obj)
                utils::ErrorAbort("SharedGcPtr<Type>: Invalid initialization!\n");
        }
    }

    template<class Type, class... Args>
    SharedGcPtr<Type> MakeShared(Args&&... t_args)
    {
        PROFILE_FUNCTION();
        Type* ptr = static_cast<Type*>(MM::Allocate(sizeof(Type)));
        Type* obj = MM::Construct<Type>(ptr, std::forward<Args>(t_args)...);
        return SharedGcPtr<Type>(obj);
    }

    template<class Type, class... Args>
    SharedGcPtr<Type[]> MakeSharedN(uint32_t t_size, Args&&... t_args)
    {
        PROFILE_FUNCTION();

        Type* ptr = static_cast<Type*>(MM::Allocate(sizeof(Type) * t_size));

        for (uint32_t i = 0; i < t_size; i++) {
            [[maybe_unused]] Type* obj =
                MM::Construct<Type>(ptr + i, std::forward<Args>(t_args)...);
        }

        return SharedGcPtr<Type[]>(ptr, t_size);
    }
}