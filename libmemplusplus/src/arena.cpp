#include "mpplib/arena.hpp"

namespace mpp {
    Chunk* Arena::AllocateFromTopChunk(std::size_t t_chunkSize)
    {
        Chunk* chunk = SplitTopChunk(t_chunkSize);
        chunksInUse.insert(chunk);
        return chunk;
    }

    // WARNING
    Chunk* Arena::SplitTopChunk(std::size_t t_chunkSize)
    {
        if (t_chunkSize == topChunk->GetSize())
        {
            Chunk* chunk = Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);
        
            // make topChunk nullptr, to let allocator know, that we dont
            // have any more space in current arena. This field can be 
            // updated later in deallocate, if we managed to merge everything
            // on right side
            topChunk = nullptr;
            return chunk;
        }

        std::size_t newTopChunkSize = topChunk->GetSize() - t_chunkSize;
        //(*) chunk->GetPrevSize() == 0 <=> chunk == this->begin
        Chunk* chunk = Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);
        topChunk = Chunk::ConstructChunk(static_cast<Chunk*>((std::size_t)topChunk + t_chunkSize), 
                                  t_chunkSize, newTopChunkSize, 1, 1);
        //(!) Add testcase with splitting topchunk to the minimal size (16)
        return chunk;
    }

    Chunk* Arena::AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);
    {
        Chunk* chunk = SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize);
        chunksInUse.insert(chunk);
        return chunk;
    }
    
    Chunk* Arena::SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {    
        // If we are working with the first chunk in arena memory
        freedChunks.RemoveChunk(t_chunk);
        if (t_chunk == begin)
        {
            if (t_chunk->GetSize() == t_chunkSize)
            {
                // Set prevInUse to 1, because we don't want to merge it to the left 
                // (cause we dont have anything on the left)
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0,
                                              t_chunkSize, 1, 1);
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
            } else {
                std::size_t toSplitChunkSize = t_chunk->GetSize();
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0,
                                              t_chunkSize, 1, 1);

                Chunk* splittedChunk = Chunk::ConstructChunk((void*)((std::size_t)chunk + t_chunkSize),
                                t_chunkSize, toSplitChunkSize - t_chunkSize,
                                0, 1);
                Chunk::GetNextChunk(splittedChunk)->SetPrevSize(toSplitChunkSize - t_chunkSize);
                // Chunk::GetNextChunk(splittedChunk)->SetIsPrevInUse(0);
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
        } else {
        // if we are anywhere in arena, excluding begin chunk
            // Split free (deallocated) chunk
            if (t_chunk->GetSize() == t_chunkSize)
            {
                Chunk* chunk = Chunk::ConstractChunk(t_chunk,
                                              Chunk::GetPrevChunk(t_chunk)->GetSize(),
                                              t_chunkSize,
                                              1, 1);
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
            } else {
                std::size_t toSplitChunkSize = t_chunk->GetSize();
                Chunk* chunk = Chunk::ConstructChunk(t_chunk,
                                                     Chunk::GetPrevChunk(t_chunk)->GetSize(),
                                                     t_chunkSize,
                                                     1, 1);
                Chunk* splittedChunk = Chunk::ConstructChunk((void*)((std::size_t)chunk + t_chunkSize),
                                                             t_chunkSize, toSplitChunkSize - t_chunkSize,
                                                             0, 1);
                Chunk::GetNextChunk(splittedChunk)->SetPrevSize(toSplitChunkSize - t_chunkSize);
                // Chunk::GetNextChunk(splittedChunk)->SetIsPrevInUse(0);
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
        }
    }
    
    // Remember to set isPrevInUse to 1 when deallocating
    void Arena::DeallocateChunk(Chunk* t_chunk)
    {
        // set fields
        // merge
        // add to chunk treap
        // RightMostChunk

        /*
        F - freed
        A - allocated
        D - to deallocate
        T - top (can be nullptr)

        General case:
            FDF
            FDA
            ADF
            ADA
        
        Starting case:
            DA
            DF

        Top case:
            FDT
            ADT
            DT
            T

        5,6->7->10
        
        */

        newChunk = MergeNeighborsChunks(t_chunk);
        if (newChunk != topChunk)
        {
            freedChunks.InsertChunk(newChunk);
        }
        return;
    }

  
    // Remember to check if topChunk is nullptr
    // if it is, then we must check that chunk
    // is top, and after merging everything, we should update topChunk
    // to point to new chunk
    Chunk* Arena::MergeNeighborsChunks(Chunk* t_chunk)
    {
        if (
            ((topChunk == nullptr) && (((void*)(std::size_t)t_chunk + t_chunk->GetSize()) == end))
            || (Chunk::GetNextChunk(t_chunk) == topChunk)
           )
        {
            return MergeWithTop(t_chunk);
        }

        Chunk* newChunk{ t_chunk };
        if (Chunk::GetNextChunk(t_chunk)->IsUsed() == 0)
        {
            newChunk = MergeTwoSequnceChunks(newChunk, Chunk::GetNextChunk(t_chunk));
        }

        if (Chunk::GetPrevChunk(newChunk)->IsUsed() == 0)
        {
            newChunk = MergeTwoSequnceChunks(Chunk::GetPrevChunk(newChunk), newChunk);
        }
        
        if (newChunk != begin)
        {
            newChunk->SetPrevSize(Chunk::GetPrevChunk(topChunk)->GetSize())
            newChunk->SetIsPrevInUse(1);
            newChunk->SetIsUsed(0);
            return newChunk;
        }
        else
        {
            newChunk->SetPrevSize(0);
            newChunk->SetIsPrevInUse(1);
            newChunk->SetIsUsed(0);
            return newChunk;
        }

        return newChunk;
    }

    Chunk* Arena::MergeWithTop(Chunk* t_chunk)
    {
        Chunk* newChunk{ t_chunk };
        if (Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0)
        {
            newChunk = MergeTwoSequnceChunks(Chunk::GetPrevChunk(t_chunk), t_chunk);
        }

        if (topChunk == nullptr)
        {
            topChunk = newChunk;
            if (topChunk != begin)
            {
                topChunk->SetPrevSize(Chunk::GetPrevChunk(topChunk)->GetSize())
                topChunk->SetIsPrevInUse(1);
                topChunk->SetIsUsed(1);
                return topChunk;
            }
            else
            {
                //ChunkSize is already set by MergeTwoSequnceChunks function
                topChunk->SetPrevSize(0);
                topChunk->SetIsPrevInUse(1);
                topChunk->SetIsUsed(1);
            }
            
        }
        else
        {
            topChunk = MergeTwoSequnceChunks(newChunk, topChunk);
            return topChunk;
        }
    }

    // Note that MergeTwoSequnceChunks doesn't check order of the
    // chunks. Also it doesn't update any flags, and/or any chunk fields
    // excluding chunk size
    Chunk* Arena::MergeTwoSequnceChunks(Chunk* t_chunk1, Chunk* t_chunk2)
    {
        Chunk* tmpChunk = Chunk::ConstructChunk(t_chunk1, t_chunk1->GetPrevSize(), 
                                        t_chunk1->GetSize() + t_chunk2->GetSize(), 
                                        0, 0);
        return tmpChunk;
    }
}