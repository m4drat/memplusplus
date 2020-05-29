#pragma once

#include <cstdint>

namespace mpp {

    struct Chunk
    {

        /**
         * What we should have here?
         * 1. InUse bit
         * 2. Should we have pointer to the next freed chunk?
         */
        struct ChunkHeader_t
        {
            uint32_t chunkHeader;
        } ChunkHeader;

        std::size_t GetSize() 
        { 
            return (this->ChunkHeader.chunkHeader >> 4) << 4;
        };

        void SetSize(std::size_t size)
        {
            this->ChunkHeader.chunkHeader = size;
        }

        void* GetUserData()
        {
            return this + sizeof(Chunk::ChunkHeader);
        };

        bool IsUsed()
        {
            return (this->ChunkHeader.chunkHeader & 0b1111) >> 3;
        };

        void SetIsUsed(uint8_t opt)
        {
            if (opt) { this->ChunkHeader.chunkHeader |= opt << 3; }
            else     { this->ChunkHeader.chunkHeader &= opt << 3; }
        };  
    };
}