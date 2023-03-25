#include "fuzzer/tokenizer.hpp"
#include "fuzzer/fuzzer.h"
#include "mpplib/utils/macros.hpp"
#include <optional>

namespace mpp { namespace fuzzer {
    std::vector<Tokenizer::Command> Tokenizer::Tokenize(const uint8_t* t_data, std::size_t t_size)
    {
        const uint8_t* dataStart = t_data;
        const uint8_t* dataEnd = (t_data + t_size);
        const uint8_t* currentDataPtr = dataStart;
        const std::size_t c_maxCommands = 128;

        std::vector<Command> commands;
        commands.reserve(c_maxCommands);

        while (currentDataPtr < dataEnd) {
            Command currentCommand;
            switch (*currentDataPtr++) {
                case 'a' /* Allocate */: {
                    const std::size_t c_maxAllocSize = 0x4000400;
                    GET_UINT32(allocSize, (allocSize >= c_maxAllocSize));

                    currentCommand = Command(Operation::Allocate, { allocSize });
                    break;
                }
                case 'd' /* Deallocate */: {
                    currentCommand = Command(Operation::Deallocate, {});
                    break;
                }
                case 'C' /* Create shared pointer */: {
                    // Command format: S<Create At Position N>
                    GET_UINT16(pointerIdx, (pointerIdx >= c_maxPointers));

                    currentCommand = Command(Operation::CreateVertex, { pointerIdx });
                    break;
                }
                case 'D' /* Remove shared pointer */: {
                    // Command format: D<index of the pointer to delete>
                    GET_UINT16(pointerIdx, (pointerIdx >= c_maxPointers));

                    currentCommand = Command(Operation::RemoveVertex, { pointerIdx });
                    break;
                }
                case 'E' /* Creates an edge between vtx1 and vtx2 */: {
                    // Command format: E<vtx1>,<vtx2>,<idx inside vtx2>
                    // Adds vtx1 to a list of pointers of the vtx2 at the index idx.
                    GET_UINT16(vtxIdx1, (vtxIdx1 >= c_maxPointers));
                    GET_UINT16(vtxIdx2, (vtxIdx2 >= c_maxPointers));
                    GET_UINT16(ptrIdx, (ptrIdx >= c_maxPointersInAVertex));

                    currentCommand = Command(Operation::CreateEdge, { vtxIdx1, vtxIdx2, ptrIdx });
                    break;
                }
                case 'R' /* Removes an edge between vtx1 and vtx2 */: {
                    // Command format: R<vtx1>,<idx inside vtx1>
                    // Removes a pointer at the index idx from the list of pointers of the vtx1.
                    GET_UINT16(vtxIdx1, (vtxIdx1 >= c_maxPointers));
                    GET_UINT16(vtxIdx2, (vtxIdx2 >= c_maxPointersInAVertex));

                    currentCommand = Command(Operation::RemoveEdge, { vtxIdx1, vtxIdx2 });
                    break;
                }
                case 'T' /* Finds a route from vtx1 to vtx2 (DFS) */: {
                    // @TODO: Implement simple DFS
                    break;
                }
                case 'P' /* Read data from vertex */: {
                    GET_UINT16(vtxIdx, (vtxIdx >= c_maxPointers));
                    currentCommand = Command(Operation::ReadSharedData, { vtxIdx });
                    break;
                }
                case 'G' /* Collect garbage */: {
                    // Calls mpp::CollectGarbage()
                    currentCommand = Command(Operation::CollectGarbage, {});
                    break;
                }

                default: {
                    currentCommand = Command(Operation::Invalid, {});
                    break;
                }
            }

            commands.push_back(currentCommand);

            if (commands.back().GetOp() == Operation::Invalid || commands.size() > c_maxCommands) {
                break;
            }
        }

        return commands;
    }
}}