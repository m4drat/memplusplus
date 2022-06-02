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
    {}

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
        SharedGcPtr<int32_t> ptr;
        Node(SharedGcPtr<int32_t> t_ptr)
            : ptr{ t_ptr }
        {}
    };

    // Create Linked List
    SharedGcPtr<Node> n1 = MakeShared<Node>(nullptr);
    n1->ptr = MakeShared<int32_t>(1337);

    GC::GetInstance().Collect();
    GC::GetInstance().Collect();
    SharedGcPtr<int32_t> b = MakeShared<int32_t>(1337);
}

int main()
{
    logic();
    return 0;
}