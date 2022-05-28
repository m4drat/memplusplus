#pragma once

#include <iostream>
#include <utility>

#include "mpplib/gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

namespace mpp {
    /**
     * @brief SharedGcPtr class. Behaves like normal shared ptr.
     * @tparam Type of user object.
     */
    template<class Type>
    class SharedGcPtr : public GcPtr
    {
    private:
        /**
         * @brief pointer to object of user type.
         */
        Type* m_objectPtr{ nullptr };

        /**
         * @brief Number of references to object.
         */
        uint32_t* m_references{ nullptr };

        /**
         * @brief Release object, decrementing m_references.
         */
        void DeleteReference();

    public:
        /**
         * @brief Default constructor.
         */
        SharedGcPtr();

        /**
         * @brief Construct SharedGcPtr from nullptr.
         * @param t_newData nullpointer.
         */
        SharedGcPtr(std::nullptr_t t_newData);

        /**
         * @brief Construct SharedGcPtr from pointer to user object type.
         * @param t_obj pointer to user object.
         */
        explicit SharedGcPtr(Type* t_obj);

        /**
         * @brief Copy-Constructor to construct from const SharedGcPtr reference.
         * @param t_other rvalue reference to another SharedGcPtr
         */
        SharedGcPtr(const SharedGcPtr<Type>& t_other);

        /**
         * @brief Copy-Constructor to construct from const SharedGcPtr rvalue reference.
         * @param t_other const reference to another SharedGcPtr
         */
        SharedGcPtr(SharedGcPtr<Type>&& t_other);

        /**
         * @brief Destroy SharedGcPtr.
         */
        ~SharedGcPtr() override;

        // SharedGcPtr<Type>& operator=(SharedGcPtr t_other);
        /**
         * @brief Overloaded assignment operator, to construct object from rvalue
         * reference.
         * @param t_other rvalue reference to SharedGcPtr.
         * @return SharedGcPtr<Type>& new object
         */
        SharedGcPtr<Type>& operator=(SharedGcPtr<Type>&& t_other) noexcept;

        /**
         * @brief Overloaded assignment operator, to construct object from const
         * SharedGcPtr reference.
         * @param t_other const reference to SharedGcPtr.
         * @return SharedGcPtr<Type>& new object
         */
        SharedGcPtr<Type>& operator=(const SharedGcPtr<Type>& t_other);

        /**
         * @brief Overloaded assignment operator, to construct object from user data
         * pointer.
         * @param t_newData pointer to user data of type Type.
         * @return SharedGcPtr<Type>& new object
         */
        SharedGcPtr<Type>& operator=(Type* t_newData);

        /**
         * @brief Overloaded assignment operator, to construct object from nullptr.
         * @param t_newData nullptr
         * @return SharedGcPtr<Type>& new object
         */
        SharedGcPtr<Type>& operator=(std::nullptr_t t_newData);

        /**
         * @brief check, if two SharedGcPtr's are equal.
         */
        bool operator==(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief check, if two SharedGcPtr's are not equal.
         */
        bool operator!=(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief check, that lhs is less than or equal to rhs.
         */
        bool operator<=(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief check, that lhs is less than rhs.
         */
        bool operator<(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief check, that lhs is greater than or equal to rhs.
         */
        bool operator>=(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief check, that lhs is greater than rhs.
         */
        bool operator>(const SharedGcPtr& t_other) noexcept;

        /**
         * @brief Allows to use smart pointers as usual pointers.
         * @return Type* pointer to user data
         */
        Type* operator->() const noexcept;

        /**
         * @brief Allows to use smart pointers as usual pointers.
         * @return Type& reference to user data
         */
        Type& operator*() const noexcept;

        /**
         * @brief Allows automatic conversions to bool.
         */
		explicit operator bool() const;

        /**
         * @brief Calculates distance between two pointers
         */
		ptrdiff_t operator-(const SharedGcPtr<Type>& t_other) const noexcept;

        /**
         * @brief Tries to add SharedGcPtr to list of all active GcPtr's.
         * @return true if succeed, false otherwise
         */
        bool AddToGcList();

        /**
         * @brief Tries to delete SharedGcPtr from list of all active GcPtr's.
         * @return true if succeed, false otherwise
         */
        bool DeleteFromGcList();

        /**
         * @brief wrapper around Reset(std::nullptr_t).
         * @sa Reset(std::nullptr_t).
         */
        void Reset();

        /**
         * @brief Resets smart pointer. Decrements references counter.
         */
        void Reset(std::nullptr_t const);

        /**
         * @brief Performs swap operation on two SharedGcPtr's.
         * @param t_other reference to SharedGcPtr to swap with.
         */
        void Swap(SharedGcPtr& t_other);

        /**
         * @brief Returns raw pointer to user data.
         * @return Type* raw pointer to user data
         */
        Type* Get() const;

        /**
         * @brief Overridden function, that returns raw pointer to user data.
         * @return void* pointer to user data.
         */
        void* GetVoid() const override;

        /**
         * @brief Overridden function, that sets new value for object pointer.
         * @param t_newPtr new pointer.
         */
        void UpdatePtr(void* t_newPtr) override;

        /**
         * @brief Return number of references to controlled object.
         * @return uint32_t number of references to controlled object.
         */
        uint32_t UseCount() override;

        /**
         * @brief Method to dump SharedGcPtr structure in human-readable format.
         * @param t_out stream to write to.
         * @return std::ostream& passed as parameter stream
         */
        std::ostream& Print(std::ostream& t_out) const override;

        /**
         * @brief Check, if user tries to initialize SharedGcPtr with 
         * invalid object. If so, abort program.
         * @param t_obj a pointer to the object that is used to initialize ShareGcPtr
         */
        void CheckInvalidInitialization(Type* t_obj);
    };

    /**
     * @brief Method to construct new SharedGcPtr. It will allocate enough space, create
     * object and construct it.
     *
     * @tparam T type of user object.
     * @tparam Args type of variadic arguments to pass to user object constructor.
     * @param t_args variadic arguments to pass to user object constructor.
     * @return SharedGcPtr<T> constructed SharedGcPtr.
     */
    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... t_args);
}

// include templates implementation
#include "mpplib/shared_gcptr-imp.hpp"