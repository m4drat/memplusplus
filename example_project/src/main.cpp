#include <iostream>
#include <memory>

#include "mpplib/mpp.hpp"

auto main() -> int
{
    auto gc = std::make_unique<GC>();
    std::cout << "In main()" << std::endl;
}