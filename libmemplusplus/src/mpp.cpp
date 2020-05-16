#include <iostream>
#include <vector>

#include "mpplib/mpp.hpp"

void GC::init()
{
    std::cout << "In init()" << std::endl;
}

ptrdiff_t GC::CalcDist(void *ptr1, void *ptr2)
{
    return static_cast<char*>(ptr1) - static_cast<char*>(ptr2);
}