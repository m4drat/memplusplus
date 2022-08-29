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

    // SharedGcPtr<SharedGcPtr<int32_t>> a =
    //     MakeShared<SharedGcPtr<int32_t>>(MakeShared<int32_t>(1337));

    // MM::VisHeapLayout(std::cout, nullptr);
    // for (auto p : GC::GetInstance().GetGcPtrs()) {
    //     std::cout << "(GcPtr*)" << p << " -> " << p->GetVoid() << std::endl;
    // }

    struct Node
    {
        SharedGcPtr<int32_t> ptr1;
        SharedGcPtr<int32_t> ptr2;
        SharedGcPtr<int32_t> ptr3;
        SharedGcPtr<Node> node;
        Node(SharedGcPtr<int32_t> t_ptr1, SharedGcPtr<int32_t> t_ptr2, SharedGcPtr<int32_t> t_ptr3)
            : ptr1{ t_ptr1 }
            , ptr2{ t_ptr2 }
            , ptr3{ t_ptr3 }
            , node{ nullptr }
        {
        }
    };

    SharedGcPtr<Node> n1 = MakeShared<Node>(nullptr, nullptr, nullptr);
    SharedGcPtr<int32_t> ptr = MakeShared<int32_t>(1337);

    n1->ptr1 = ptr;
    n1->ptr2 = ptr;
    n1->ptr3 = ptr;
    n1->node = MakeShared<Node>(nullptr, nullptr, nullptr);

    n1->node->ptr1 = MakeShared<int32_t>(1);
    n1->node->node = n1;

    ptr = nullptr;

    GC::GetInstance().Collect();
    // GC::GetInstance().Collect();
    // SharedGcPtr<int32_t> b = MakeShared<int32_t>(1337);
}

int main()
{
    logic();
    return 0;
}