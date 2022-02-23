#include "fuzzer/crc_calculator.hpp"
#include "fuzzer/tokenizer.hpp"
#include "mpplib/memory_allocator.hpp"

#include <deque>
#include <iostream>
#include <vector>

using namespace mpp::fuzzer;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, std::size_t Size)
{
    // translate input string into sequence of opcodes
    std::deque<std::pair<Tokenizer::Tokens, std::size_t>> commands =
        Tokenizer::Tokenize(Data, Size);
    std::vector<void*> allocatedChunks;

    while (!commands.empty()) {
        std::pair<Tokenizer::Tokens, std::size_t> cmd = commands.front();

        switch (cmd.first) {
            case Tokenizer::Tokens::Allocate: {
                // std::cout << "Allocating chunk of size: " << cmd.second;
                allocatedChunks.push_back(mpp::MemoryAllocator::Allocate(cmd.second));
                // std::cout << ". Chunk allocated: " << allocatedChunks.back() << std::endl;
                break;
            }
            case Tokenizer::Tokens::Deallocate: {
                if (allocatedChunks.empty())
                {
                    return 0;
                }
                uint32_t position = rand() % allocatedChunks.size();
                void* chunk = allocatedChunks.at(position);
                // std::cout << "Deallocating chunk: " << chunk << ". Of size: " <<
                // mpp::Chunk::GetHeaderPtr(chunk)->GetSize() << std::endl;
                mpp::MemoryAllocator::Deallocate(chunk);
                allocatedChunks.erase(allocatedChunks.begin() + position);
                break;
            }
            case Tokenizer::Tokens::Invalid: {
                mpp::MemoryAllocator::ResetAllocatorState();
                return 0;
                break;
            }
        }

        commands.pop_front();
    }

    mpp::MemoryAllocator::ResetAllocatorState();
    return 0;
}

/*
int main()
{
    std::string data;

    std::cin >> data;

    // translate input string into sequence of opcodes
    std::deque <std::pair<Tokenizer::Tokens, std::size_t>> commands = Tokenizer::Tokenize((const
uint8_t*)data.c_str(), data.length()); std::vector <void*> allocatedChunks;

    while (!commands.empty())
    {
        std::pair<Tokenizer::Tokens, std::size_t> cmd = commands.front();

        switch (cmd.first)
        {
        case Tokenizer::Tokens::Allocate: {
            // std::cout << "Allocating chunk of size: " << cmd.second;
            allocatedChunks.push_back(mpp::MemoryAllocator::Allocate(cmd.second));
            // std::cout << ". Chunk allocated: " << allocatedChunks.back() << std::endl;
            break;
        }
        case Tokenizer::Tokens::Deallocate: {
            if (allocatedChunks.size() == 0)
                return 0;
            uint32_t position = rand() % allocatedChunks.size();
            void* chunk = allocatedChunks.at(position);
            // std::cout << "Deallocating chunk: " << chunk << ". Of size: " <<
mpp::Chunk::GetHeaderPtr(chunk)->GetSize() << std::endl; mpp::MemoryAllocator::Deallocate(chunk);
            allocatedChunks.erase(allocatedChunks.begin() + position);
            break;
        }
        case Tokenizer::Tokens::Invalid: {
            return 0;
            break;
        }
        }

        commands.pop_front();
    }

    return 0;
}
*/