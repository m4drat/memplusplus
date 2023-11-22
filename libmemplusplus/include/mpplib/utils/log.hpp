#pragma once

#include <cstdio>
#include <string>
#include <unordered_map>

namespace mpp { namespace logging {
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL,
        DISABLED
    };

    static const std::unordered_map<LogLevel, std::string> s_LogLevelToString = {
        { LogLevel::TRACE, "TRACE" },      { LogLevel::DEBUG, "DEBUG" },
        { LogLevel::INFO, "INFO" },        { LogLevel::WARNING, "WARNING" },
        { LogLevel::ERROR, "ERROR" },      { LogLevel::FATAL, "FATAL" },
        { LogLevel::DISABLED, "DISABLED" }
    };

    static const std::unordered_map<std::string, LogLevel> s_StringToLogLevel = {
        { "TRACE", LogLevel::TRACE },      { "DEBUG", LogLevel::DEBUG },
        { "INFO", LogLevel::INFO },        { "WARNING", LogLevel::WARNING },
        { "ERROR", LogLevel::ERROR },      { "FATAL", LogLevel::FATAL },
        { "DISABLED", LogLevel::DISABLED }
    };

    LogLevel LogLevelFromString(const std::string& logLevel);
}}

#define MPP_COLOR_GREY "\u001b[90m"
#define MPP_COLOR_YELLOW "\u001b[33m"
#define MPP_COLOR_RED "\u001b[31m"
#define MPP_COLOR_RESET "\u001b[0m"

#define MPP_LOG(LEVEL, LEVEL_FMT, FMT, ...)                                                        \
    if (LEVEL >= mpp::utils::EnvOptions::Get().GetMppLogLevel()) {                                 \
        /* NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)  */                     \
        std::printf(LEVEL_FMT FMT __VA_OPT__(, ) __VA_ARGS__);                                     \
    }

#define MPP_LOG_TRACE(FMT, ...)                                                                    \
    MPP_LOG(mpp::logging::LogLevel::TRACE,                                                         \
            MPP_COLOR_GREY "🐾 [TRACE] ",                                                           \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)
#define MPP_LOG_DEBUG(FMT, ...)                                                                    \
    MPP_LOG(mpp::logging::LogLevel::DEBUG,                                                         \
            MPP_COLOR_GREY "❓ [DEBUG] ",                                                           \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)
#define MPP_LOG_INFO(FMT, ...)                                                                     \
    MPP_LOG(mpp::logging::LogLevel::INFO,                                                          \
            MPP_COLOR_GREY "📘 [INFO] ",                                                            \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)
#define MPP_LOG_WARNING(FMT, ...)                                                                  \
    MPP_LOG(mpp::logging::LogLevel::WARNING,                                                       \
            MPP_COLOR_YELLOW "🚧 [WARNING] ",                                                       \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)
#define MPP_LOG_ERROR(FMT, ...)                                                                    \
    MPP_LOG(mpp::logging::LogLevel::ERROR,                                                         \
            MPP_COLOR_RED "❌ [ERROR] ",                                                            \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)
#define MPP_LOG_FATAL(FMT, ...)                                                                    \
    MPP_LOG(mpp::logging::LogLevel::FATAL,                                                         \
            MPP_COLOR_RED "⛔ [FATAL] ",                                                            \
            FMT MPP_COLOR_RESET,                                                                   \
            __VA_ARGS__)                                                                           \
    mpp::utils::ErrorAbort("Fatal error occurred!");