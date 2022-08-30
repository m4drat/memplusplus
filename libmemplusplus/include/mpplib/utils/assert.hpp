#pragma once

#include "mpplib/utils/utils.hpp"

namespace mpp {
#define MPP_STRINGIFY(x) #x
#define MPP_TO_STRING(x) MPP_STRINGIFY(x)

#define PRIVATE__MPP_ASSERT(expr, msg)                                                             \
    ((expr) ? (void)0                                                                              \
            : mpp::utils::ErrorAbort("Assertation " #expr " failed in: " __FILE__                  \
                                     ":" MPP_TO_STRING(__LINE__) "\n"))

#ifdef MPP_DEBUG
#define MPP_ASSERT(expr, msg) PRIVATE__MPP_ASSERT((expr), (msg))
#else
#define MPP_ASSERT(expr, msg) ((void)0)
#endif

#define MPP_RELEASE_ASSERT(expr, msg) PRIVATE__MPP_ASSERT((expr), (msg))
}