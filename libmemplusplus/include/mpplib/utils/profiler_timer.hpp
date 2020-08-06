#pragma once

#include "mpplib/utils/profiler.hpp"
#include "mpplib/utils/timer.hpp"

#include <thread>

namespace mpp { namespace utils { namespace profile {
    /**
     * @brief Extended timer, to automate profiling 
     */
    class ProfilerTimer : public Timer
    {
    public:
        /**
         * @brief Construct a new Profiler Timer object
         * @param t_name name of the timer
         */
        ProfilerTimer(std::string& t_name);

        /**
         * @brief Destroy the Profiler Timer object
         */
        ~ProfilerTimer();

        /**
         * @brief stop the profiler timer
         */
        void Stop();
    private:
        /**
         * @brief is profiler timer stopped
         */
        bool m_Stopped;
    };

    #define PROFILE_SCOPE(name) ProfilerTimer timer##__LINE__(name)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
}}}