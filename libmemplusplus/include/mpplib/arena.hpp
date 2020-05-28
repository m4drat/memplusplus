#pragma once

#include "mpplib/chunk.hpp"
#include <vector>

namespace mpp {
    struct Arena
    {
        // 1. Find max element
        // 2. Fast insert/delete
        // 3. Fast exact search
        // 4. Find bigger or equal element
        std::vector<Chunk*> chunksInUse;
        std::size_t size{ 0 };
        std::size_t rightSpace{ 0 };
        std::size_t maxBetweenSpace{ 0 };
        void* begin{ nullptr };
        void* end{ nullptr };

        Arena(std::size_t t_size, void* t_begin, void* t_end)
        {
            size = t_size;
            rightSpace = t_size;
            begin = t_begin;
            end = t_end;
        };

        Chunk* AllocateChunk(std::size_t t_chunkSize);
        void DeallocateChunk(Chunk* t_chunk);
    };
}