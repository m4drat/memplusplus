#include <iostream>

#include "mpplib/gc.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/profiler_definitions.hpp"
#include <memory>

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

    ~UserData()
    {
    }

    int GetData()
    {
        return m_data;
    }
};

void logic()
{
    PROFILE_FUNCTION();
    using namespace mpp;
    using namespace std::literals::chrono_literals;

    SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1338);
    SharedGcPtr<UserData> p2 = MakeSharedGcPtr<UserData>(1339);
    SharedGcPtr<UserData> p3 = MakeSharedGcPtr<UserData>(1340);
    SharedGcPtr<UserData> p4 = MakeSharedGcPtr<UserData>(1341);
    SharedGcPtr<UserData> p5 = MakeSharedGcPtr<UserData>(1342);

    std::vector<SharedGcPtr<UserData>> ptrs;

    for (uint32_t i = 0; i < 10000; ++i)
        ptrs.push_back(MakeSharedGcPtr<UserData>(1337));

    for (uint32_t i = 0; i < 8000; i++)
    {
        ptrs.at(rand() % ptrs.size()) = nullptr;
    }
    
    p0 = nullptr;
    p2 = nullptr;
    p4 = nullptr;

    utils::Statistics::GetInstance().DumpStats(std::cout, true) << std::endl;
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;

    std::cout << p1 << p1->GetData() << std::endl;
    std::cout << p3 << p3->GetData() << std::endl;
    std::cout << p5 << p5->GetData() << std::endl;

    GC::GetInstance().Collect();
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
}

int main()
{
    PROFILE_FUNCTION();
    logic();
    return 0;
}