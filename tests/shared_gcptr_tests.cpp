#include "gtest/gtest.h"

#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"

TEST(SharedGcPtrTests, EmptyConstructor)
{
    using namespace mpp;

    SharedGcPtr<char> ptr;
    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
}

TEST(SharedGcPtrTests, NullptrConstructor)
{
    using namespace mpp;

    SharedGcPtr<char> ptr(nullptr);

    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
}

TEST(SharedGcPtrTests, ExplicitConstructor)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr((char*)MemoryManager::Allocate(40));

    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST(SharedGcPtrTests, AssignToRValueRef)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr = SharedGcPtr<char>(data1);

    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(ptr.Get() == data1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST(SharedGcPtrTests, AssignToConstReference)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    char* data1 = (char*)MemoryManager::Allocate(40);
    char* data2 = (char*)MemoryManager::Allocate(40);

    SharedGcPtr<char> ptr1(data1);
    SharedGcPtr<char> ptr2(data2);

    ASSERT_TRUE(ptr1.UseCount() == 1);
    ASSERT_TRUE(ptr1.Get() == data1);
    ASSERT_TRUE(ptr2.UseCount() == 1);
    ASSERT_TRUE(ptr2.Get() == data2);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 2);

    ptr1 = ptr2;

    ASSERT_TRUE(ptr1.UseCount() == 2);
    ASSERT_TRUE(ptr1.Get() == data2);
    ASSERT_TRUE(ptr2.UseCount() == 2);
    ASSERT_TRUE(ptr2.Get() == data2);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 2);
}

TEST(SharedGcPtrTests, AssignToTypePtr)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr1 = nullptr;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
    ASSERT_TRUE(ptr1.UseCount() == 1);
    ASSERT_TRUE(ptr1.Get() == nullptr);

    ptr1 = data1;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
    ASSERT_TRUE(ptr1.UseCount() == 1);
    ASSERT_TRUE(ptr1.Get() == data1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST(SharedGcPtrTests, AssignToNullptr)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1 = nullptr;

    ASSERT_TRUE(ptr1.UseCount() == 1);
    ASSERT_TRUE(ptr1.Get() == nullptr);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
}

TEST(SharedGcPtrTests, FunctionCallWithSharedPtr)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    char* data1 = (char*)MemoryManager::Allocate(40);
    SharedGcPtr<char> ptr1(data1);
    ASSERT_TRUE(ptr1.UseCount() == 1);

    auto function = [&](SharedGcPtr<char> t_ptr) -> int32_t {
        EXPECT_TRUE(t_ptr.UseCount() == 2);
        EXPECT_TRUE(ptr1.UseCount() == 2);
        return t_ptr.UseCount();
    };

    function(ptr1);

    ASSERT_TRUE(ptr1.UseCount() == 1);
}

TEST(SharedGcPtrTests, MultiplePointersToTheSameObject)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1(nullptr);
    SharedGcPtr<char> ptr2(ptr1);
    SharedGcPtr<char> ptr3(ptr2);
    SharedGcPtr<char> ptr4(ptr3);

    ASSERT_TRUE(ptr1.UseCount() == 4);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
}

TEST(SharedGcPtrTests, CreateNewPtrAssignment)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1(nullptr);
    SharedGcPtr<char> ptr2(ptr1);
    SharedGcPtr<char> ptr3(ptr2);
    SharedGcPtr<char> ptr4(ptr3);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());

    ptr1 = (char*)MemoryManager::Allocate(64);

    ASSERT_TRUE((ptr1.UseCount() == 1 && ptr2.UseCount() == 3 && ptr3.UseCount() == 3 &&
                 ptr4.UseCount() == 3));
    ASSERT_TRUE((ptr2 == nullptr && ptr3 == nullptr && ptr4 == nullptr));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST(SharedGcArrayTests, MakeSharedNCallsCtorsDtors)
{
    using namespace mpp;
    MM::ResetAllocatorState();

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

        ~Data()
        {
            (*m_dtorCallsN)++;
        }
    };

    SharedGcPtr<Data[]> dataPtrs = MakeSharedN<Data>(5, &ctorCallsN, &dtorCallsN);
    dataPtrs = nullptr;

    ASSERT_TRUE(ctorCallsN == 5);
    ASSERT_TRUE(dtorCallsN == 5);

    ctorCallsN = 0;
    dtorCallsN = 0;

    uint32_t length = 12;
    SharedGcPtr<Data[]> dataPtrs2 = MakeSharedN<Data>(length, &ctorCallsN, &dtorCallsN);
    dataPtrs2 = nullptr;

    ASSERT_TRUE(ctorCallsN == 12);
    ASSERT_TRUE(dtorCallsN == 12);
}

TEST(SharedGcArrayTests, MakeSharedCallsCtorDtor)
{
    using namespace mpp;
    MM::ResetAllocatorState();

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

        ~Data()
        {
            (*m_dtorCallsN)++;
        }
    };

    SharedGcPtr<Data> dataPtr = MakeShared<Data>(&ctorCallsN, &dtorCallsN);
    dataPtr = nullptr;

    ASSERT_TRUE(ctorCallsN == 1);
    ASSERT_TRUE(dtorCallsN == 1);
}

TEST(SharedGcArrayTests, GetArraySize)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t[]> dataPtr1 = MakeSharedN<int32_t>(7);
    ASSERT_TRUE(dataPtr1.GetArraySize() == 7);

    SharedGcPtr<int32_t[]> dataPtr2;
    ASSERT_TRUE(dataPtr2.GetArraySize() == 0);

    dataPtr2 = MakeSharedN<int32_t>(10);
    ASSERT_TRUE(dataPtr2.GetArraySize() == 10);

    dataPtr1.Swap(dataPtr2);

    ASSERT_TRUE(dataPtr1.GetArraySize() == 10);
    ASSERT_TRUE(dataPtr2.GetArraySize() == 7);
}

TEST(SharedGcArrayTests, AccessElemetsByIndex)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t[]> dataPtr1 = MakeSharedN<int32_t>(3, 1337);
    ASSERT_TRUE(dataPtr1.GetArraySize() == 3);

    ASSERT_TRUE(dataPtr1[0] == 1337);
    ASSERT_TRUE(dataPtr1[1] == 1337);
    ASSERT_TRUE(dataPtr1[2] == 1337);
}

TEST(SharedGcArrayTests, SharedPtrPointingToAnArrayOfSharedPtrs)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<SharedGcPtr<int32_t>[]> dataPtr1 = MakeSharedN<SharedGcPtr<int32_t>>(3);
    ASSERT_TRUE(dataPtr1.GetArraySize() == 3);

    dataPtr1[0] = MakeShared<int32_t>(1337);
    dataPtr1[1] = MakeShared<int32_t>(1338);
    dataPtr1[2] = MakeShared<int32_t>(1339);

    ASSERT_TRUE(*dataPtr1[0].Get() == 1337);
    ASSERT_TRUE(*dataPtr1[1].Get() == 1338);
    ASSERT_TRUE(*dataPtr1[2].Get() == 1339);
}

TEST(SharedGcArrayTests, SharedPtrCreateCopy)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t[]> dataPtr1 = MakeSharedN<int32_t>(3, 1337);
    ASSERT_TRUE(dataPtr1.GetArraySize() == 3);

    for (uint32_t i = 0; i < dataPtr1.GetArraySize(); i++)
        ASSERT_TRUE(dataPtr1[i] == 1337);

    auto dataPtr2 = dataPtr1;
    ASSERT_TRUE(dataPtr2.GetArraySize() == 3);
    for (uint32_t i = 0; i < dataPtr2.GetArraySize(); i++)
        ASSERT_TRUE(dataPtr2[i] == 1337);

    SharedGcPtr<int32_t[]> dataPtr3 = nullptr;
    dataPtr3 = dataPtr1;
    ASSERT_TRUE(dataPtr3.GetArraySize() == 3);
    for (uint32_t i = 0; i < dataPtr3.GetArraySize(); i++)
        ASSERT_TRUE(dataPtr3[i] == 1337);
}

TEST(SharedGcPtrTests, IntegrationTest_1)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr2((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr3((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr4((char*)MemoryManager::Allocate(64));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 4);
    ASSERT_TRUE((ptr1.UseCount() == 1 && ptr2.UseCount() == 1 && ptr3.UseCount() == 1 &&
                 ptr4.UseCount() == 1));

    ptr1 = nullptr;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 3);

    ptr1 = ptr4;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 4);
    ASSERT_TRUE(ptr1.UseCount() == 2);
    ASSERT_TRUE(ptr4.UseCount() == 2);

    ptr2 = SharedGcPtr<char>(nullptr);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 3);
    ASSERT_TRUE(ptr2.UseCount() == 1);

    ptr1 = ptr2;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 2);
    ASSERT_TRUE(ptr1.UseCount() == 2);
    ASSERT_TRUE(ptr2.UseCount() == 2);

    ptr3 = ptr2;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
    ASSERT_TRUE(ptr3.UseCount() == 3);
    ASSERT_TRUE(ptr2.UseCount() == 3);

    ptr4 = ptr2;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
    ASSERT_TRUE(ptr2.UseCount() == 4);
    ASSERT_TRUE(ptr4.UseCount() == 4);
}

TEST(SharedGcPtrTests, IntegrationTest_2)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1((char*)MemoryManager::Allocate(64));
    SharedGcPtr<char> ptr2 = ptr1;
    SharedGcPtr<char> ptr3 = ptr1;

    ASSERT_TRUE(ptr1.UseCount() == 3);
    ASSERT_TRUE(ptr2.UseCount() == 3);
    ASSERT_TRUE(ptr3.UseCount() == 3);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 3);

    ptr1.Reset();
    ASSERT_TRUE(ptr1.UseCount() == 1);
    ASSERT_TRUE(ptr2.UseCount() == 2);
    ASSERT_TRUE(ptr3.UseCount() == 2);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 2);

    ptr2.Reset();
    ASSERT_TRUE(ptr2.UseCount() == 1);
    ASSERT_TRUE(ptr3.UseCount() == 1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr3 = (char*)MemoryManager::Allocate(64);
    ASSERT_TRUE(ptr3.UseCount() == 1);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr3 = ptr1;
    ASSERT_TRUE(ptr3.UseCount() == 2);
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());
}

TEST(SharedGcPtrTests, IntegrationTest_3)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1 = nullptr;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1 = nullptr;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());

    SharedGcPtr<char> ptr2(SharedGcPtr<char>((char*)MemoryManager::Allocate(64)));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
    ASSERT_TRUE(ptr2.GetVoid() != nullptr);

    SharedGcPtr<char> ptr3(SharedGcPtr<char>(nullptr));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);
}

TEST(SharedGcPtrTests, IntegrationTest_4)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<char> ptr1 = nullptr;
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());

    ptr1 = SharedGcPtr<char>((char*)MemoryManager::Allocate(64));
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().size() == 1);

    ptr1.Reset();
    ASSERT_TRUE(GC::GetInstance().GetGcPtrs().empty());

    SharedGcPtr<char> ptr2 = ptr1;
}