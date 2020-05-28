#pragma once

#include "mpplib/chunk.hpp"
#include <vector>

namespace mpp {
    struct Arena
    {
        std::vector<Chunk*> chunksInUse;
        std::size_t size{ 0 };
        std::size_t freeSpace{ 0 };
        std::size_t maxAvailableChunkSize{ 0 };
        void* begin{ nullptr };
        void* end{ nullptr };

        Arena(std::size_t t_size, void* t_begin, void* t_end)
        {
            size = t_size;
            freeSpace = t_size;
            begin = t_begin;
            end = t_end;
        };

        Chunk* AllocateChunk(std::size_t t_chunkSize);
        void DeAllocateChunk(Chunk* t_chunk);
    };
}