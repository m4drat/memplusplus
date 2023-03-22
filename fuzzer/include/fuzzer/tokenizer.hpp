#pragma once

#include <cstdint>
#include <deque>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace mpp { namespace fuzzer {
#define CHECK_MORE_DATA()                                                                          \
    if (currentDataPtr >= dataEnd) {                                                               \
        currentCommand = Command(Operation::Invalid, {});                                          \
        break;                                                                                     \
    }

#define CHECK_HAS_AT_LEAST_N(length)                                                               \
    if (currentDataPtr + length > dataEnd) {                                                       \
        currentCommand = Command(Operation::Invalid, {});                                          \
        break;                                                                                     \
    }

#define CONSUME_SINGLE()                                                                           \
    CHECK_HAS_AT_LEAST_N(sizeof(uint8_t));                                                         \
    currentDataPtr++;

#define GET_PRIMITIVE_CHECKED(type, var_name, cond)                                                \
    CHECK_HAS_AT_LEAST_N(sizeof(type));                                                            \
    type var_name = *reinterpret_cast<const type*>(currentDataPtr);                                \
                                                                                                   \
    if ((cond)) {                                                                                  \
        currentCommand = Command(Operation::Invalid, {});                                          \
        break;                                                                                     \
    }                                                                                              \
                                                                                                   \
    currentDataPtr += sizeof(type);

#define GET_UINT8(var_name, cond) GET_PRIMITIVE_CHECKED(uint8_t, var_name, cond)
#define GET_UINT16(var_name, cond) GET_PRIMITIVE_CHECKED(uint16_t, var_name, cond)
#define GET_UINT32(var_name, cond) GET_PRIMITIVE_CHECKED(uint32_t, var_name, cond)

#define CHECK_DELIMETER()                                                                          \
    CHECK_HAS_AT_LEAST_N(sizeof(uint8_t));                                                         \
    if (*currentDataPtr != ',') {                                                                  \
        currentCommand = Command(Operation::Invalid, {});                                          \
        break;                                                                                     \
    }                                                                                              \
    currentDataPtr++;

    class Tokenizer
    {
    public:
        /**
         * @brief Specifies all available tokens (aka opcodes)
         * that can be used to fuzz allocator logic
         */
        enum class Operation
        {
            /* Allocate/Deallocate APIs */
            Allocate,
            Deallocate,

            /* GC/GcPtr's APis */
            CreateVertex,
            RemoveVertex,
            CreateEdge,
            RemoveEdge,
            ReadSharedData,
            CollectGarbage,

            /* Generic error command */
            Invalid
        };

        class Command
        {
        private:
            Operation m_op;
            std::vector<uint32_t> m_arguments;

        public:
            Command()
                : m_op(Operation::Invalid)
            {
            }

            Command(Operation t_op, std::vector<uint32_t>&& t_args)
                : m_op{ t_op }
                , m_arguments{ t_args }
            {
            }

            Operation GetOp()
            {
                return m_op;
            }

            std::vector<uint32_t>& GetArgs()
            {
                return m_arguments;
            }
        };

        /**
         * @brief Parse input string into sequence of opcodes and parameters to them.
         * @param t_data fuzzer-generated data
         * @param t_size size of fuzzer-generated data
         * @return std::deque<std::pair<Tokens, std::size_t>> of opcodes and their parameters
         */
        static std::deque<Command> Tokenize(const uint8_t* t_data, std::size_t t_size);
    };
}}