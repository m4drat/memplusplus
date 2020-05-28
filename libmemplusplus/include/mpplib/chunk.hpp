#pragma once

namespace mpp {

    class ChunkPrototype 
    {   
        public:
        struct Chunk
        {
            unsigned int chunkHeader;
        };

        bool GetSize(Chunk* chunk) {
            return (chunk->chunkHeader  >> 4) << 4;
        };

        void* GetUserData(Chunk* chunk) {
            return chunk + sizeof(Chunk::chunkHeader);
        };

        bool IsUsed(Chunk* chunk) {
            return (chunk->chunkHeader & 0b1111) >> 3;
        };

    };

}