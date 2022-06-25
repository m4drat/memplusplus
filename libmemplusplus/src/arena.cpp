#include "mpplib/arena.hpp"
#include "mpplib/memory_manager.hpp"

#include <functional>

namespace mpp {
    Arena::Arena(std::size_t t_size, std::byte* t_begin)
        : size{ t_size }
        , topChunk{ Chunk::ConstructChunk(t_begin, 0, t_size, 1, 1) }
        , begin{ t_begin }
        , end{ t_begin + t_size }
    {
        PROFILE_FUNCTION();
#if MPP_STATS == 1
        arenaStats = std::make_shared<utils::Statistics::ArenaStats>();
        utils::Statistics::GetInstance().AddArenaStats(arenaStats);
        arenaStats->totalAllocated = 0;
        arenaStats->totalFreed = 0;
        arenaStats->biggestAllocation = 0;
        arenaStats->smallestAllocation = std::numeric_limits<std::size_t>::max();
        arenaStats->fullArenaSize = t_size;
        arenaStats->bigArena = false;
        arenaStats->gcCreatedArena = false;
#endif
    }

    Arena::~Arena()
    {
        PROFILE_FUNCTION();

        chunksInUse.clear();
        MemoryManager::SysDealloc(this->begin, size);
    }

    std::size_t Arena::FreeMemoryInsideChunkTreap()
    {
        return freedChunks.GetAmountOfFreedMemory();
    }

    Chunk* Arena::GetFirstGreaterOrEqualThanChunk(std::size_t t_desiredChunkSize) const
    {
        PROFILE_FUNCTION();
        // Find suitable chunk in treap of freed chunks
        return freedChunks.FirstGreaterOrEqualThan(t_desiredChunkSize);
    }

    Chunk* Arena::AllocateFromTopChunk(std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // We have enough space in top chunk, so in this case
        // we just need to split it in smaller chunks
        Chunk* chunk = SplitTopChunk(t_chunkSize);

#if MPP_STATS == 1
        arenaStats->totalAllocated += t_chunkSize;
        if (chunk->GetSize() > arenaStats->biggestAllocation) {
            arenaStats->biggestAllocation = chunk->GetSize();
        }
        if (chunk->GetSize() < arenaStats->smallestAllocation) {
            arenaStats->smallestAllocation = chunk->GetSize();
        }
#endif

        // Keep track of in use chunks
        chunksInUse.insert(chunk);

        // update current allocated space
        m_currentlyAllocatedSpace += t_chunkSize;
        return chunk;
    }

    Chunk* Arena::SplitTopChunk(std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // Size of requested chunk is equal to size of top chunk
        if (t_chunkSize == topChunk->GetSize()) {
            // Construct new chunk from all memory, that belongs to top chunk
            Chunk* chunk =
                Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);

            // make topChunk nullptr, to let allocator know, that we dont
            // have any more top-space in current arena. This field can be
            // updated later in deallocate, if we managed to merge everything
            // on the right side
            topChunk = nullptr;
            return chunk;
        }

        // Splitting top chunk in smaller chunks
        std::size_t newTopChunkSize = topChunk->GetSize() - t_chunkSize;

        // Constructing new chunk from splitted memory
        Chunk* chunk = Chunk::ConstructChunk(topChunk, topChunk->GetPrevSize(), t_chunkSize, 1, 1);

        // Update top chunk
        topChunk = Chunk::ConstructChunk(reinterpret_cast<std::byte*>(topChunk) + t_chunkSize,
                                         t_chunkSize,
                                         newTopChunkSize,
                                         1,
                                         1);

        return chunk;
    }

    Chunk* Arena::AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // Extract chunk from free list, and split it if needed
        Chunk* chunk = SplitChunkFromFreeList(t_chunk, t_chunkSize);

        // Keep track of inuse chunks
        chunksInUse.insert(chunk);

#if MPP_STATS == 1
        arenaStats->totalAllocated += t_chunkSize;
#endif

        // Update used space variable
        m_currentlyAllocatedSpace += t_chunkSize;

        return chunk;
    }

    Chunk* Arena::SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();

        // Delete chunk, that we are currently working with from
        // free list
        freedChunks.RemoveChunk(t_chunk);

        // First case, chunk to split is the first chunk inside arena
        // memory layout: [t_chunk][....]
        if (static_cast<void*>(t_chunk) == begin) {
            // First chunk size is equal to requested size
            if (t_chunk->GetSize() == t_chunkSize) {
                // Set prevInUse to 1, because we don't want to merge it to the
                // left (cause we dont have anything on the left)
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
                // First chunks size doesn't equal to requested size
            } else {
                // First chunk (is going to be splitted)
                std::size_t toSplitChunkSize = t_chunk->GetSize();

                // Splitting first chunk, this is going to be returned
                // to the user
                Chunk* chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);

                // Update the fields of the remaining chunk
                Chunk* splittedChunk =
                    Chunk::ConstructChunk(reinterpret_cast<std::byte*>(chunk) + t_chunkSize,
                                          t_chunkSize,
                                          toSplitChunkSize - t_chunkSize,
                                          0,
                                          1);

                // Update previous size for the next chunk after splitted
                // current memory layout: [user-returned][splitted part][next chunk after
                // splitted]
                Chunk::GetNextChunk(splittedChunk)->SetPrevSize(toSplitChunkSize - t_chunkSize);

                // Keep track of splitted part, by placing it into
                // free list
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
            // Second case: we are anywhere in arena, excluding first chunk
            // memory layout: [...][t_chunk][....]
        } else {
            // t_chunk size is equal to requesteed size, so we don't need
            // to split it in smaller parts
            if (t_chunk->GetSize() == t_chunkSize) {
                // Construct new chunk
                Chunk* chunk = Chunk::ConstructChunk(
                    t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);

                // Update inuse bit
                Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);

                // Update previous size
                Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
                return chunk;
            } else {
                // Chunk size, that is going to be splitted
                std::size_t toSplitChunkSize = t_chunk->GetSize();

                // Construct chunk, that is going to be returned
                Chunk* chunk = Chunk::ConstructChunk(
                    t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);

                // Construct splitted chunk
                Chunk* splittedChunk =
                    Chunk::ConstructChunk(reinterpret_cast<std::byte*>(chunk) + t_chunkSize,
                                          t_chunkSize,
                                          toSplitChunkSize - t_chunkSize,
                                          0,
                                          1);

                // Update previous size field for next chunk, after
                // splitted chunk
                Chunk::GetNextChunk(splittedChunk)->SetPrevSize(toSplitChunkSize - t_chunkSize);

                // Insert splitted part into free list
                freedChunks.InsertChunk(splittedChunk);
                return chunk;
            }
        }
    }

    void Arena::DeallocateChunk(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();

        // Delete chunk from active chunks
        // If erase returns 0, it means, that we haven't deleted
        // any chunks from chunks in use. This can mean, that chunk
        // already was deleted (aka DoubleFree occurred), or some other
        // kind of memory corruption occurred (for example we tried to
        // free invalid chunk). Always abort program, because
        // we don't have any performance impact.
        if (!chunksInUse.erase(t_chunk)) {
            utils::ErrorAbort("Arena::DeallocateChunk(): Double free or corruption detected!\n");
        }

        // Update currently used space variable
        m_currentlyAllocatedSpace -= t_chunk->GetSize();

        // Null out memory that belongs to current chunk in secure build
        // #if MPP_SECURE == 1
        //         std::memset(Chunk::GetUserDataPtr(t_chunk), MemoryManager::g_FILL_CHAR,
        //         t_chunk->GetSize() - sizeof(Chunk::ChunkHeader));
        // #endif

        // try to merge deallocated chunk forward and backwards
        Chunk* newChunk = MergeNeighborsChunks(t_chunk);
        if (newChunk != topChunk) {
            // Update free list
            freedChunks.InsertChunk(newChunk);
        }

#if MPP_STATS == 1
        arenaStats->totalFreed += t_chunk->GetSize();
#endif
        return;
    }

    // Remember to check if topChunk is nullptr
    // if it is, then we must check that chunk
    // is top, and after merging everything, we should update topChunk
    // to point to new chunk
    // TODO: Add more sanity checks for this function
    Chunk* Arena::MergeNeighborsChunks(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();
        /*
        Legend:
            F - freed
            A - allocated
            D - to deallocate
            T - top (can be nullptr)
        */

        /*
        First case:
            1. FDT
            2. ADT
            3. DT
        */
        if (((topChunk == nullptr) &&
             (reinterpret_cast<std::byte*>(t_chunk) + t_chunk->GetSize() == end)) ||
            (Chunk::GetNextChunk(t_chunk) == topChunk)) {
            return MergeWithTop(t_chunk);
        }

        /*
        Second case:
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
            newChunk = MergeTwoSequenceChunks(newChunk, Chunk::GetNextChunk(t_chunk));
        }

        // Merge backwards
        if ((reinterpret_cast<void*>(t_chunk) != begin) &&
            Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            newChunk = MergeTwoSequenceChunks(Chunk::GetPrevChunk(newChunk), newChunk);
        }

        // Magic rule, well to know: chunk->GetPrevSize() == 0 <=> chunk == this->begin
        // Set size of previous chunk
        if (static_cast<void*>(newChunk) != begin) {
            newChunk->SetPrevSize(Chunk::GetPrevChunk(newChunk)->GetSize());
        } else {
            newChunk->SetPrevSize(0);
        }

        // Set other fields
        Chunk::GetNextChunk(newChunk)->SetIsPrevInUse(0);
        Chunk::GetNextChunk(newChunk)->SetPrevSize(newChunk->GetSize());
        newChunk->SetIsPrevInUse(1);
        newChunk->SetIsUsed(0);

        return newChunk;
    }

    Chunk* Arena::MergeWithTop(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();

        Chunk* newChunk{ t_chunk };

        // Merge backwards
        if ((static_cast<void*>(t_chunk) != begin) && Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            newChunk = MergeTwoSequenceChunks(Chunk::GetPrevChunk(t_chunk), t_chunk);
        }

        // If top chunk is null, we need to create new one
        if (topChunk == nullptr) {
            topChunk = newChunk;
            // Check, if top chunk isn't the first chunk in arena:
            if (static_cast<void*>(topChunk) != begin) {
                topChunk->SetPrevSize(Chunk::GetPrevChunk(topChunk)->GetSize());
                // Check, if top chunk is the first chunk in arena:
            } else {
                // ChunkSize is already set by MergeTwoSequenceChunks function
                topChunk->SetPrevSize(0);
            }
            topChunk->SetIsPrevInUse(1);
            topChunk->SetIsUsed(1);
            return topChunk;
            // Merging with topChunk if it isn't nullptr
            // Merge forward
        } else {
            topChunk = MergeTwoSequenceChunks(newChunk, topChunk);
            topChunk->SetIsPrevInUse(1);
            topChunk->SetIsUsed(1);
            return topChunk;
        }
    }

    // Note that MergeTwoSequenceChunks doesn't check order of the
    // chunks. Also it doesn't update any flags, and/or any chunk fields
    // excluding chunk size
    Chunk* Arena::MergeTwoSequenceChunks(Chunk* t_chunk1, Chunk* t_chunk2)
    {
        PROFILE_FUNCTION();

        Chunk* chunk = Chunk::ConstructChunk(
            t_chunk1, t_chunk1->GetPrevSize(), t_chunk1->GetSize() + t_chunk2->GetSize(), 0, 0);
        return chunk;
    }

    Chunk* Arena::GetInUseChunkByPtr(void* t_ptr)
    {
        PROFILE_FUNCTION();

        // Try to find InUse chunk by ptr in some location
        // inside this chunk
        auto foundChunkIt = utils::LowerBound(
            chunksInUse.begin(), chunksInUse.end(), t_ptr, [](Chunk* t_ch, void* t_ptr) -> bool {
                return (t_ptr >= reinterpret_cast<void*>(t_ch));
            });
        if (foundChunkIt != chunksInUse.end() && *foundChunkIt == t_ptr) {
            return *foundChunkIt;
        }
        return *(--foundChunkIt);
    }

    std::size_t Arena::GetUsedSpace()
    {
        return m_currentlyAllocatedSpace;
    }

    void Arena::SetUsedSpace(std::size_t t_newSize)
    {
        m_currentlyAllocatedSpace = t_newSize;
    }

#if MPP_STATS == 1
    std::ostream& Arena::DumpArena(std::ostream& t_out,
                                   Arena* t_arena,
                                   bool t_dumpFreedChunks,
                                   bool t_dumpInUseChunks)
    {
        PROFILE_FUNCTION();

        t_out << "-------------- Arena: " << reinterpret_cast<void*>(t_arena) << " --------------"
              << std::endl;

        t_out << "MPP - Total arena size           : "
              << utils::Statistics::FormattedSize(t_arena->size) << std::endl;
        t_out << "MPP - Currently Allocated Space  : "
              << utils::Statistics::FormattedSize(t_arena->m_currentlyAllocatedSpace) << std::endl;
        t_out << "MPP - Amount of free memory      : "
              << utils::Statistics::FormattedSize(t_arena->size -
                                                  t_arena->m_currentlyAllocatedSpace)
              << " (" << std::fixed << std::setprecision(4)
              << (t_arena->size - t_arena->m_currentlyAllocatedSpace) / float(t_arena->size) * 100
              << "% of total arena size)" << std::endl;
        t_out << "MPP - Amount of allocated memory : "
              << utils::Statistics::FormattedSize(t_arena->m_currentlyAllocatedSpace) << " ("
              << std::fixed << std::setprecision(4)
              << t_arena->m_currentlyAllocatedSpace / float(t_arena->size) * 100
              << "% of total arena size)" << std::endl;
        t_out << "MPP - Allocated memory == 0      : ";
        if (t_arena->m_currentlyAllocatedSpace == 0) {
#if MPP_COLOUR == 1
            t_out << col::GREEN << "true" << col::RESET << std::endl;
#else
            t_out << "true" << std::endl;
#endif
        } else {
#if MPP_COLOUR == 1
            t_out << col::RED << "false" << col::RESET << std::endl;
#else
            t_out << "false" << std::endl;
#endif
        }
        t_out << "MPP - Memory used for metadata   : "
              << utils::Statistics::FormattedSize(t_arena->chunksInUse.size() *
                                                  sizeof(Chunk::ChunkHeader_t))
              << " (";
        if (t_arena->m_currentlyAllocatedSpace == 0) {
            t_out << "0% of currently allocated space)" << std::endl;
        } else {
            t_out << std::fixed << std::setprecision(4)
                  << (t_arena->chunksInUse.size() * sizeof(Chunk::ChunkHeader_t)) /
                         float(t_arena->m_currentlyAllocatedSpace) * 100
                  << "% of currently allocated space)" << std::endl;
        }

        t_out << "MPP - TopChunk                   : ";
        if (t_arena->topChunk) {
            Chunk::DumpChunk(t_out, t_arena->topChunk);
        } else {
            t_out << "nullptr";
        }
        t_out << std::endl;

        t_out << "MPP - Arena begin pointer        : " << static_cast<void*>(t_arena->begin)
              << std::endl;
        t_out << "MPP - Arena end pointer          : " << static_cast<void*>(t_arena->end)
              << std::endl;

        t_out << "MPP - Freed chunks nodes (" << t_arena->freedChunks.GetFreedChunksSize() << ")"
              << std::endl;
        int32_t idx1 = 0;
        std::function<void(std::ostream&, Node*)> Iterate = [&](std::ostream& out, Node* node) {
            if (!node) {
                return;
            }

            Iterate(out, node->rightChild);
            out << "\t" << idx1 << ". " << node << std::endl;
            idx1++;
            Iterate(out, node->leftChild);
        };
        if (t_dumpFreedChunks == true) {
            Iterate(std::cout, t_arena->freedChunks.GetRootNode());
        }

        t_out << "MPP - Chunks in use (" << t_arena->chunksInUse.size() << ")" << std::endl;
        int32_t idx2 = 0;
        if (t_dumpInUseChunks == true) {
            for (auto* ch : t_arena->chunksInUse) {
                t_out << "\t" << idx2 << ". ";
                Chunk::DumpChunk(t_out, ch) << std::endl;
                idx2++;
            }
        }
        return t_out;
    }
#endif
}