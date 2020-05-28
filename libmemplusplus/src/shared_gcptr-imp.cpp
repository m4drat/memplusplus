#pragma once

#include "mpplib/shared_gcptr.hpp"

#include <iostream>
#include <type_traits>

namespace mpp {
    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args)
    {
        // TODO
        // return new (malloc(sizeof(T))) T(std::forward<Args>(args)...);
        return SharedGcPtr<T>();
    }
}