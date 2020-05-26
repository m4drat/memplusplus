#pragma once

#include "mpplib/shared_gcptr.hpp"

#include <iostream>

namespace mpp {
    template<class T, class... Args>
    SharedGcPtr<T> MakeSharedGcPtr(Args&&... args)
    {
        return SharedGcPtr<T>();
    }
}