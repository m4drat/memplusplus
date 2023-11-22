#include "fuzzer/crc_calculator.hpp"
#include "fuzzer/fuzzer.h"
#include "fuzzer/tokenizer.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/log.hpp"

#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace mpp::fuzzer;

std::function<int(const uint8_t* Data, std::size_t Size)> g_MppFuzzOneInput;

void HelpAndExit(char* executable)
{
    std::cout << "Usage: FUZZ_MODE=<fuzz_mode> " << executable << "\n";
    std::cout << "Available fuzz targets: \n";
    std::cout << "    - alloc_api\n";
    std::cout << "    - gc\n";

    exit(1);
}

int MppFuzzAllocApi(const uint8_t* Data, std::size_t Size)
{
    mpp::MemoryManager memMgr = mpp::MemoryManager();

    // translate input string into sequence of opcodes
    auto commands = Tokenizer::Tokenize(Data, Size);

    std::vector<void*> allocatedChunks;

    for (auto cmdIter = commands.begin(); cmdIter != commands.end(); cmdIter++) {
        Tokenizer::Command& cmd = *cmdIter;

        switch (cmd.GetOp()) {
            case Tokenizer::Operation::Allocate: {
                // std::cout << "Allocating chunk of size: " << cmd.second;
                allocatedChunks.push_back(memMgr.Allocate(cmd.GetArgs()[0]));
                // std::cout << ". Chunk allocated: " << allocatedChunks.back() << std::endl;
                break;
            }
            case Tokenizer::Operation::Deallocate: {
                if (allocatedChunks.empty()) {
                    return 0;
                }
                uint32_t position = rand() % allocatedChunks.size();
                void* chunk = allocatedChunks.at(position);
                // std::cout << "Deallocating chunk: " << chunk << ". Of size: " <<
                // mpp::Chunk::GetHeaderPtr(chunk)->GetSize() << std::endl;
                memMgr.Deallocate(chunk);
                allocatedChunks.erase(allocatedChunks.begin() + position);
                break;
            }
            case Tokenizer::Operation::Invalid:
            default:
                return 0;
        }
    }

    return 0;
}

int MppFuzzGcApi(const uint8_t* Data, std::size_t Size)
{
    mpp::g_memoryManager = std::make_unique<mpp::MemoryManager>();

    // translate input string into sequence of opcodes
    auto commands = Tokenizer::Tokenize(Data, Size);
    std::array<mpp::SharedGcPtr<Vertex>, c_maxPointers> pointers;

    for (auto cmdIter = commands.begin(); cmdIter != commands.end(); cmdIter++) {
        Tokenizer::Command& cmd = *cmdIter;

        switch (cmd.GetOp()) {
            case Tokenizer::Operation::CreateVertex: {
                MPP_DEBUG_ASSERT(cmd.GetArgs().size() == 1,
                                 "Got incorrect number of arguments for CreateVertex operation!");
                MPP_LOG_DEBUG("CreateVertex(%d)\n", cmd.GetArgs()[0]);

                auto vtx = mpp::MakeShared<Vertex>();
                pointers.at(cmd.GetArgs()[0]) = std::move(vtx);
                break;
            }
            case Tokenizer::Operation::RemoveVertex: {
                MPP_DEBUG_ASSERT(cmd.GetArgs().size() == 1,
                                 "Got incorrect number of arguments for RemoveVertex operation!");
                MPP_LOG_DEBUG("RemoveVertex(%d)\n", cmd.GetArgs()[0]);

                pointers.at(cmd.GetArgs()[0]) = nullptr;
                break;
            }
            case Tokenizer::Operation::CreateEdge: {
                MPP_DEBUG_ASSERT(cmd.GetArgs().size() == 3,
                                 "Got incorrect number of arguments for CreateEdge operation!");
                MPP_LOG_DEBUG("CreateEdge(%d, %d, %d)\n",
                              cmd.GetArgs()[0],
                              cmd.GetArgs()[1],
                              cmd.GetArgs()[2]);

                auto [vtxIdx1, vtxIdx2, ptrIdx] =
                    std::tie(cmd.GetArgs()[0], cmd.GetArgs()[1], cmd.GetArgs()[2]);
                mpp::SharedGcPtr<Vertex>& vtx_to_add = pointers.at(vtxIdx1);
                mpp::SharedGcPtr<Vertex>& vtx_add_to = pointers.at(vtxIdx2);

                if (vtx_to_add != nullptr && vtx_add_to != nullptr) {
                    vtx_add_to->AddPointerAtIndex(ptrIdx, vtx_to_add);
                }
                break;
            }
            case Tokenizer::Operation::RemoveEdge: {
                MPP_DEBUG_ASSERT(cmd.GetArgs().size() == 2,
                                 "Got incorrect number of arguments for RemoveEdge operation!");
                MPP_LOG_DEBUG("RemoveEdge(%d, %d)\n", cmd.GetArgs()[0], cmd.GetArgs()[1]);

                auto [vtxIdx, ptrIdx] = std::tie(cmd.GetArgs()[0], cmd.GetArgs()[1]);
                mpp::SharedGcPtr<Vertex>& vertex = pointers.at(vtxIdx);

                if (vertex != nullptr)
                    vertex->AddPointerAtIndex(ptrIdx, nullptr);
                break;
            }
            case Tokenizer::Operation::ReadSharedData: {
                MPP_DEBUG_ASSERT(cmd.GetArgs().size() == 1,
                                 "Got incorrect number of arguments for ReadSharedData operation!");
                MPP_LOG_DEBUG("ReadSharedData(%d)\n", cmd.GetArgs()[0]);

                auto vtxIdx = cmd.GetArgs()[0];
                mpp::SharedGcPtr<Vertex>& vertex = pointers.at(vtxIdx);
                if (vertex != nullptr) {
                    volatile uint64_t& data = vertex->GetData();
                }

                break;
            }
            case Tokenizer::Operation::CollectGarbage: {
                MPP_LOG_DEBUG("CollectGarbage()\n");
                mpp::CollectGarbage();
                break;
            }
            case Tokenizer::Operation::Allocate:
            case Tokenizer::Operation::Deallocate:
            case Tokenizer::Operation::Invalid:
            default:
                return 0;
        }
    }

    return 0;
}

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv)
{
    auto* fuzz_mode = std::getenv("FUZZ_MODE");
    if (!fuzz_mode) {
        std::cout << "Environment variable FUZZ_MODE is not set! Fuzzing default target: "
                     "MppFuzzAllocApi\n";
        g_MppFuzzOneInput = MppFuzzAllocApi;
        return 0;
    }

    if (!std::strcmp(fuzz_mode, "alloc_api")) {
        std::cout << "Environment variable FUZZ_MODE is set to \"alloc_api\"! Fuzzing "
                     "\"MppFuzzAllocApi\" target\n";
        g_MppFuzzOneInput = MppFuzzAllocApi;
    } else if (!std::strcmp(fuzz_mode, "gc")) {
        std::cout << "Environment variable FUZZ_MODE is set to \"gc\"! Fuzzing "
                     "\"MppFuzzGcApi\" target\n";
        g_MppFuzzOneInput = MppFuzzGcApi;
    } else {
        HelpAndExit(*argv[0]);
    }

    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, std::size_t Size)
{
    return g_MppFuzzOneInput(Data, Size);
}
