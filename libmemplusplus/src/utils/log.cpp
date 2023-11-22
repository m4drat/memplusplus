#include "mpplib/utils/log.hpp"
#include <algorithm>

namespace mpp { namespace logging {
    LogLevel LogLevelFromString(const std::string& logLevel)
    {
        std::string logLevelStr = logLevel;
        std::transform(logLevelStr.begin(), logLevelStr.end(), logLevelStr.begin(), ::toupper);

        if (s_StringToLogLevel.find(logLevelStr) != s_StringToLogLevel.end())
            return s_StringToLogLevel.at(logLevelStr);

        return LogLevel::FATAL;
    }
}}