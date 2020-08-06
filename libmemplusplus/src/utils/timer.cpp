#include "mpplib/utils/timer.hpp"

namespace mpp { namespace utils { namespace profile {
    Timer::Timer(const char* t_name)
        : m_Name(t_name)
    {}

    Timer& Timer::TimerStart()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
        return *this;
    }

    Timer& Timer::TimerEnd()
    {
        m_EndTimePoint = std::chrono::high_resolution_clock::now();
        return *this;   
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> Timer::GetStartTimepoint()
    {
        return m_StartTimepoint;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> Timer::GetEndTimepoint()
    {
        return m_EndTimePoint;
    }

    const char* Timer::GetName()
    {
        return m_Name;
    }
}}}