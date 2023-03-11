#include "mpplib/utils/timer.hpp"

namespace mpp { namespace utils { namespace profile {
    Timer::Timer(const char* t_name)
        : m_name(t_name)
    {
    }

    Timer& Timer::TimerStart()
    {
        m_startTimepoint = std::chrono::high_resolution_clock::now();
        return *this;
    }

    Timer& Timer::TimerEnd()
    {
        m_endTimePoint = std::chrono::high_resolution_clock::now();
        return *this;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> Timer::GetStartTimepoint()
    {
        return m_startTimepoint;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> Timer::GetEndTimepoint()
    {
        return m_endTimePoint;
    }

    const char* Timer::GetName()
    {
        return m_name;
    }
}}}