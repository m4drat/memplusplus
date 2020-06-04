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
    // SharedGcPtr<SharedGcPtr<UserData>> p0 = MakeSharedGcPtr<SharedGcPtr<UserData>>(MakeSharedGcPtr<UserData>(1337));
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

    void* p1 = MemoryAllocator::Allocate(144);
    void* p2 = MemoryAllocator::Allocate(144);
    void* p3 = MemoryAllocator::Allocate(144);
    void* p4 = MemoryAllocator::Allocate(144);
    void* p5 = MemoryAllocator::Allocate(144);
    void* p6 = MemoryAllocator::Allocate(144);

    MemoryAllocator::Deallocate(p2);
    MemoryAllocator::Deallocate(p4);

    std::cout << "Found: " << (void*)MemoryManager::GetArenaByPtr(p1)->GetInUseChunkByPtr(p5 + 160) << std::endl;
    std::cout << "Correct: " << (void*)((std::size_t)p6 - 16) << std::endl;

    MemoryManager::VisHeapLayout(std::cout) << std::endl;
    MemoryManager::DumpStats(std::cout);

    return 0;
}