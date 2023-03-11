#pragma once

#include <limits>
#include <random>

namespace mpp {
    /**
     * @brief Class that provides API to work with 64 bit random values.
     * In insecure (debug)
     */
    class Random
    {
    private:
        /**
         * @brief Random values generator. Will use previously
         * created random device.
         */
        std::mt19937_64 m_gen;

        /**
         * @brief Generate random uniformally distributed numbers.
         */
        std::uniform_int_distribution<std::size_t> m_distribution;

    public:
        /**
         * @brief Construct a new Random object
         * @param t_min min value to generate
         * @param t_max max value to generate (limited to (2 << 63) - 1)
         * @param t_randSeed Seed source (by default system random seed /dev/random)
         */
        explicit Random(std::size_t t_min = 0x0,
                        std::size_t t_max = std::numeric_limits<std::size_t>::max(),
                        std::size_t t_randSeed = std::random_device{}())
            : m_gen{ t_randSeed }
            , m_distribution{ t_min, t_max }
        {
        }

        /**
         * @brief Sets seed, to generate predictable values. Used only
         * in debug/fuzzer builds.
         * @param t_seed new seed value
         * @return Random& instance of current object
         */
        Random& SetSeed(uint32_t t_seed)
        {
            m_gen.seed(t_seed);
            return *this;
        }

        /**
         * @brief Generate uniformally distributed random value [t_min, t_max]
         * @return std::size_t 64bit random value
         */
        std::size_t operator()()
        {
            return m_distribution(m_gen);
        }

        /**
         * @brief Returns global instance of Random object
         * @return Random& global instance
         */
        static Random& GetInstance()
        {
            static Random s_randomInstance;
#if MPP_FUZZER_INSECURE == 1 || MPP_DEBUG == 1
            s_randomInstance.SetSeed(0);
#endif
            return s_randomInstance;
        }
    };
}