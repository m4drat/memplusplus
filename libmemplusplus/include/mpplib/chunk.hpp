#pragma once

#include <cstdint>

namespace mpp {

    struct Chunk
    {

        /**
         * What we shoul have here?
         * 1. InUse bit
         * 2. Should we have pointer to the next freed chunk?
         */
        struct ChunkHeader_t
        {
            uint32_t chunkHeader;
        } ChunkHeader;

        bool GetSize(Chunk* chunk) 
        { 
            return (chunk->ChunkHeader.chunkHeader >> 4) << 4; 
        };

        void* GetUserData(Chunk* chunk)
        {
            return chunk + sizeof(Chunk::ChunkHeader);
        };

        bool IsUsed(Chunk* chunk)
        {
            return (chunk->ChunkHeader.chunkHeader & 0b1111) >> 3;
        };

        void SetIsUsed(Chunk* chunk, uint8_t opt)
        {
            if (opt) { chunk->ChunkHeader.chunkHeader |= opt << 3; }
            else     { chunk->ChunkHeader.chunkHeader &= opt << 3; }
        };  
    };
}