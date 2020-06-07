#include <iostream>

#include "mpplib/memory_allocator.hpp"
#include "mpplib/shared_gcptr.hpp"

using namespace mpp;

class UserData
{
private:
    int m_data{ 0 };
public:
    UserData(int val) : m_data{ val }
    {
        std::cout << "Created!\n";
    }

    ~UserData()
    {
        std::cout << "Deleted!\n";
    }
};

SharedGcPtr<UserData> foo()
{
    SharedGcPtr<UserData> p1 = MakeSharedGcPtr<UserData>(1337);
    return p1;
}

int main(int argc, char* argv[])
{
    SharedGcPtr<UserData> p0 = MakeSharedGcPtr<UserData>(1337);
    SharedGcPtr<UserData> p1(p0);
    SharedGcPtr<UserData> p2(p0);
    SharedGcPtr<UserData> p3(p0);
    SharedGcPtr<UserData> p4(p0);
    SharedGcPtr<UserData> p5(p0);

    MemoryManager::DumpStats(std::cout);
    MemoryManager::VisHeapLayout(std::cout);

    GC::Collect();

    return 0;
}