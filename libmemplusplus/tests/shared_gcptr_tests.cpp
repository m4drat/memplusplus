#include "catch2/catch.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/gc.hpp"

TEST_CASE("Empty constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr;
    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetGcPtrs().size() == 0);
}

TEST_CASE("Nullptr constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr(nullptr);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetGcPtrs().size() == 0);
}

TEST_CASE("Explicit constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr(new char[40]);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to R-value reference")
{
    using namespace mpp;

    char* data1 = new char[40];
    SharedGcPtr<char> ptr = SharedGcPtr<char>(data1);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(ptr.Get() == data1);
    REQUIRE(GC::GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to const reference")
{
    using namespace mpp;

    char* data1 = new char[40];
    char* data2 = new char[40];

    SharedGcPtr<char> ptr1(data1);
    SharedGcPtr<char> ptr2(data2);
    
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
    REQUIRE(ptr2.UseCount() == 1);
    REQUIRE(ptr2.Get() == data2);
    REQUIRE(GC::GetGcPtrs().size() == 2);

    ptr1 = ptr2;

    REQUIRE(ptr1.UseCount() == 2);
    REQUIRE(ptr1.Get() == data2);
    REQUIRE(ptr2.UseCount() == 2);
    REQUIRE(ptr2.Get() == data2);
    REQUIRE(GC::GetGcPtrs().size() == 2);
}

TEST_CASE("Assign to Type*")
{
    using namespace mpp;

    char* data1 = new char[40];
    SharedGcPtr<char> ptr1 = nullptr;
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);

    ptr1 = data1;

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
    REQUIRE(GC::GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to nullptr")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1 = nullptr;

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);
    REQUIRE(GC::GetGcPtrs().size() == 1);
}

TEST_CASE("Function call with shared ptr in parameters")
{
    using namespace mpp;

    char* data1 = new char[40];
    SharedGcPtr<char> ptr1(data1);
    REQUIRE(ptr1.UseCount() == 1);

    auto foo = [&](SharedGcPtr<char> t_ptr)
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
    using namespace mpp;

    SharedGcPtr<char> ptr1(nullptr);
    SharedGcPtr<char> ptr2(ptr1);
    SharedGcPtr<char> ptr3(ptr2);
    SharedGcPtr<char> ptr4(ptr3);

    REQUIRE(ptr1.UseCount() == 4);
    REQUIRE(GC::GetGcPtrs().size() == 0);
}

TEST_CASE("Create new pointer through assigment")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1(nullptr);
    SharedGcPtr<char> ptr2(ptr1);
    SharedGcPtr<char> ptr3(ptr2);
    SharedGcPtr<char> ptr4(ptr3);
    REQUIRE(GC::GetGcPtrs().size() == 0);

    ptr1 = new char[20];

    REQUIRE((ptr1.UseCount() == 1 && ptr2.UseCount() == 3 &&
             ptr3.UseCount() == 3 && ptr4.UseCount() == 3));
    REQUIRE(GC::GetGcPtrs().size() == 4);
}

// TEST_CASE("")
// {
//     mpp::SharedGcPtr<char> ptr1(nullptr);
//     mpp::SharedGcPtr<char> ptr2(new char[64]);
// }

