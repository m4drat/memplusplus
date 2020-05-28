#pragma once

namespace mpp {

    struct Chunk
    {
        struct ChunkHeader_t
        {
            unsigned int chunkHeader;
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
    };

}