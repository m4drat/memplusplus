#include "fuzzer/tokenizer.hpp"

namespace mpp { namespace fuzzer {
    std::string Tokenizer::ParseNumber(const uint8_t* t_dataStart, const uint8_t* t_dataEnd)
    {
        std::string number = "";
        uint8_t* currentDataPtr = (uint8_t*)t_dataStart;

        while (currentDataPtr < t_dataEnd) 
        {
            switch (*currentDataPtr)
            {
            case 0x30 /* Number */:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
                number.push_back(*currentDataPtr);
                ++currentDataPtr;
                break;
            
            default:
                if (number.length() != 0)
                    return number;
                return "-1";
            }
        }

        if (number.length() == 0)
            return "-1";
        return number;
    }

    std::deque<std::pair<Tokenizer::Tokens, std::size_t>> Tokenizer::Tokenize(const uint8_t* t_data, size_t t_size)
    {
        std::deque<std::pair<Tokenizer::Tokens, std::size_t>> commands;
        std::size_t current_size = t_size;
        const uint8_t *dataStart = t_data, *dataEnd = (t_data + t_size);
        uint8_t* currentDataPtr = (uint8_t*)dataStart;

        while (currentDataPtr < dataEnd)
        {
            std::pair<Tokens, std::size_t> currentCommand;

            switch (*currentDataPtr)
            {
            case 0x61 /* Allocate */: {
                std::string allocSize = ParseNumber(currentDataPtr + 1, dataEnd);
                if (allocSize.length() > 8 || std::stoull(allocSize) == -1 || std::stoull(allocSize) > 67109888)
                {
                    currentCommand = std::make_pair(Tokens::Invalid, 0);
                    break;
                }

                currentCommand = std::make_pair(Tokens::Allocate, std::stoull(allocSize));

                current_size -= (allocSize.length() + 1);
                currentDataPtr += allocSize.length() + 1;
                break;
            }
            case 0x64 /* Deallocate */: {
                currentCommand = std::make_pair(Tokens::Deallocate, 0);
                --current_size;
                ++currentDataPtr;
                break;
            }

            default: {
                currentCommand = std::make_pair(Tokens::Invalid, 0);
                break;
            }
            }

            commands.push_back(currentCommand);

            if (commands.back().first == Tokens::Invalid)
            {
                break;
            }
        }

        return commands;
    }
}}