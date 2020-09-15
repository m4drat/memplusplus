#pragma once

#include <deque>
#include <cstdint>
#include <string>
#include <sstream>

namespace mpp { namespace fuzzer {
class Tokenizer {
public:
    enum class Tokens {
        Allocate,
        Deallocate,
        Invalid
    };

    static std::string ParseNumber(const uint8_t* t_dataStart, const uint8_t* t_dataEnd);
    /* a1024a128a16a20ddd */
    static std::deque<std::pair<Tokens, std::size_t>> Tokenize(const uint8_t* t_data, size_t t_size);
};
}}