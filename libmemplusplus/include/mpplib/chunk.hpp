#pragma once

namespace mpp {

    struct Chunk
    {
        struct ChunkHeader
        {
            uint32_t chunkHeader;
            // in_use bit
        };

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