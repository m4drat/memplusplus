#pragma once

#include "mpplib/utils/profiler_timer.hpp"

#if MPP_PROFILE == 1
    #define PROFILE_SCOPE(name) mpp::utils::profile::ProfilerTimer timer##__LINE__(name)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
    #define PROFILE_FUNCTION()
#endif