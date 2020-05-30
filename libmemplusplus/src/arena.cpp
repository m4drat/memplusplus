#include "mpplib/arena.hpp"

namespace mpp {
    Chunk* Arena::AllocateChunkFromRightSpace(std::size_t t_chunkSize)
    {
        Chunk* chunk = (Chunk*)this->rightSpaceStart;
        chunk->SetIsUsed(1);
        chunk->SetSize(t_chunkSize);
        // if chunk

        this->rightSpaceStart = reinterpret_cast<void*>((std::size_t)(this->rightSpaceStart) + t_chunkSize); 
        return chunk;
    }

    Chunk* Arena::ReuseChunk(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        return nullptr;
    }

    void Arena::MergeNeighborsChunks(Chunk* t_chunk)
    {

    }
}