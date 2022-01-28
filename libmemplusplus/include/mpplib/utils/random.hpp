#pragma once

#include <random>

namespace mpp {
    /**
     * @brief Class that provides API to work with 64 bit random values.
     * In insecure (debug)
     */
    class Random {
    private:
        /**
         * @brief Default random seed source. On linux
         * it will use /dev/random as a seed source, so
         * it should be secure enough to use it to randomize mmap
         * base, and create headers keys.
         */
        std::random_device m_OsRandomDev;

        /**
         * @brief Random values generator. Will use previously 
         * created random device.
         */
        std::mt19937_64 m_Gen;

        /**
         * @brief Generate random uniformally distributed numbers. 
         */
        std::uniform_int_distribution<size_t> m_Distribution;
    
    public:
        /**
         * @brief Construct a new Random object
         * @param t_Min min value to generate 
         * @param t_Max max value to generate (limited to (2 << 63) - 1)
         * @param t_RandSeed Seed source (by default system random seed /dev/random)
         */
        Random(std::size_t t_Min = 0x0, std::size_t t_Max = 18446744073709551615ull, std::size_t t_RandSeed = std::random_device{}())
            : m_Gen{t_RandSeed}, m_Distribution{t_Min, t_Max}
        {}

        /**
         * @brief Sets seed, to generate predictable values. Used only
         * in debug/fuzzer builds.
         * @param t_Seed new seed value
         * @return Random& instance of current object
         */
        Random& SetSeed(uint32_t t_Seed) {
            m_Gen.seed(t_Seed);
            return *this;
        }

        /**
         * @brief Generate uniformally distributed random value [t_Min, t_Max] 
         * @return std::size_t 64bit random value 
         */
        std::size_t operator()() {
            return m_Distribution(m_Gen);
        }

        /**
         * @brief Returns global instance of Random object
         * @return Random& global instance 
         */
        static Random& GetInstance()
        {
            static Random s_RandomInstance;
#if MPP_FUZZER_INSECURE == 1 || MPP_DEBUG == 1
            s_RandomInstance.SetSeed(0);
#endif
            return s_RandomInstance;
        }
    };
}