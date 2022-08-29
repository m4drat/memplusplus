#include "gtest/gtest.h"

#include "mpplib/chunk.hpp"
#include "mpplib/mpp.hpp"
#include <memory>

TEST(GcTest, CreateCollectCreate)
{
    using namespace mpp;

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

#if 0
TEST(GcTest, CreatePointerOnHeapCollectGarbageAllocate)
{
    using namespace mpp;

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

    ASSERT_EXIT(
        {
            SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1338);
            EXPECT_TRUE(*a1->ptr == 1337);
            EXPECT_TRUE(*b1 == 1338);
            exit(0);
        },
        ::testing::ExitedWithCode(0),
        ".*");
}

TEST(GcTest, CreateTwoObjectsDestroyCollectAndCreate)
{
    using namespace mpp;

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    SharedGcPtr<int32_t> a2 = MakeShared<int32_t>(1338);
    a1 = nullptr;

    GC::GetInstance().Collect();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);

    EXPECT_TRUE(*a1 == 1337);
    EXPECT_TRUE(*a2 == 1338);
    EXPECT_TRUE(*b1 == 1339);
}

TEST(GcTest, CollectX5)
{
    using namespace mpp;
}

TEST(GcTest, GcPtrsUpdatedAfterCollect)
{
    using namespace mpp;

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    void* rawPtrBeforeGcCollect = a1.GetVoid();
    GC::GetInstance().Collect();

    EXPECT_TRUE(rawPtrBeforeGcCollect != a1.GetVoid());
}

#endif

/* For ctrl+c, ctrl+v
TEST(GcGraphTest, "")
{
    using namespace mpp;

}
*/