#pragma once

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>

namespace mpp { namespace utils { namespace profile {
    /**
     * @brief Class that provides features to profile and dump results
     */
    class Profiler
    {
    private:
        /**
         * @brief Stream to write to
         */
        std::ofstream m_OutputStream;

        /**
         * @brief profile counts
         */
        int32_t m_ProfileCount;

    public:
        /**
         * @brief Construct a new Profiler object
         */
        Profiler();

        /**
         * @brief Destroy the Profiler object, and write to mpplib-profile if needed
         */
        ~Profiler();

        /**
         * @brief Start new profiling session
         * @param t_name session name
         * @param t_filepath profile filename
         */
        void BeginSession(const std::string& t_name,
                          const std::string& t_filepath = "profile.json");

        /**
         * @brief Stop profiling session
         */
        void EndSession();

#if MPP_PROFILE == 1
        __attribute__((constructor)) void BeginGlobalSession();
#endif

        /**
         * @brief Write info to profile
         * @param t_name timestamp name
         * @param t_start start time
         * @param t_end end time
         * @param t_threadId thread id
         */
        void WriteProfile(const char* t_name, int64_t t_start, int64_t t_end, uint32_t t_threadId);

        /**
         * @brief Write header to profile file
         */
        void WriteHeader();

        /**
         * @brief Write footer to profile file
         */
        void WriteFooter();

        /**
         * @brief Get static instance
         * @return Profiler&
         */
        static Profiler& Get();
    };
}}}