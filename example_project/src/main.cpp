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

    char* ptr = (char*)MemoryAllocator::Allocate(1024);
    SharedGcPtr<char> a(ptr);
    auto b = a;
    auto c = a;
    auto d = a;
    auto e = c;
    auto f = c;
    // Should trigger invalid initialization
    // SharedGcPtr<char> b(ptr);
}

int main()
{
    logic();
    return 0;
}