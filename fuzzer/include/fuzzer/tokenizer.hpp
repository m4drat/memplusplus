#pragma once

#include <cstdint>
#include <deque>
#include <sstream>
#include <string>

namespace mpp { namespace fuzzer {
    class Tokenizer
    {
    public:
        /**
         * @brief Specifies all available tokens (aka opcodes)
         * that can be used to fuzz allocator logic
         */
        enum class Tokens
        {
            Allocate,
            Deallocate,
            Invalid
        };

        /**
         * @brief Extract number as std::string starting from t_dataStart. (This function doesn't
         * work with negative numbers).
         * @param t_dataStart points to the first char to start parsing number from
         * @param t_dataEnd points to the last valid char of the buffer
         * @return std::string parsed number or "-1" if something went wrong
         */
        static std::string ParseNumber(const uint8_t* t_dataStart, const uint8_t* t_dataEnd);

        /**
         * @brief Parse input string into sequence of opcodes and parameters to them.
         * @param t_data fuzzer-generated data
         * @param t_size size of fuzzer-generated data
         * @return std::deque<std::pair<Tokens, std::size_t>> of opcodes and their parameters
         */
        static std::deque<std::pair<Tokens, std::size_t>> Tokenize(const uint8_t* t_data,
                                                                   std::size_t t_size);
    };
}}