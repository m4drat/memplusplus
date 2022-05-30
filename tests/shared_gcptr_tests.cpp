#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("Empty constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr;
    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
}

TEST_CASE("Nullptr constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr(nullptr);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
}

TEST_CASE("Explicit constructor")
{
    using namespace mpp;

    SharedGcPtr<char> ptr((char*)MemoryManager::Allocate(40));

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to R-value reference")
{
    using namespace mpp;

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr = SharedGcPtr<char>(data1);

    REQUIRE(ptr.UseCount() == 1);
    REQUIRE(ptr.Get() == data1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to const reference")
{
    using namespace mpp;

    char* data1 = (char*)MemoryManager::Allocate(40);
    char* data2 = (char*)MemoryManager::Allocate(40);

    SharedGcPtr<char> ptr1(data1);
    SharedGcPtr<char> ptr2(data2);

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
    REQUIRE(ptr2.UseCount() == 1);
    REQUIRE(ptr2.Get() == data2);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 2);

    ptr1 = ptr2;

    REQUIRE(ptr1.UseCount() == 2);
    REQUIRE(ptr1.Get() == data2);
    REQUIRE(ptr2.UseCount() == 2);
    REQUIRE(ptr2.Get() == data2);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 2);
}

TEST_CASE("Assign to Type*")
{
    using namespace mpp;

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr1 = nullptr;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);

    ptr1 = data1;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == data1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST_CASE("Assign to nullptr")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1 = nullptr;

    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr1.Get() == nullptr);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
}

TEST_CASE("Function call with shared ptr in parameters")
{
    using namespace mpp;

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr1(data1);
    REQUIRE(ptr1.UseCount() == 1);

    auto foo = [&](SharedGcPtr<char> t_ptr) {
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
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
}

TEST_CASE("Create new pointer through assignment")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1(nullptr);
    SharedGcPtr<char> ptr2(ptr1);
    SharedGcPtr<char> ptr3(ptr2);
    SharedGcPtr<char> ptr4(ptr3);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);

    ptr1 = (char*)MemoryManager::Allocate(64);

    REQUIRE((ptr1.UseCount() == 1 && ptr2.UseCount() == 3 && ptr3.UseCount() == 3 &&
             ptr4.UseCount() == 3));
    REQUIRE((ptr2 == nullptr && ptr3 == nullptr && ptr4 == nullptr));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST_CASE("Make shared array - elements access")
{
    using namespace mpp;

    // SharedGcPtr<int32_t[]> a;
}

TEST_CASE("Test MakeSharedN works correctly (ctors/dtors)")
{
    using namespace mpp;

    int32_t ctorCallsN = 0;
    int32_t dtorCallsN = 0;

    class Data
    {
    private:
        int32_t* m_ctorCallsN;
        int32_t* m_dtorCallsN;

    public:
        Data(int32_t* t_ctorCallsN, int32_t* t_dtorCallsN)
            : m_ctorCallsN(t_ctorCallsN)
            , m_dtorCallsN(t_dtorCallsN)
        {
            (*m_ctorCallsN)++;
        }

        ~Data() {
            (*m_dtorCallsN)++;
        }
    };

    SharedGcPtr<Data[]> dataPtrs = MakeSharedN<Data>(5, &ctorCallsN, &dtorCallsN);
    dataPtrs = nullptr;

    REQUIRE(ctorCallsN == 5);
    REQUIRE(dtorCallsN == 5);

    ctorCallsN = 0;
    dtorCallsN = 0;

    uint32_t length = 12;
    SharedGcPtr<Data[]> dataPtrs2 = MakeSharedN<Data>(length, &ctorCallsN, &dtorCallsN);
    dataPtrs2 = nullptr;

    REQUIRE(ctorCallsN == 12);
    REQUIRE(dtorCallsN == 12);
}

TEST_CASE("Test MakeShared works correctly (ctor/dtor)")
{
    using namespace mpp;

    int32_t ctorCallsN = 0;
    int32_t dtorCallsN = 0;

    class Data
    {
    private:
        int32_t* m_ctorCallsN;
        int32_t* m_dtorCallsN;

    public:
        Data(int32_t* t_ctorCallsN, int32_t* t_dtorCallsN)
            : m_ctorCallsN(t_ctorCallsN)
            , m_dtorCallsN(t_dtorCallsN)
        {
            (*m_ctorCallsN)++;
        }

        ~Data() {
            (*m_dtorCallsN)++;
        }
    };

    SharedGcPtr<Data> dataPtr = MakeShared<Data>(&ctorCallsN, &dtorCallsN);
    dataPtr = nullptr;

    REQUIRE(ctorCallsN == 1);
    REQUIRE(dtorCallsN == 1);
}

TEST_CASE("Test GetArraySize")
{
    using namespace mpp;

    SharedGcPtr<int32_t[]> dataPtr1 = MakeSharedN<int32_t>(7);
    REQUIRE(dataPtr1.GetArraySize() == 7);

    SharedGcPtr<int32_t[]> dataPtr2;
    REQUIRE(dataPtr2.GetArraySize() == 0);

    dataPtr2 = MakeSharedN<int32_t>(10);
    REQUIRE(dataPtr2.GetArraySize() == 10);

    dataPtr1.Swap(dataPtr2);

    REQUIRE(dataPtr1.GetArraySize() == 10);
    REQUIRE(dataPtr2.GetArraySize() == 7);
}

TEST_CASE("Test access element by index")
{
    using namespace mpp;

    SharedGcPtr<int32_t[]> dataPtr1 = MakeSharedN<int32_t>(3, 1337);
    REQUIRE(dataPtr1.GetArraySize() == 3);

    REQUIRE(dataPtr1[0] == 1337);
    REQUIRE(dataPtr1[1] == 1337);
    REQUIRE(dataPtr1[2] == 1337);
}

TEST_CASE("Integration test - 1")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr2((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr3((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr4((char*)MemoryManager::Allocate(64));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 4);
    REQUIRE((ptr1.UseCount() == 1 && ptr2.UseCount() == 1 && ptr3.UseCount() == 1 &&
             ptr4.UseCount() == 1));

    ptr1 = nullptr;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 3);

    ptr1 = ptr4;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 4);
    REQUIRE(ptr1.UseCount() == 2);
    REQUIRE(ptr4.UseCount() == 2);

    ptr2 = SharedGcPtr<char>(nullptr);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 3);
    REQUIRE(ptr2.UseCount() == 1);

    ptr1 = ptr2;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 2);
    REQUIRE(ptr1.UseCount() == 2);
    REQUIRE(ptr2.UseCount() == 2);

    ptr3 = ptr2;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
    REQUIRE(ptr3.UseCount() == 3);
    REQUIRE(ptr2.UseCount() == 3);

    ptr4 = ptr2;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
    REQUIRE(ptr2.UseCount() == 4);
    REQUIRE(ptr4.UseCount() == 4);
}

TEST_CASE("Integration test - 2")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr2 = ptr1;
    SharedGcPtr<char> ptr3 = ptr1;

    REQUIRE(ptr1.UseCount() == 3);
    REQUIRE(ptr2.UseCount() == 3);
    REQUIRE(ptr3.UseCount() == 3);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 3);

    ptr1.Reset();
    REQUIRE(ptr1.UseCount() == 1);
    REQUIRE(ptr2.UseCount() == 2);
    REQUIRE(ptr3.UseCount() == 2);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 2);

    ptr2.Reset();
    REQUIRE(ptr2.UseCount() == 1);
    REQUIRE(ptr3.UseCount() == 1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr3 = (char*)MemoryManager::Allocate(64);
    REQUIRE(ptr3.UseCount() == 1);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr3 = ptr1;
    REQUIRE(ptr3.UseCount() == 2);
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);
}

TEST_CASE("Integration test - 3")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1 = nullptr;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1 = nullptr;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);

    SharedGcPtr<char> ptr2(SharedGcPtr<char>((char*)MemoryManager::Allocate(64)));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
    REQUIRE(ptr2.GetVoid() != nullptr);

    SharedGcPtr<char> ptr3(SharedGcPtr<char>(nullptr));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST_CASE("Integration test - 4")
{
    using namespace mpp;

    SharedGcPtr<char> ptr1 = nullptr;
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1.Reset();
    REQUIRE(GC::GetInstance().GetGcPtrs().size() == 0);

    SharedGcPtr<char> ptr2 = ptr1;
}