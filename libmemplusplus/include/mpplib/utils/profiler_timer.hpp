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
        explicit ProfilerTimer(const char* t_name);

        //! @brief Deleted copy constructor
        ProfilerTimer(const ProfilerTimer&) = delete;

        //! @brief Deleted move constructor
        ProfilerTimer(ProfilerTimer&&) = delete;

        //! @brief Deleted copy assignment operator
        ProfilerTimer& operator=(const ProfilerTimer&) = delete;

        //! @brief Deleted move assignment operator
        ProfilerTimer& operator=(ProfilerTimer&&) = delete;

        //! @brief Destroys the Profiler Timer and stops the timer
        ~ProfilerTimer();

        //! @brief stop the profiler timer
        void Stop();

    private:
        //! @brief is profiler timer stopped
        bool m_stopped;
    };
}}}