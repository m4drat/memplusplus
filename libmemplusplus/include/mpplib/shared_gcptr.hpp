#pragma once

#include <iostream>
#include <type_traits>
#include <utility>

#include "mpplib/gc.hpp"
#include "mpplib/gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

namespace mpp {
    template<bool Type>
    class SharedGcPtrArray
    {
    protected:
        /**
         * @brief Size of the created array
         */
        uint32_t m_arraySize = 0;
    };

    template<>
    class SharedGcPtrArray<false>
    {
    };

    /**
     * @brief SharedGcPtr class. Behaves like normal shared ptr.
     * @tparam Type of user object.
     */
    template<class Type>
    class SharedGcPtr
        : public SharedGcPtrArray<std::is_array<Type>::value>
        , public GcPtr
    {
        // static_assert(offsetof(SharedGcPtr<Type>, m_objectPtr) == 10,
        //               "m_objectPtr must be at offset 10");

        friend class GC;

    protected:
        using ElementType = typename std::remove_extent<Type>::type;

        /**
         * @brief pointer to object.
         */
        ElementType* m_objectPtr{ nullptr };

        /**
         * @brief Number of references to the object.
         */
        uint32_t* m_references{ nullptr };

        /**
         * @brief Releases the object, decrementing m_references.
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
        explicit SharedGcPtr(ElementType* t_obj);

        /**
         * @brief Copy-Constructor to construct from const SharedGcPtr reference.
         * @param t_other rvalue reference to another SharedGcPtr
         */
        SharedGcPtr(const SharedGcPtr<Type>& t_other);

        /**
         * @brief Copy-Constructor to construct from const SharedGcPtr rvalue reference.
         * @param t_other const reference to another SharedGcPtr
         */
        SharedGcPtr(SharedGcPtr<Type>&& t_other) noexcept;

        /**
         * @brief Construct SharedGcPtr which holds an array of objects of type ElementType
         * @param t_obj pointer to user object.
         * @param t_arraySize size of the array.
         */
        SharedGcPtr(Type t_obj, uint32_t t_arraySize);

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
        ElementType* operator->() const noexcept;

        /**
         * @brief Allows to use smart pointers as usual pointers.
         * @return Type& reference to user data
         */
        ElementType& operator*() const noexcept;

        /**
         * @brief Allows automatic conversions to bool.
         */
        explicit operator bool() const;

        /**
         * @brief Calculates distance between two pointers
         */
        std::ptrdiff_t operator-(const SharedGcPtr<Type>& t_other) const noexcept;

        /**
         * @brief Retrieves element from the array by its index
         * @param t_index - index to access
         */
        ElementType& operator[](std::ptrdiff_t t_index) const noexcept;

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
        void Reset(std::nullptr_t);

        /**
         * @brief Calls object destructor and deallocates memory
         */
        void Destroy();

        /**
         * @brief Performs swap operation on two SharedGcPtr's.
         * @param t_other reference to SharedGcPtr to swap with.
         */
        void Swap(SharedGcPtr& t_other);

        /**
         * @brief Returns raw pointer to user data.
         * @return Type* raw pointer to user data
         */
        ElementType* Get() const noexcept;

        /**
         * @brief Overridden function, that returns raw pointer to user data.
         * @return void* pointer to user data.
         */
        void* GetVoid() const noexcept override;

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
         * @brief If this smart pointer is an array - return its size
         * @return uint32_t array size pointed to by current SharedPtr
         */
        uint32_t GetArraySize();

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
        void CheckInvalidInitialization(ElementType* t_obj);
    };

    /**
     * @brief Method to construct new SharedGcPtr. It will allocate enough space, create
     * object and construct it.
     * @tparam T type of user object.
     * @tparam Args type of variadic arguments to pass to user object constructor.
     * @param t_args variadic arguments to pass to user object constructor.
     * @return SharedGcPtr<T> constructed SharedGcPtr.
     */
    template<class Type, class... Args>
    SharedGcPtr<Type> MakeShared(Args&&... t_args);

    /**
     * @brief Method to construct new SharedGcPtr that holds an array.
     * It will allocate enough space, create object and construct it.
     *
     * @tparam T type of user object.
     * @tparam Args type of variadic arguments to pass to user object constructor.
     * @param t_size array length
     * @param t_args variadic arguments to pass to user object constructor.
     * @return SharedGcPtr<T> SharedGcPtr with constructed objects array.
     */
    template<class Type, class... Args>
    SharedGcPtr<Type[]> MakeSharedN(uint32_t t_size, Args&&... t_args);
}

// include templates implementation
#include "mpplib/shared_gcptr-imp.hpp"