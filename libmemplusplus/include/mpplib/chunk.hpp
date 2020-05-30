#pragma once

#include <cstdint>

namespace mpp {

    struct Chunk
    {
        /*
    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |            Size of chunk, in bytes        |U|P|X|X|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |            User data starts here...               .
            .                                                   .
            .            (ChunkUsableSize() bytes)              .
            .                                                   |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
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

        bool IsPrevInUse()
        {
            return (this->ChunkHeader.chunkHeader & 0b111) >> 2;
        };

        void SetIsPrevInUse(uint8_t opt)
        {
            if (opt) {
                this->ChunkHeader.chunkHeader |= opt << 2;
            } else {
                this->ChunkHeader.chunkHeader &= opt << 2;
            }
        };

        void SetIsUsed(uint8_t opt)
        {
            if (opt) {
                this->ChunkHeader.chunkHeader |= opt << 3;
            } else {
                this->ChunkHeader.chunkHeader &= opt << 3;
            }
        };
    };
}