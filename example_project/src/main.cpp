#include <iostream>

#include "mpplib/gc.hpp"
#include "mpplib/shared_gcptr.hpp"
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
        // std::cout << "Created!\n";
    }

    ~UserData()
    {
        // std::cout << "Deleted!\n";
    }

    int GetData()
    {
        return m_data;
    }
};

// SharedGcPtr<UserData> foo()
// {
//     SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1337);
//     return p1;
// }

int main(int argc, char* argv[])
{
    using namespace mpp;

    // SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    // SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1338);
    // SharedGcPtr<UserData> p2 = MakeSharedGcPtr<UserData>(1339);
    // SharedGcPtr<UserData> p3 = MakeSharedGcPtr<UserData>(1340);
    // SharedGcPtr<UserData> p4 = MakeSharedGcPtr<UserData>(1341);
    // SharedGcPtr<UserData> p5 = MakeSharedGcPtr<UserData>(1342);

    // p0 = nullptr;
    // p2 = nullptr;
    // p4 = nullptr;

    // // MemoryManager::DumpStats(std::cout);
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;

    // std::cout << p1 << p1->GetData() << std::endl;
    // std::cout << p3 << p3->GetData() << std::endl;
    // std::cout << p5 << p5->GetData() << std::endl;

    // GC::Collect();

    // MemoryManager::VisHeapLayout(std::cout) << std::endl;

    // std::cout << p1 << p1->GetData() << std::endl;
    // std::cout << p3 << p3->GetData() << std::endl;
    // std::cout << p5 << p5->GetData() << std::endl;

    // MemoryManager::DumpStats(std::cout) << std::endl;

    // SharedGcPtr<char> ptr1((char*)MemoryAllocator::Allocate(64));
    // SharedGcPtr<char> ptr2 = ptr1;
    // ptr1.Swap(ptr2);
    // ptr1.Reset();

    // GC::Collect();

    // MemoryManager::ResetAllocatorState();

    return 0;
} 