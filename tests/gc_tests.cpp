#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/mpp.hpp"
#include <memory>

TEST(GcTest, CreateCollectCreate)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1);
    GC::GetInstance().Collect();

    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(2);
    SharedGcPtr<int32_t> b2 = MakeShared<int32_t>(3);
    SharedGcPtr<int32_t> b3 = MakeShared<int32_t>(4);

    EXPECT_TRUE(*a1 == 1);
    EXPECT_TRUE(*b1 == 2);
    EXPECT_TRUE(*b2 == 3);
    EXPECT_TRUE(*b3 == 4);
}

TEST(GcTest, PointerToPointer)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<SharedGcPtr<int32_t>> p =
        MakeShared<SharedGcPtr<int32_t>>(MakeShared<int32_t>(0x95782));
    EXPECT_TRUE(*p->Get() == 0x95782);
    GC::GetInstance().Collect();

    EXPECT_TRUE(*p->Get() == 0x95782);
}

TEST(GcTest, CreatePointerOnHeapCollectGarbageAllocate)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    struct Node
    {
        SharedGcPtr<int32_t> ptr;
        Node(SharedGcPtr<int32_t> t_ptr)
            : ptr{ t_ptr }
        {
        }
    };

    SharedGcPtr<Node> a1 = MakeShared<Node>(nullptr);
    a1->ptr = MakeShared<int32_t>(1337);

    void* rawPtrBeforeGc1 = a1.GetVoid();
    void* rawPtrBeforeGc2 = a1->ptr.GetVoid();

    GC::GetInstance().Collect();

    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1338);
    EXPECT_TRUE(*a1->ptr == 1337);
    EXPECT_TRUE(*b1 == 1338);
}

TEST(GcTest, CreateTwoObjectsDestroyCollectAndCreate)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    SharedGcPtr<int32_t> a2 = MakeShared<int32_t>(1338);
    a1 = nullptr;

    GC::GetInstance().Collect();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);

    EXPECT_TRUE(*a2 == 1338);
    EXPECT_TRUE(*b1 == 1339);
}

TEST(GcTest, CreateCycleOfLength3)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    struct Node
    {
        SharedGcPtr<Node> ptr;
        int32_t data;

        Node(SharedGcPtr<Node> t_node, int32_t t_data)
            : ptr{ t_node }
            , data{ t_data }
        {
        }
    };

    SharedGcPtr<Node> a1 = MakeShared<Node>(nullptr, 1);
    SharedGcPtr<Node> a2 = MakeShared<Node>(nullptr, 2);
    SharedGcPtr<Node> a3 = MakeShared<Node>(nullptr, 3);

    a1->ptr = a2;
    a2->ptr = a3;
    a3->ptr = a1;

    GC::GetInstance().Collect();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);

    EXPECT_TRUE(a1->data == 1);
    EXPECT_TRUE(a2->data == 2);
    EXPECT_TRUE(a3->data == 3);
}

TEST(GcTest, TestDanglingCyclesAreDestroyed)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    struct Node
    {
        SharedGcPtr<Node> ptr;
        int32_t data;

        Node(SharedGcPtr<Node> t_node, int32_t t_data)
            : ptr{ t_node }
            , data{ t_data }
        {
        }
    };

    {
        SharedGcPtr<Node> a1 = MakeShared<Node>(nullptr, 1);
        SharedGcPtr<Node> a2 = MakeShared<Node>(nullptr, 2);
        SharedGcPtr<Node> a3 = MakeShared<Node>(nullptr, 3);

        a1->ptr = a2;
        a2->ptr = a3;
        a3->ptr = a1;
    }

    GC::GetInstance().Collect();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);
}

TEST(GcTest, DISABLED_CollectX5)
{
    using namespace mpp;
}

TEST(GcTest, GcPtrsAreUpdatedAfterCollect)
{
    using namespace mpp;
    MM::ResetAllocatorState();

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    void* rawPtrBeforeGcCollect = a1.GetVoid();
    GC::GetInstance().Collect();

    EXPECT_TRUE(rawPtrBeforeGcCollect != a1.GetVoid());
}

/* For ctrl+c, ctrl+v
TEST(GcGraphTest, "")
{
    using namespace mpp;

}
*/