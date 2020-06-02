#pragma once

#include <cstdint>
#include <iostream>

namespace mpp {

    /**
     * Basic allocator structure
     */
    struct Chunk
    {
        /*
    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |            Size of chunk, in bytes       |X|U|P|X|X|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |            User data starts here...               .
            .                                                   .
            .            (ChunkUsableSize() bytes)              .
            .                                                   |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        */
        struct ChunkHeader_t
        {
            std::size_t prevChunkSize;
            std::size_t chunkHeader;
        } ChunkHeader;

        static Chunk* ConstructChunk(void* t_newChunkPtr,
                                     std::size_t t_prevSize,
                                     std::size_t t_chunkSize,
                                     uint8_t t_isInUse,
                                     uint8_t t_isPrevInUse)
        {
            Chunk* newChunk = (Chunk*)t_newChunkPtr;
            newChunk->SetPrevSize(t_prevSize);
            newChunk->SetSize(t_chunkSize);
            newChunk->SetIsUsed(t_isInUse);
            newChunk->SetIsPrevInUse(t_isPrevInUse);

            return newChunk;
        }

        static void* GetUserDataPtr(Chunk* t_chunk)
        {
            return (void*)((std::size_t)t_chunk + sizeof(Chunk::ChunkHeader));
        }

        static Chunk* GetHeaderPtr(void* t_userData)
        {
            return (Chunk*)((std::size_t)t_userData - sizeof(Chunk::ChunkHeader));
        }

        static Chunk* GetPrevChunk(Chunk* t_chunk)
        {
            // 1. Compute prev chunk pointer
            // 2. Call IsUsed for this pointer
            return ((Chunk*)((std::size_t)t_chunk - t_chunk->GetPrevSize()));
        }

        static Chunk* GetNextChunk(Chunk* t_chunk)
        {
            return (Chunk*)((std::size_t)t_chunk + t_chunk->GetSize());
        }

        std::size_t GetPrevSize()
        {
            return (this->ChunkHeader.prevChunkSize >> 5) << 5;
        };

        void SetPrevSize(std::size_t size)
        {
            this->ChunkHeader.prevChunkSize = size;
        }

        std::size_t GetSize()
        {
            return (this->ChunkHeader.chunkHeader >> 5) << 5;
        };

        void SetSize(std::size_t size)
        {
            this->ChunkHeader.chunkHeader =
              (size | (0b11111 & this->ChunkHeader.chunkHeader));
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
                this->ChunkHeader.chunkHeader |= 1UL << 2;
            } else {
                this->ChunkHeader.chunkHeader &= ~(1UL << 2);
            }
        };

        void SetIsUsed(uint8_t opt)
        {
            if (opt) {
                this->ChunkHeader.chunkHeader |= 1UL << 3;
            } else {
                this->ChunkHeader.chunkHeader &= ~(1UL << 3);
            }
        };

        static std::ostream& DumpChunk(std::ostream& t_out, Chunk* t_ch)
        {
            return t_out << "[" << reinterpret_cast<void*>(t_ch) << "]("
                         << t_ch->GetPrevSize() << ", " << t_ch->GetSize()
                         << "|InUse:" << t_ch->IsUsed()
                         << "|PrevInUse:" << t_ch->IsPrevInUse() << ")";
        }

        friend std::ostream& operator<<(std::ostream& t_out, Chunk* t_ch)
        {
            return t_out << "[" << reinterpret_cast<void*>(t_ch) << "]("
                         << t_ch->GetPrevSize() << ", " << t_ch->GetSize()
                         << "|InUse:" << t_ch->IsUsed()
                         << "|PrevInUse:" << t_ch->IsPrevInUse() << ")";
        }
    };
}