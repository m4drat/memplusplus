#include "mpplib/arena.hpp"
#include "mpplib/memory_allocator.hpp"

#include <functional>

namespace mpp {
    Arena::Arena(std::size_t t_size, void* t_begin)
    {
        size = t_size;
        topChunk = Chunk::ConstructChunk(t_begin, 0, t_size, 1, 1);
        begin = t_begin;
        end = reinterpret_cast<void*>(reinterpret_cast<std::size_t>(t_begin) + t_size);
    };

    Arena::~Arena()
    {
        // TODO: correctly destroy ChunkTreap
        freedChunks.Delete();
        chunksInUse.clear();
        MemoryAllocator::SysDealloc(this->begin, size);
    }

    Chunk* Arena::GetFirstGreaterOrEqualThanChunk(std::size_t t_desiredChunkSize)
    {
        return freedChunks.FirstGreaterOrEqualThan(t_desiredChunkSize);
    }

    Chunk* Arena::AllocateFromTopChunk(std::size_t t_chunkSize)
    {
        Chunk* chunk = SplitTopChunk(t_chunkSize);
        chunksInUse.insert(chunk);
        CurrentlyAllocatedSpace += t_chunkSize;
        return chunk;
    }

    Chunk* Arena::SplitTopChunk(std::size_t t_chunkSize)
    {
        if (t_chunkSize == topChunk->GetSize()) {
            Chunk* chunk =
              Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);

            // make topChunk nullptr, to let allocator know, that we dont
            // have any more space in current arena. This field can be
            // updated later in deallocate, if we managed to merge everything
            // on right side
            topChunk = nullptr;
            return chunk;
        }

        std::size_t newTopChunkSize = topChunk->GetSize() - t_chunkSize;
        //(*) chunk->GetPrevSize() == 0 <=> chunk == this->begin
        Chunk* chunk =
          Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);
        topChunk = Chunk::ConstructChunk(
          reinterpret_cast<Chunk*>(reinterpret_cast<size_t>(topChunk) + t_chunkSize),
          t_chunkSize,
          newTopChunkSize,
          1,
          1);
        //(!) Add testcase with splitting topchunk to the minimal size (16)
        return chunk;
    }

    Chunk* Arena::AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        Chunk* chunk = SplitChunkFromFreeList(t_chunk, t_chunkSize);
        chunksInUse.insert(chunk);
        CurrentlyAllocatedSpace += t_chunkSize;
        return chunk;
    }

    Chunk* Arena::SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        // If we are working with the first chunk in arena memory
        freedChunks.RemoveChunk(t_chunk);
        if (t_chunk == begin) {
            if (t_chunk->GetSize() == t_chunkSize) {
                // Set prevInUse to 1, because we don't want to merge it to the
                // left (cause we dont have anything on the left)
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
            } else {
                std::size_t toSplitChunkSize = t_chunk->GetSize();
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);

                Chunk* splittedChunk = Chunk::ConstructChunk(
                  reinterpret_cast<void*>(reinterpret_cast<std::size_t>(chunk) +
                                          t_chunkSize),
                  t_chunkSize,
                  toSplitChunkSize - t_chunkSize,
                  0,
                  1);
                Chunk::GetNextChunk(splittedChunk)
                  ->SetPrevSize(toSplitChunkSize - t_chunkSize);
                // Chunk::GetNextChunk(splittedChunk)->SetIsPrevInUse(0);
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
        } else {
            // if we are anywhere in arena, excluding begin chunk
            // Split free (deallocated) chunk
            if (t_chunk->GetSize() == t_chunkSize) {
                Chunk* chunk = Chunk::ConstructChunk(
                  t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
            } else {
                std::size_t toSplitChunkSize = t_chunk->GetSize();
                Chunk* chunk = Chunk::ConstructChunk(
                  t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);
                Chunk* splittedChunk = Chunk::ConstructChunk(
                  reinterpret_cast<void*>(reinterpret_cast<size_t>(chunk) + t_chunkSize),
                  t_chunkSize,
                  toSplitChunkSize - t_chunkSize,
                  0,
                  1);
                Chunk::GetNextChunk(splittedChunk)
                  ->SetPrevSize(toSplitChunkSize - t_chunkSize);
                // Chunk::GetNextChunk(splittedChunk)->SetIsPrevInUse(0);
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
        }
    }

    // Remember to set isPrevInUse to 1 when deallocating
    void Arena::DeallocateChunk(Chunk* t_chunk)
    {
        /*
        F - freed
        A - allocated
        D - to deallocate
        T - top (can be nullptr)
        */

        // Delete chunk from active chunks
        chunksInUse.erase(t_chunk);
        CurrentlyAllocatedSpace -= t_chunk->GetSize();
        Chunk* newChunk = MergeNeighborsChunks(t_chunk);
        if (newChunk != topChunk) {
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
        /*
        1. T
        2. FDT
        3. ADT
        4. DT
        */
        if (((topChunk == nullptr) &&
             (reinterpret_cast<void*>(reinterpret_cast<std::size_t>(t_chunk) +
                                      t_chunk->GetSize()) == end)) ||
            (Chunk::GetNextChunk(t_chunk) == topChunk)) {
            return MergeWithTop(t_chunk);
        }

        /*
            1. DA
            2. DF
            3. FDA
            4. ADF
            5. FDF
            6. ADA
        */
        Chunk* newChunk{ t_chunk };

        // Merge forward
        if (Chunk::GetNextChunk(t_chunk)->IsUsed() == 0) {
            freedChunks.RemoveChunk(Chunk::GetNextChunk(t_chunk));
            newChunk = MergeTwoSequnceChunks(newChunk, Chunk::GetNextChunk(t_chunk));
        }

        // Merge backwards
        if ((reinterpret_cast<void*>(t_chunk) != begin) &&
            Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            newChunk = MergeTwoSequnceChunks(Chunk::GetPrevChunk(newChunk), newChunk);
        }

        if (newChunk != begin) {
            newChunk->SetPrevSize(Chunk::GetPrevChunk(newChunk)->GetSize());
        } else {
            newChunk->SetPrevSize(0);
        }
        Chunk::GetNextChunk(newChunk)->SetIsPrevInUse(0);
        Chunk::GetNextChunk(newChunk)->SetPrevSize(newChunk->GetSize());
        newChunk->SetIsPrevInUse(1);
        newChunk->SetIsUsed(0);

        return newChunk;
    }

    Chunk* Arena::MergeWithTop(Chunk* t_chunk)
    {
        // if (topChunk != nullptr)
        //     freedChunks.RemoveChunk(t_chunk);
        Chunk* newChunk{ t_chunk };
        if ((reinterpret_cast<void*>(t_chunk) != begin) &&
            Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            // freedChunks.RemoveChunk(t_chunk);
            newChunk = MergeTwoSequnceChunks(Chunk::GetPrevChunk(t_chunk), t_chunk);
        }

        if (topChunk == nullptr) {
            topChunk = newChunk;
            if (reinterpret_cast<void*>(topChunk) != begin) {
                topChunk->SetPrevSize(Chunk::GetPrevChunk(topChunk)->GetSize());
            } else {
                // ChunkSize is already set by MergeTwoSequnceChunks function
                topChunk->SetPrevSize(0);
            }
            topChunk->SetIsPrevInUse(1);
            topChunk->SetIsUsed(1);
            return topChunk;
        } else {
            topChunk = MergeTwoSequnceChunks(newChunk, topChunk);
            topChunk->SetIsPrevInUse(1);
            topChunk->SetIsUsed(1);
            return topChunk;
        }
    }

    // Note that MergeTwoSequnceChunks doesn't check order of the
    // chunks. Also it doesn't update any flags, and/or any chunk fields
    // excluding chunk size
    Chunk* Arena::MergeTwoSequnceChunks(Chunk* t_chunk1, Chunk* t_chunk2)
    {
        Chunk* chunk = Chunk::ConstructChunk(t_chunk1,
                                             t_chunk1->GetPrevSize(),
                                             t_chunk1->GetSize() + t_chunk2->GetSize(),
                                             0,
                                             0);
        return chunk;
    }

    Chunk* Arena::GetInUseChunkByPtr(void* t_ptr)
    {
        auto foundChunkIt =
          utils::LowerBound(chunksInUse.begin(),
                            chunksInUse.end(),
                            t_ptr,
                            [](Chunk* t_ch, void* t_ptr) -> bool {
                                return (t_ptr >= reinterpret_cast<void*>(t_ch));
                            });
        if (foundChunkIt != chunksInUse.end() && *foundChunkIt == t_ptr) {
            return *foundChunkIt;
        }
        return *(--foundChunkIt);
    }

    std::size_t Arena::GetUsedSpace()
    {
        return CurrentlyAllocatedSpace;
    }

    void Arena::SetUsedSpace(std::size_t t_newSize)
    {
        CurrentlyAllocatedSpace = t_newSize;
    }

    std::ostream& Arena::DumpArena(std::ostream& t_out, Arena* t_arena)
    {
        t_out << "Arena: " << reinterpret_cast<void*>(t_arena) << std::endl;

        t_out << "\tsize: " << t_arena->size << std::endl;
        t_out << "\tCurrentlyAllocatedSpace: " << t_arena->CurrentlyAllocatedSpace
              << std::endl;

        t_out << "\ttopChunk: ";
        if (t_arena->topChunk)
            Chunk::DumpChunk(t_out, t_arena->topChunk);
        else
            t_out << "nullptr";
        t_out << std::endl;

        t_out << "\tbegin: " << t_arena->begin << std::endl;
        t_out << "\tend: " << t_arena->end << std::endl;

        t_out << "\tfreedChunks nodes: " << std::endl;
        int32_t idx1 = 0;
        std::function<void(std::ostream&, Node*)> Iterate = [&](std::ostream& out,
                                                                Node* node) {
            if (!node)
                return;

            Iterate(out, node->rightChild);
            out << "\t\t" << idx1 << ". " << node << std::endl;
            idx1++;
            Iterate(out, node->leftChild);
        };
        Iterate(std::cout, t_arena->freedChunks.GetRootNode());

        t_out << "\tchunksInUse: " << std::endl;
        int32_t idx2 = 0;
        for (auto ch : t_arena->chunksInUse) {
            t_out << "\t\t" << idx2 << ". ";
            Chunk::DumpChunk(t_out, ch) << std::endl;
            idx2++;
        }
        return t_out;
    }
}