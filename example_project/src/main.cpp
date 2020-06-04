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
    SharedGcPtr<SharedGcPtr<UserData>> p0 = MakeSharedGcPtr<SharedGcPtr<UserData>>(MakeSharedGcPtr<UserData>(1337));
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // SharedGcPtr<UserData> p1 = foo();
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // SharedGcPtr<UserData> p2 = foo();
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // SharedGcPtr<UserData> p3 = foo();
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // SharedGcPtr<UserData> p4 = foo();
    // SharedGcPtr<UserData> p5(p4);
    // SharedGcPtr<UserData> p6 = p5;
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;
    // std::cout << p1 << std::endl;
    // std::cout << p2 << std::endl;
    // std::cout << p3 << std::endl;
    // std::cout << p4 << std::endl;
    // std::cout << p5 << std::endl;
    // std::cout << p6 << std::endl;
    // p1 = nullptr;
    // std::cout << p1 << std::endl;
    // std::cout << p2 << std::endl;
    // std::cout << p3 << std::endl;
    // std::cout << p4 << std::endl;
    // std::cout << p5 << std::endl;
    // std::cout << p6 << std::endl;
    // MemoryManager::VisHeapLayout(std::cout) << std::endl;

    return 0;
}