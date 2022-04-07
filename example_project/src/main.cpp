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

    char* ptr = (char*)MemoryManager::Allocate(1024);
    SharedGcPtr<char> a(ptr);
    SharedGcPtr<UserData> b = MakeSharedGcPtr<UserData>(1337);
    SharedGcPtr<UserData> c = MakeSharedGcPtr<UserData>(1337);
    SharedGcPtr<UserData> d = MakeSharedGcPtr<UserData>(1337);
    
    a = nullptr;
    // b = nullptr;
    c = nullptr;
    // d = nullptr;
    
    GC::GetInstance().Collect();
    // Should trigger invalid initialization
    // SharedGcPtr<char> b(ptr);
}

int main()
{
    logic();
    return 0;
}