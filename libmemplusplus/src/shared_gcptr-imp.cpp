#pragma once

#include "mpplib/shared_gcptr.hpp"

#include <type_traits>
#include <iostream>

namespace mpp {
    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args)
    {
        // TODO
        return SharedGcPtr<T>();
    }
}