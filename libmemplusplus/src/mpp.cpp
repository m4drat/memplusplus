#include "mpplib/mpp.hpp"

void GC::init()
{
    std::cout << "In init()" << std::endl;
}

auto GC::CalcDist(void* ptr1, void* ptr2)
{
    return static_cast<char*>(ptr1) - static_cast<char*>(ptr2);
}