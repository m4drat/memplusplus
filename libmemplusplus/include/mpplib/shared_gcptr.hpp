#pragma once

#include <iostream>
#include <utility>

#include "mpplib/gcptr.hpp"

namespace mpp {
    template<class Type>
    class SharedGcPtr : public GcPtr
    {
    private:
        Type* m_objectPtr{ nullptr };
        uint32_t* m_references{ nullptr };

    public:
        // Constructors
        SharedGcPtr();
        SharedGcPtr(std::nullptr_t t_newData);
        explicit SharedGcPtr(Type* t_obj);

        // Copy-Constructors
        SharedGcPtr(const SharedGcPtr<Type>& t_another);

        // Destructors
        ~SharedGcPtr() override;

        // Assignment operators
        // SharedGcPtr<Type>& operator=(SharedGcPtr t_other);
        SharedGcPtr<Type>& operator=(SharedGcPtr&& t_other) noexcept;
        SharedGcPtr<Type>& operator=(const SharedGcPtr& t_other);
        SharedGcPtr<Type>& operator=(Type* t_newData);
        SharedGcPtr<Type>& operator=(std::nullptr_t t_newData);

        // comparisons operators
        bool operator==(Type* t_other) noexcept;
        bool operator!=(Type* t_other) noexcept;
        bool operator<=(Type* t_other) noexcept;
        bool operator<(Type* t_other) noexcept;
        bool operator>=(Type* t_other) noexcept;
        bool operator>(Type* t_other) noexcept;
        
        Type* operator->() const noexcept;
        Type& operator*() const noexcept;

        bool DeleteFromGcList();
        void Reset();
        void Reset(std::nullptr_t const);
        void Swap(SharedGcPtr& t_other) noexcept;
        Type* Get() const;
        void* GetVoid() const override;
        void UpdatePtr(void* t_newPtr) override;
        uint32_t UseCount() override;

        std::ostream& Print(std::ostream& t_out) const override;
    };

    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... t_args);
};

// include templates implementation
// only in this case it's ok to include .cpp file
#include "shared_gcptr-imp.cpp"