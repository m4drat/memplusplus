#include "gtest/gtest.h"

#include "gtest_fixtures.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/mpp.hpp"
#include <memory>

TEST_F(GcTest, DoubleCollectSelfReference1_Issue88)
{
    using namespace mpp;

    class Vertex
    {
    private:
        SharedGcPtr<Vertex> m_gc;
        uint64_t m_data;

    public:
        explicit Vertex(uint64_t t_data)
            : m_data(t_data)
        {
        }

        Vertex()
            : m_data(0x13371337deadbeef)
        {
        }

        void AddPointer(const SharedGcPtr<Vertex>& t_ptr)
        {
            m_gc = t_ptr;
        }

        const SharedGcPtr<Vertex>& GetInternalPointer()
        {
            return m_gc;
        }

        uint64_t& GetData()
        {
            return m_data;
        }
    };

    mpp::SharedGcPtr<Vertex> ptr1 = mpp::MakeShared<Vertex>(0x1337);
    mpp::SharedGcPtr<Vertex> ptr2 = mpp::MakeShared<Vertex>(0xdead);

    EXPECT_TRUE(ptr1->GetData() == 0x1337);
    EXPECT_TRUE(ptr2->GetData() == 0xdead);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 2);

    mpp::SharedGcPtr<Vertex>& vtx_to_add = ptr1;
    mpp::SharedGcPtr<Vertex>& vtx_add_to = ptr2;
    vtx_add_to->AddPointer(vtx_to_add);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 3);
    EXPECT_TRUE(ptr1->GetData() == 0x1337);

    // Overwrite ptr1 with ptr2
    vtx_to_add = ptr2;
    vtx_add_to = ptr2;
    vtx_add_to->AddPointer(vtx_to_add);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 3);

    EXPECT_TRUE(ptr1->GetData() == 0xdead);
    EXPECT_TRUE(ptr2->GetData() == 0xdead);
    EXPECT_TRUE(ptr1->GetInternalPointer()->GetData() == 0xdead);
    EXPECT_TRUE(ptr2->GetInternalPointer()->GetData() == 0xdead);

    mpp::CollectGarbage();
    mpp::CollectGarbage();

    EXPECT_TRUE(ptr1->GetData() == 0xdead);
    EXPECT_TRUE(ptr2->GetData() == 0xdead);
    EXPECT_TRUE(ptr1->GetInternalPointer()->GetData() == 0xdead);
    EXPECT_TRUE(ptr2->GetInternalPointer()->GetData() == 0xdead);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 3);
}

TEST_F(GcTest, DoubleCollectSelfReference2_Issue88)
{
    using namespace mpp;

    class Vertex
    {
    private:
        std::array<SharedGcPtr<Vertex>, 16> m_gcs;
        uint64_t m_data;

    public:
        explicit Vertex(uint64_t t_data)
            : m_data(t_data)
        {
        }

        Vertex()
            : m_data(0x13371337deadbeef)
        {
        }

        void AddPointerAtIndex(uint32_t t_idx, const SharedGcPtr<Vertex>& t_ptr)
        {
            m_gcs.at(t_idx) = t_ptr;
        }

        const SharedGcPtr<Vertex>& GetPointerAtIndex(uint32_t t_idx)
        {
            return m_gcs.at(t_idx);
        }

        uint64_t& GetData()
        {
            return m_data;
        }
    };

    std::array<mpp::SharedGcPtr<Vertex>, 32> pointers;
    pointers.at(0) = mpp::MakeShared<Vertex>(0x1337);
    pointers.at(1) = mpp::MakeShared<Vertex>(0xdead);

    EXPECT_TRUE(pointers.at(0)->GetData() == 0x1337);
    EXPECT_TRUE(pointers.at(1)->GetData() == 0xdead);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 2);

    mpp::SharedGcPtr<Vertex>& vtx_to_add = pointers.at(0);
    mpp::SharedGcPtr<Vertex>& vtx_add_to = pointers.at(0);
    vtx_add_to->AddPointerAtIndex(1, vtx_to_add);
    EXPECT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 3);

    EXPECT_TRUE(pointers.at(0)->GetData() == 0x1337);
    EXPECT_TRUE(pointers.at(1)->GetData() == 0xdead);
    EXPECT_TRUE(pointers.at(0)->GetPointerAtIndex(1)->GetData() == 0x1337);

    // Crashes sometimes
    mpp::SharedGcPtr<Vertex>& vtx_to_add2 = pointers.at(1);
    mpp::SharedGcPtr<Vertex>& vtx_add_to2 = pointers.at(0);
    vtx_add_to2->AddPointerAtIndex(0, vtx_to_add2);
    EXPECT_TRUE(pointers.at(0)->GetPointerAtIndex(0)->GetData() == 0xdead);

    mpp::CollectGarbage();
    mpp::CollectGarbage();

    EXPECT_TRUE(pointers.at(0)->GetData() == 0x1337);
    EXPECT_TRUE(pointers.at(1)->GetData() == 0xdead);
    EXPECT_TRUE(pointers.at(0)->GetPointerAtIndex(1)->GetData() == 0x1337);
    EXPECT_TRUE(pointers.at(0)->GetPointerAtIndex(0)->GetData() == 0xdead);
}

TEST_F(GcTest, CreateCollectCreate)
{
    using namespace mpp;

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1);
    CollectGarbage();

    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(2);
    SharedGcPtr<int32_t> b2 = MakeShared<int32_t>(3);
    SharedGcPtr<int32_t> b3 = MakeShared<int32_t>(4);

    EXPECT_TRUE(*a1 == 1);
    EXPECT_TRUE(*b1 == 2);
    EXPECT_TRUE(*b2 == 3);
    EXPECT_TRUE(*b3 == 4);
}

TEST_F(GcTest, PointerToPointer)
{
    using namespace mpp;

    SharedGcPtr<SharedGcPtr<int32_t>> p =
        MakeShared<SharedGcPtr<int32_t>>(MakeShared<int32_t>(0x95782));
    EXPECT_TRUE(*p->Get() == 0x95782);
    CollectGarbage();

    EXPECT_TRUE(*p->Get() == 0x95782);
}

TEST_F(GcTest, CreatePointerOnHeapCollectGarbageAllocate)
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

    CollectGarbage();

    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1338);
    EXPECT_TRUE(*a1->ptr == 1337);
    EXPECT_TRUE(*b1 == 1338);
}

TEST_F(GcTest, CreateTwoObjectsDestroyCollectAndCreate)
{
    using namespace mpp;

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    SharedGcPtr<int32_t> a2 = MakeShared<int32_t>(1338);
    a1 = nullptr;

    CollectGarbage();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);

    EXPECT_TRUE(*a2 == 1338);
    EXPECT_TRUE(*b1 == 1339);
}

TEST_F(GcTest, CreateCycleOfLength3)
{
    using namespace mpp;

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

    CollectGarbage();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);

    EXPECT_TRUE(a1->data == 1);
    EXPECT_TRUE(a2->data == 2);
    EXPECT_TRUE(a3->data == 3);
}

TEST_F(GcTest, TestDanglingCyclesAreDestroyed)
{
    using namespace mpp;

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

    CollectGarbage();
    SharedGcPtr<int32_t> b1 = MakeShared<int32_t>(1339);
}

TEST_F(GcTest, ReferenceToItself1)
{
    using namespace mpp;

    struct alignas(64) ListNode
    {
        uint32_t index;
        uint32_t data;
        SharedGcPtr<ListNode> next;

        ListNode(uint32_t t_index, uint32_t t_data)
            : index(t_index)
            , data(t_data)
            , next(nullptr)
        {
        }
    };

    SharedGcPtr<ListNode> ptr = MakeShared<ListNode>(0, 0x1337);
    ptr->next = MakeShared<ListNode>(1, 0xdead);

    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(ptr->data == 0x1337);
    ASSERT_TRUE(ptr->next.UseCount() == 1);
    ASSERT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 2);
    ptr = ptr->next;
    ASSERT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 1);

    CollectGarbage();

    ASSERT_TRUE(ptr.UseCount() == 1);
    ASSERT_TRUE(ptr->data == 0xdead);
    ASSERT_TRUE(ptr->next == nullptr);
    ASSERT_TRUE(g_memoryManager->GetGC().GetGcPtrs().size() == 1);
}

TEST_F(GcTest, DISABLED_CollectX5)
{
    using namespace mpp;
}

TEST_F(GcTest, GcPtrsAreUpdatedAfterCollect)
{
    using namespace mpp;

    SharedGcPtr<int32_t> a1 = MakeShared<int32_t>(1337);
    void* rawPtrBeforeGcCollect = a1.GetVoid();
    CollectGarbage();

    EXPECT_TRUE(rawPtrBeforeGcCollect != a1.GetVoid());
}

/* For ctrl+c, ctrl+v
TEST(GcGraphTest, "")
{
    using namespace mpp;

}
*/