#include "mpplib/utils/profiler.hpp"
#include <iostream>

namespace mpp { namespace utils { namespace profile {
    Profiler::Profiler()
        : m_profileCount(0)
    {
        BeginSession("Mpplib profiling", "mpplib-profiling.json");
    }

    Profiler::~Profiler()
    {
        Profiler::Get().EndSession();
    }

    void Profiler::BeginSession(const std::string& t_name, const std::string& t_filepath)
    {
        m_outputStream.open(t_filepath);
        WriteHeader();
    }

    void Profiler::EndSession()
    {
        WriteFooter();
        m_outputStream.close();
        m_profileCount = 0;
    }

    void Profiler::WriteProfile(const char* t_name,
                                int64_t t_start,
                                int64_t t_end,
                                uint32_t t_threadId)
    {
        if (m_profileCount++ > 0) {
            m_outputStream << ",";
        }

        std::string name = std::string(t_name);
        std::replace(name.begin(), name.end(), '"', '\'');

        m_outputStream << "{";
        m_outputStream << "\"cat\":\"function\",";
        m_outputStream << "\"dur\":" << (t_end - t_start) << ',';
        m_outputStream << "\"name\":\"" << name << "\",";
        m_outputStream << "\"ph\":\"X\",";
        m_outputStream << "\"pid\":0,";
        m_outputStream << "\"tid\":" << t_threadId << ",";
        m_outputStream << "\"ts\":" << t_start;
        m_outputStream << "}";

        m_outputStream.flush();
    }

    void Profiler::WriteHeader()
    {
        m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_outputStream.flush();
    }

    void Profiler::WriteFooter()
    {
        m_outputStream << "]}";
        m_outputStream.flush();
    }

    Profiler& Profiler::Get()
    {
        static Profiler s_instance;
        return s_instance;
    }
}}}