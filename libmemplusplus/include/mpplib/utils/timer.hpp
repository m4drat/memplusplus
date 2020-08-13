#pragma once

#include <chrono>
#include <string>

namespace mpp { namespace utils { namespace profile {
    /**
     * @brief Timer class that provides basic time-measuring components
     */
    class Timer
    {
    public:
        /**
         * @brief Construct a new Timer object
         * @param t_name timer name
         */
        Timer(const char* t_name);

        /**
         * @brief Start timer
         * @return Timer&
         */
        Timer& TimerStart();

        /**
         * @brief Stop timer
         * @return Timer&
         */
        Timer& TimerEnd();

        /**
         * @brief Get the start timepoint
         * @return std::chrono::time_point<std::chrono::high_resolution_clock>
         */
        std::chrono::time_point<std::chrono::high_resolution_clock> GetStartTimepoint();

        /**
         * @brief Get the end timepoint
         * @return std::chrono::time_point<std::chrono::high_resolution_clock>
         */
        std::chrono::time_point<std::chrono::high_resolution_clock> GetEndTimepoint();

        /**
         * @brief Get name of the timer
         * @return std::string&
         */
        const char* GetName();

        /**
         * @brief Get the elapsed time
         * @tparam T - can be any of std::chrono time types (std::chrono::milliseconds, ...)
         * @return std::chrono::duration<double, T>
         */
        template<class T = std::chrono::milliseconds>
        auto GetElapsed() -> auto
        {
            return std::chrono::duration_cast<T>(m_EndTimePoint - m_StartTimepoint);
        }

    private:
        /**
         * @brief Name of the timer
         */
        const char* m_Name;

        /**
         * @brief Start time point
         */
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

        /**
         * @brief End time point
         */
        std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTimePoint;
    };
}}}