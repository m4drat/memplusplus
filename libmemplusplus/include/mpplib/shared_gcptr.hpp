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
        explicit SharedGcPtr(Type* obj = nullptr);

        ~SharedGcPtr() override;

        // Define copy constructor
        SharedGcPtr(const SharedGcPtr<Type>& another);

        SharedGcPtr<Type>& operator=(SharedGcPtr other);
        SharedGcPtr<Type>& operator=(SharedGcPtr&& other) noexcept;
        SharedGcPtr<Type>& operator=(Type* newData);

        void swap(SharedGcPtr& other) noexcept;

        Type* operator->() const
        {
            return m_objectPtr;
        }
        Type& operator*() const
        {
            return *m_objectPtr;
        }

        Type* get() const
        {
            return m_objectPtr;
        }

        uint32_t UseCount()
        {
            return *m_references;
        }

        std::ostream& Print(std::ostream& t_out) const override
        {
            return t_out << "[|SP|" << this << "]"
                         << "(" << reinterpret_cast<void*>(m_objectPtr) << ", "
                         << *m_references << ")" << std::endl;
        }
    };

    // TODO
    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args);
};

// include templates implementation
// only in this case it's ok to include .cpp file
#include "shared_gcptr-imp.cpp"