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
    char data[2048];

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
    using namespace mpp;
    using namespace std::literals::chrono_literals;

    SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1338);
    SharedGcPtr<UserData> p2 = MakeSharedGcPtr<UserData>(1339);
    SharedGcPtr<UserData> p3 = MakeSharedGcPtr<UserData>(1340);
    SharedGcPtr<UserData> p4 = MakeSharedGcPtr<UserData>(1341);
    SharedGcPtr<UserData> p5 = MakeSharedGcPtr<UserData>(1342);

    // std::vector<SharedGcPtr<UserData>> ptrs;

    // void* p0 = MemoryAllocator::Allocate(1024);
    // void* p1 = MemoryAllocator::Allocate(1024);
    // void* p2 = MemoryAllocator::Allocate(1024);
    // void* p3 = MemoryAllocator::Allocate(1024);
    // void* p4 = MemoryAllocator::Allocate(15);

    p2 = nullptr;
    p4 = nullptr;

    // MemoryAllocator::Deallocate(p0);
    // MemoryAllocator::Deallocate(p1);
    // MemoryAllocator::Deallocate(p2);
    // MemoryAllocator::Deallocate(p3);
    // MemoryAllocator::Deallocate(p4);
    // MemoryAllocator::Deallocate(p4);

    // for (uint32_t i = 0; i < 10000; ++i)
    //     ptrs.push_back(MakeSharedGcPtr<UserData>(1337));

    // for (uint32_t i = 0; i < 8000; i++)
    // {
    //     ptrs.at(rand() % ptrs.size()) = nullptr;
    // }

    // GC::GetInstance().Collect();

    // p1 = nullptr;
    // p2 = nullptr;

    // SharedGcPtr<UserData> p5 = MakeSharedGcPtr<UserData>(1342);
    // utils::Statistics::GetInstance().DumpStats(std::cout, true) << std::endl;
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;

    // std::cout << p1 << p1->GetData() << std::endl;
    // std::cout << p3 << p3->GetData() << std::endl;
    // std::cout << p5 << p5->GetData() << std::endl;

    GC::GetInstance().Collect();
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // utils::Statistics::GetInstance().DumpStats(std::cout, true, false, false) << std::endl;
}

int main()
{
    logic();
    return 0;
}