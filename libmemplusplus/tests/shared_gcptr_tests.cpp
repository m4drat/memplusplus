#include "main_config.hpp"
#include "mpplib/shared_gcptr.hpp"

TEST_CASE("Nullptr references")
{
    mpp::SharedGcPtr<char> ptr(nullptr);

    REQUIRE(ptr.UseCount() == 1);
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

// TEST_CASE("positive difference")
// {
//     GC gc;

//     char *ptr1 = (char*)(0x1000), *ptr2 = (char*)(0x1020);

//     ptrdiff_t diff = gc.CalcDist(ptr2, ptr1);

//     REQUIRE(diff > 0);
// }