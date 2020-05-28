#pragma once

#include "mpplib/chunk.hpp"
#include <vector>

namespace mpp {

    struct Arena
    {
        std::vector<ChunkPrototype::Chunk*> chunkList;
        std::size_t size{ 0 };
        void* begin{ nullptr };
        void* end{ nullptr };
    };

}