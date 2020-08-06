#include "mpplib/utils/profiler_timer.hpp"

namespace mpp { namespace utils { namespace profile {

    ProfilerTimer::ProfilerTimer(const char* t_name)
        : Timer(t_name), m_Stopped(false)
    {
        this->TimerStart();
    }

    ProfilerTimer::~ProfilerTimer()
    {
        if (!m_Stopped)
            Stop();
    }

    void ProfilerTimer::Stop()
    {
        this->TimerEnd();

        int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(GetStartTimepoint()).time_since_epoch().count();
        int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(GetEndTimepoint()).time_since_epoch().count();

        uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
        mpp::utils::profile::Profiler::Get().WriteProfile(GetName(), start, end, threadId);

        m_Stopped = true;
    }
}}}