#include "fuzzer/tokenizer.hpp"

namespace mpp { namespace fuzzer {
    std::optional<std::string> Tokenizer::ParseNumber(const uint8_t* t_dataStart,
                                                      const uint8_t* t_dataEnd)
    {
        std::string number;
        while (t_dataStart < t_dataEnd) {
            switch (*t_dataStart) {
                case '0' /* Number */:
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    number.push_back(*t_dataStart);
                    ++t_dataStart;
                    break;

                default:
                    if (number.length() != 0)
                        return number;
                    return std::nullopt;
            }
        }

        if (number.length() == 0)
            return std::nullopt;

        return number;
    }

    std::deque<std::pair<Tokenizer::Tokens, std::size_t>> Tokenizer::Tokenize(const uint8_t* t_data,
                                                                              std::size_t t_size)
    {
        std::deque<std::pair<Tokenizer::Tokens, std::size_t>> commands;
        std::size_t current_size = t_size;
        const uint8_t *dataStart = t_data, *dataEnd = (t_data + t_size);
        uint8_t* currentDataPtr = (uint8_t*)dataStart;

        while (currentDataPtr < dataEnd) {
            std::pair<Tokens, std::size_t> currentCommand;

            switch (*currentDataPtr) {
                case 'a' /* Allocate */: {
                    const std::size_t c_maxAllocSize = 0x4000400;
                    std::string allocSizeStr =
                        ParseNumber(currentDataPtr + 1, dataEnd).value_or("0");
                    std::size_t allocSize = 0;
                    try {
                        std::size_t allocSize = std::stoull(allocSizeStr);
                    } catch (const std::invalid_argument& e) {
                        currentCommand = std::make_pair(Tokens::Invalid, 0);
                        break;
                    } catch (const std::out_of_range& e) {
                        currentCommand = std::make_pair(Tokens::Invalid, 0);
                        break;
                    }

                    if (allocSize > c_maxAllocSize) {
                        currentCommand = std::make_pair(Tokens::Invalid, 0);
                        break;
                    }

                    currentCommand = std::make_pair(Tokens::Allocate, allocSize);

                    current_size -= (allocSizeStr.length() + 1);
                    currentDataPtr += allocSizeStr.length() + 1;
                    break;
                }
                case 'd' /* Deallocate */: {
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

            if (commands.back().first == Tokens::Invalid) {
                break;
            }
        }

        return commands;
    }
}}