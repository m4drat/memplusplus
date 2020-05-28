#pragma once

#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"

namespace mpp {
    Chunk* Arena::AllocateChunk(std::size_t t_chunkSize)
    {
        if (this->rightSpace >= t_chunkSize)
        {
            Chunk* chunk = new Chunk()
            return chunk
        }
        
        //currentChunkSize = Chunk::GetSize( static_cast<Chunk*>(i) );
        size_t currentChunkSize;
        for (int i; i < (this->end - this->rightSpace); i + currentChunkSize )
        {
            currentChunkSize = Chunk::GetSize( static_cast<Chunk*>(i) );
            if (!Chunk::IsUsed(static_cast<Chunk*>(i)))
            {
                if (currentChunkSize >= t_chunkSize)
                {
                    Chunk* chunk = new Chunk()
                    return chunk
                }
            }
        }
    }

    void Arena::DeallocateChunk(Chunk* t_chunk)
    {
        t_chunk->SetIsUsed(t_chunk, 0);
        // WARNING: check if it's actually work
        this->chunksInUse.erase(t_chunk);
        //this->chunksInUse.erase(this->chunksInUse.begin() + this->chunksInUse.find(t_chunk));
    }
}