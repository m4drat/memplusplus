#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

using namespace mpp;
class UserData
{
private:
    int m_data{ 0 };

public:
    UserData(int val)
        : m_data{ val }
    {
    }

    int GetData()
    {
        return m_data;
    }
};

void logic()
{
    using namespace mpp;
    using namespace std::literals::chrono_literals;
    struct Node
    {
        uint32_t data;
        SharedGcPtr<Node> prev;
        SharedGcPtr<Node> next;

        Node(uint32_t t_data, SharedGcPtr<Node> t_p, SharedGcPtr<Node> t_n)
            : data{ t_data }
            , prev{ t_p }
            , next{ t_n }
        {
        }
    };

    // Create Linked List
    SharedGcPtr<Node> n1 = MakeShared<Node>(1, nullptr, nullptr);
    SharedGcPtr<Node> n2 = MakeShared<Node>(2, nullptr, nullptr);
    SharedGcPtr<Node> n3 = MakeShared<Node>(3, nullptr, nullptr);
    SharedGcPtr<Node> n4 = MakeShared<Node>(4, nullptr, nullptr);

    n1->prev = nullptr;
    n1->next = n2;

    n2->prev = n1;
    n2->next = n3;

    n3->prev = n2;
    n3->next = n4;

    n4->prev = n3;
    n4->next = nullptr;

    SharedGcPtr<int8_t> a = MakeShared<int8_t>(1);
    SharedGcPtr<int8_t> b = MakeShared<int8_t>(1);
    SharedGcPtr<SharedGcPtr<int8_t>> c = MakeShared<SharedGcPtr<int8_t>>(MakeShared<int8_t>(1));
    SharedGcPtr<int8_t> d = MakeShared<int8_t>(1);
    SharedGcPtr<int8_t> e = MakeShared<int8_t>(1);

    b = nullptr;
    d = nullptr;

    // Tree node
    struct TreeNode
    {
        uint32_t data;
        SharedGcPtr<TreeNode> left;
        SharedGcPtr<TreeNode> right;
        SharedGcPtr<TreeNode> up;

        TreeNode(uint32_t t_data,
                 SharedGcPtr<TreeNode> t_left,
                 SharedGcPtr<TreeNode> t_right,
                 SharedGcPtr<TreeNode> t_up)
            : data{ t_data }
            , left{ std::move(t_left) }
            , right{ std::move(t_right) }
            , up{ std::move(t_up) }
        {
        }
    };

    // Create a random tree
    SharedGcPtr<TreeNode> root = MakeShared<TreeNode>(0, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode1 = MakeShared<TreeNode>(1, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode2 = MakeShared<TreeNode>(2, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode3 = MakeShared<TreeNode>(3, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode4 = MakeShared<TreeNode>(4, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode5 = MakeShared<TreeNode>(5, nullptr, nullptr, nullptr);

    root->up = nullptr;
    root->left = treeNode1;
    root->right = treeNode2;

    treeNode1->up = root;
    treeNode1->left = nullptr;
    treeNode1->right = nullptr;

    treeNode2->up = root;
    treeNode2->left = treeNode3;
    treeNode2->right = treeNode4;

    treeNode3->up = treeNode2;
    treeNode3->left = nullptr;
    treeNode3->right = nullptr;

    treeNode4->up = treeNode2;
    treeNode4->left = treeNode5;
    treeNode4->right = nullptr;

    treeNode5->up = treeNode4;
    treeNode5->left = nullptr;
    treeNode5->right = nullptr;

    std::cout << "Before GC" << std::endl;
    MM::VisHeapLayout(std::cout, nullptr);

    GC::GetInstance().Collect();

    std::cout << "After GC" << std::endl;
    MM::VisHeapLayout(std::cout, nullptr);
}

int main()
{
    logic();
    return 0;
}