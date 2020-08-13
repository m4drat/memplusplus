#include "mpplib/utils/profiler.hpp"
#include <iostream>

namespace mpp { namespace utils { namespace profile {
    Profiler::Profiler()
        : m_ProfileCount(0)
    {}

    Profiler::~Profiler()
    {
#if MPP_PROFILE == 1
        Profiler::Get().EndSession();
#endif
    }

    void Profiler::BeginSession(const std::string& t_name, const std::string& t_filepath)
    {
        m_OutputStream.open(t_filepath);
        WriteHeader();
    }

    void Profiler::EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        m_ProfileCount = 0;
    }

#if MPP_PROFILE == 1
    void Profiler::BeginGlobalSession()
    {
        Profiler::Get().BeginSession("Mpplib profiling", "mpplib-profiling.json");
    }
#endif

    void Profiler::WriteProfile(const char* t_name,
                                int64_t t_start,
                                int64_t t_end,
                                uint32_t t_threadId)
    {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = std::string(t_name);
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (t_end - t_start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << t_threadId << ",";
        m_OutputStream << "\"ts\":" << t_start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    void Profiler::WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void Profiler::WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    Profiler& Profiler::Get()
    {
        static Profiler s_instance;
        return s_instance;
    }
}}}