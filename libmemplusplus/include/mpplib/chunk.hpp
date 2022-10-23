#pragma once

#include "mpplib/utils/macros.hpp"
#include <cstdint>
#include <iostream>

#if MPP_COLOUR == 1
#include "mpplib/utils/colours.hpp"
namespace col = mpp::utils::colours;
#endif

namespace mpp {

    /**
     * @brief Represent chunk of memory.
     */
    struct Chunk
    {
        /**
         * @brief chunk header structure.
         */
        struct ChunkHeader_t
        {
            /**
             * @brief Size of the previous chunk.
             */
            std::size_t prevChunkSize;

            /**
             * @brief actual chunk header.
             *
             * Contains all required mark bits. Maximum amount of mark bits is 5.
             * Currently used only 2.
             * Bit-2: Previous chunk in use
             * Bit-3: Current chunk in use
             */
            std::size_t chunkHeader;
        } ChunkHeader;

        static constexpr uint32_t EXTRACT_SIZE_SHIFT = 5;
        static constexpr uint32_t INFO_BITS_MASK = 0b11111;
        static constexpr uint32_t IS_USED_BIT_MASK = 0b1111;
        static constexpr uint32_t IS_USED_SHIFT = 3;
        static constexpr uint32_t IS_PREV_IN_USE_BIT_MASK = 0b111;
        static constexpr uint32_t IS_PREV_IN_USE_SHIFT = 2;

        /**
         * @brief Constructs new chunk at location, passed as first parameter.
         * @param t_newChunkPtr actual memory, where chunk is going to be constructed.
         * @param t_prevSize previous chunk size value.
         * @param t_chunkSize current chunk size value.
         * @param t_isInUse current chunk in use bit.
         * @param t_isPrevInUse previous chunk in use bit.
         * @return Chunk* with all fields set to passed parameters
         */
        static Chunk* ConstructChunk(void* t_newChunkPtr,
                                     std::size_t t_prevSize,
                                     std::size_t t_chunkSize,
                                     uint8_t t_isInUse,
                                     uint8_t t_isPrevInUse)
        {
            auto* newChunk = static_cast<Chunk*>(t_newChunkPtr);

            MPP_UNPOISON_MEM(newChunk, t_chunkSize);

            newChunk->SetPrevSize(t_prevSize);
            newChunk->SetSize(t_chunkSize);
            newChunk->SetIsUsed(t_isInUse);
            newChunk->SetIsPrevInUse(t_isPrevInUse);

            return newChunk;
        }

        /**
         * @brief Get pointer to user data, from pointer to chunk.
         * @param t_chunk actual chunk, to get pointer to user data from.
         * @return void* pointer to start of user data in current chunk
         */
        static void* GetUserDataPtr(Chunk* t_chunk)
        {
            return reinterpret_cast<void*>(reinterpret_cast<std::byte*>(t_chunk) +
                                           sizeof(Chunk::ChunkHeader));
        }

        /**
         * @brief Get pointer to chunk header from user data pointer.
         * @param t_userData pointer to user data
         * @return Chunk* pointer to chunk header
         */
        static Chunk* GetHeaderPtr(void* t_userData)
        {
            return reinterpret_cast<Chunk*>(reinterpret_cast<std::byte*>(t_userData) -
                                            sizeof(Chunk::ChunkHeader));
        }

        /**
         * @brief Get previous chunk in memory.
         * @param t_chunk chunk pointer.
         * @return Chunk* located previously in memory chunk
         */
        static Chunk* GetPrevChunk(Chunk* t_chunk)
        {
            return reinterpret_cast<Chunk*>(reinterpret_cast<std::byte*>(t_chunk) -
                                            t_chunk->GetPrevSize());
        }

        /**
         * @brief Get next chunk in memory.
         * @param t_chunk chunk pointer.
         * @return Chunk* located right after specified chunk
         */
        static Chunk* GetNextChunk(Chunk* t_chunk)
        {
            return reinterpret_cast<Chunk*>(reinterpret_cast<std::byte*>(t_chunk) +
                                            t_chunk->GetSize());
        }

        /**
         * @brief Get previous size from chunk header.
         * @return std::size_t extracted from header previous size value
         */
        std::size_t GetPrevSize() const
        {
            return (this->ChunkHeader.prevChunkSize >> EXTRACT_SIZE_SHIFT) << EXTRACT_SIZE_SHIFT;
        };

        /**
         * @brief Set previous size in chunk header
         * @param size new size to set
         */
        void SetPrevSize(std::size_t size)
        {
            this->ChunkHeader.prevChunkSize = size;
        }

        /**
         * @brief Get size of current chunk from its chunk header.
         * @return std::size_t current chunk size
         */
        std::size_t GetSize() const
        {
            return (this->ChunkHeader.chunkHeader >> EXTRACT_SIZE_SHIFT) << EXTRACT_SIZE_SHIFT;
        };

        /**
         * @brief Set size of current chunk.
         *
         * This function wouldn't change any flag bits.
         * @param size new size value.
         */
        void SetSize(std::size_t size)
        {
            this->ChunkHeader.chunkHeader =
                (size | (INFO_BITS_MASK & this->ChunkHeader.chunkHeader));
        }

        /**
         * @brief Get pointer to user data, from current chunk.
         * @return void* pointer to start of user data in current chunk
         */
        void* GetUserData()
        {
            return this + sizeof(Chunk::ChunkHeader);
        };

        /**
         * @brief returns state of current chunk. (in use / isn't in use)
         * @return true if current chunk is in use
         * @return false if current chunk isn't in use
         */
        bool IsUsed() const
        {
            return (this->ChunkHeader.chunkHeader & IS_USED_BIT_MASK) >> IS_USED_SHIFT;
        };

        /**
         * @brief returns state of previous in memory chunk. (in use / isn't in use)
         * @return true if previous chunk is in use
         * @return false if previous chunk isn't in use
         */
        bool IsPrevInUse() const
        {
            return (this->ChunkHeader.chunkHeader & IS_PREV_IN_USE_BIT_MASK) >>
                   IS_PREV_IN_USE_SHIFT;
        };

        /**
         * @brief Update value of PrevInUse flag.
         * @param opt new value for PrevInUse flag.
         */
        void SetIsPrevInUse(uint8_t opt)
        {
            if (opt) {
                this->ChunkHeader.chunkHeader |= 1UL << IS_PREV_IN_USE_SHIFT;
            } else {
                this->ChunkHeader.chunkHeader &= ~(1UL << IS_PREV_IN_USE_SHIFT);
            }
        };

        /**
         * @brief Update value of InUse flag.
         * @param opt new value for InUse flag.
         */
        void SetIsUsed(uint8_t opt)
        {
            if (opt) {
                this->ChunkHeader.chunkHeader |= 1UL << IS_USED_SHIFT;
            } else {
                this->ChunkHeader.chunkHeader &= ~(1UL << IS_USED_SHIFT);
            }
        };

#if MPP_STATS == 1
        /**
         * @brief Helper method to dump chunk structure in human-readable format.
         * @param t_out stream to write to.
         * @param t_ch chunk pointer.
         * @return std::ostream& stream that was used
         */
        static std::ostream& DumpChunk(std::ostream& t_out, Chunk* t_ch)
        {
#if MPP_COLOUR == 1
            t_out << "[" << reinterpret_cast<void*>(t_ch) << "](" << t_ch->GetPrevSize() << ", "
                  << col::BRIGHT_BLUE << t_ch->GetSize() << col::RESET;

            if (t_ch->IsUsed()) {
                t_out << "|InUse:" << col::GREEN << t_ch->IsUsed() << col::RESET;
            } else {
                t_out << "|InUse:" << col::RED << t_ch->IsUsed() << col::RESET;
            }

            if (t_ch->IsPrevInUse()) {
                t_out << "|PrevInUse:" << col::GREEN << t_ch->IsPrevInUse() << col::RESET << ")";
            } else {
                t_out << "|PrevInUse:" << col::RED << t_ch->IsPrevInUse() << col::RESET << ")";
            }
#else
            t_out << "[" << reinterpret_cast<void*>(t_ch) << "](" << t_ch->GetPrevSize() << ", "
                  << t_ch->GetSize() << "|InUse:" << t_ch->IsUsed()
                  << "|PrevInUse:" << t_ch->IsPrevInUse() << ")";
#endif

            return t_out;
        }

        /**
         * @brief Overloaded "<<" operator to dump chunk structure in human-readable
         * format.
         * @param t_out stream to write to.
         * @param t_ch chunk pointer.
         * @return std::ostream& stream that was used
         */
        friend std::ostream& operator<<(std::ostream& t_out, Chunk* t_ch)
        {
            return DumpChunk(t_out, t_ch);
        }
#endif
    };
}