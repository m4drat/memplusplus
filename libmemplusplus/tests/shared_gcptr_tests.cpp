#include "catch2/catch.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/gc.hpp"

TEST_CASE("Empty constructor")
{
    mpp::SharedGcPtr<char> ptr;
    REQUIRE(ptr.UseCount() == 1);
}

TEST_CASE("Nullptr constructor")
{
    mpp::SharedGcPtr<char> ptr(nullptr);

    REQUIRE(ptr.UseCount() == 1);
}

TEST_CASE("Explicit constructor")
{
    mpp::SharedGcPtr<char> ptr(new char[40]);

    REQUIRE(ptr.UseCount() == 1);
}

TEST_CASE("Assign to R-value reference")
{
    char* data1 = new char[40];
    mpp::SharedGcPtr<char> ptr = mpp::SharedGcPtr<char>(data1);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(ptr.Get() == data1);
}

TEST_CASE("Assign to const reference")
{
    char* data1 = new char[40];
    char* data2 = new char[40];

    mpp::SharedGcPtr<char> ptr1(data1);
    mpp::SharedGcPtr<char> ptr2(data2);
    
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
    REQUIRE(ptr2.UseCount() == 1);
    REQUIRE(ptr2.Get() == data2);

    ptr1 = ptr2;

    REQUIRE(ptr1.UseCount() == 2);
    REQUIRE(ptr1.Get() == data2);
    REQUIRE(ptr2.UseCount() == 2);
    REQUIRE(ptr2.Get() == data2);
}

TEST_CASE("Assign to Type*")
{
    char* data1 = new char[40];
    mpp::SharedGcPtr<char> ptr1 = nullptr;
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);

    ptr1 = data1;

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
}

TEST_CASE("Assign to nullptr")
{
    mpp::SharedGcPtr<char> ptr1 = nullptr;

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);
}

TEST_CASE("Function call with shared ptr in parameters")
{
    char* data1 = new char[40];
    mpp::SharedGcPtr<char> ptr1(data1);
    REQUIRE(ptr1.UseCount() == 1);

    auto foo = [&](mpp::SharedGcPtr<char> t_ptr)
    {
        REQUIRE(t_ptr.UseCount() == 2);
        REQUIRE(ptr1.UseCount() == 2);
        return t_ptr.UseCount();
    };

    foo(ptr1);

    REQUIRE(ptr1.UseCount() == 1);
}

TEST_CASE("Multiple pointers to the same object")
{
    mpp::SharedGcPtr<char> ptr1(nullptr);
    mpp::SharedGcPtr<char> ptr2(ptr1);
    mpp::SharedGcPtr<char> ptr3(ptr2);
    mpp::SharedGcPtr<char> ptr4(ptr3);

    REQUIRE(ptr1.UseCount() == 4);
}

TEST_CASE("Create new pointer through assigment")
{
    mpp::SharedGcPtr<char> ptr1(nullptr);
    mpp::SharedGcPtr<char> ptr2(ptr1);
    mpp::SharedGcPtr<char> ptr3(ptr2);
    mpp::SharedGcPtr<char> ptr4(ptr3);

    ptr1 = new char[20];

    REQUIRE((ptr1.UseCount() == 1 && ptr2.UseCount() == 3 &&
             ptr3.UseCount() == 3 && ptr4.UseCount() == 3));
}

