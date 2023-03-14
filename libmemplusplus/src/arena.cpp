#include "mpplib/arena.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/macros.hpp"

#include <functional>

namespace mpp {
    Arena::Arena(std::size_t t_size, std::byte* t_begin)
        : m_size{ t_size }
        , m_topChunk{ Chunk::ConstructChunk(t_begin, 0, t_size, 1, 1) }
        , m_Begin{ t_begin }
        , m_End{ t_begin + t_size }
    {
        PROFILE_FUNCTION();
#if MPP_STATS == 1
        m_arenaStats = std::make_shared<utils::Statistics::ArenaStats>();
        utils::Statistics::GetInstance().AddArenaStats(m_arenaStats);
        m_arenaStats->totalAllocated = 0;
        m_arenaStats->totalFreed = 0;
        m_arenaStats->biggestAllocation = 0;
        m_arenaStats->smallestAllocation = std::numeric_limits<std::size_t>::max();
        m_arenaStats->fullArenaSize = t_size;
        m_arenaStats->bigArena = false;
        m_arenaStats->gcCreatedArena = false;
#endif
    }

    Arena::~Arena()
    {
        PROFILE_FUNCTION();

        MemoryManager::SysDealloc(this->m_Begin, m_size);
    }

    std::set<Chunk*> Arena::BuildChunksInUse()
    {
        std::set<Chunk*> chunksInUse;

        for (Chunk& chunk : *this) {
            if (chunk.IsUsed() && (&chunk != m_topChunk)) {
                chunksInUse.insert(&chunk);
            }
        }

        return chunksInUse;
    }

    std::size_t Arena::FreeMemoryInsideChunkTreap() const
    {
        return m_freedChunks.TotalFreeMemory();
    }

    Chunk* Arena::GetFirstGreaterOrEqualToChunk(std::size_t t_desiredChunkSize) const
    {
        PROFILE_FUNCTION();
        // Find suitable chunk in treap of freed chunks
        return m_freedChunks.FirstGreaterOrEqualTo(t_desiredChunkSize);
    }

    Chunk* Arena::AllocateFromTopChunk(std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // We have enough space in top chunk, so in this case
        // we just need to split it in smaller chunks
        Chunk* chunk = SplitTopChunk(t_chunkSize);

#if MPP_STATS == 1
        m_arenaStats->IncreaseTotalAllocated(t_chunkSize);
        m_arenaStats->UpdateBiggestAllocation(chunk->GetSize());
        m_arenaStats->UpdateSmallestAllocation(chunk->GetSize());
#endif

        // update current allocated space
        m_currentlyAllocatedSpace += t_chunkSize;
        return chunk;
    }

    Chunk* Arena::SplitTopChunk(std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // Size of requested chunk is equal to size of top chunk
        if (t_chunkSize == m_topChunk->GetSize()) {
            // Construct new chunk from all memory, that belongs to top chunk
            Chunk* chunk =
                Chunk::ConstructChunk(m_topChunk, m_topChunk->GetPrevSize(), t_chunkSize, 1, 1);

            // make topChunk nullptr, to let allocator know, that we dont
            // have any more top-space in current arena. This field can be
            // updated later in deallocate, if we managed to merge everything
            // on the right side
            m_topChunk = nullptr;
            return chunk;
        }

        // Splitting top chunk in smaller chunks
        std::size_t newTopChunkSize = m_topChunk->GetSize() - t_chunkSize;

        // Constructing new chunk from splitted memory
        Chunk* chunk =
            Chunk::ConstructChunk(m_topChunk, m_topChunk->GetPrevSize(), t_chunkSize, 1, 1);

        // Update top chunk
        m_topChunk = Chunk::ConstructChunk(reinterpret_cast<std::byte*>(m_topChunk) + t_chunkSize,
                                           t_chunkSize,
                                           newTopChunkSize,
                                           1,
                                           1);
        MPP_POISON_USER_DATA_INSIDE_CHUNK(m_topChunk);

        return chunk;
    }

    Chunk* Arena::AllocateFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();
        // Extract chunk from free list, and split it if needed
        Chunk* chunk = SplitChunkFromFreeList(t_chunk, t_chunkSize);

#if MPP_STATS == 1
        m_arenaStats->IncreaseTotalAllocated(t_chunkSize);
#endif

        // Update used space variable
        m_currentlyAllocatedSpace += t_chunkSize;

        return chunk;
    }

    Chunk* Arena::SplitChunkFromFreeList(Chunk* t_chunk, std::size_t t_chunkSize)
    {
        PROFILE_FUNCTION();

        // Chunk to return
        Chunk* chunk = nullptr;
        // Size of chunk extracted from free list
        std::size_t toSplitChunkSize = t_chunk->GetSize();

        // Delete current chunk from free list
        m_freedChunks.RemoveChunk(t_chunk);

        // Free-list chunk size is equal to requested size (we don't need to split)
        if (t_chunk->GetSize() == t_chunkSize) {
            // Chunk to split is the first chunk inside arena. Memory layout: [t_chunk][....]
            if (static_cast<void*>(t_chunk) == m_Begin) {
                // Set prevInUse to 1, because we don't want to merge it to the
                // left (cause we dont have anything on the left)
                chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);
            } else {
                chunk = Chunk::ConstructChunk(
                    t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);
            }
            Chunk::GetNextChunk(chunk)->SetIsPrevInUse(1);
            Chunk::GetNextChunk(chunk)->SetPrevSize(t_chunkSize);
        } else {
            // Free-list chunk size is NOT equal to requested size (we have need to split it)
            if (static_cast<void*>(t_chunk) == m_Begin) {
                // Chunk to split is the first chunk inside arena. Memory layout: [t_chunk][....]
                // Split chunk from the beginning of the arena
                chunk = Chunk::ConstructChunk(t_chunk, 0, t_chunkSize, 1, 1);
            } else {
                chunk = Chunk::ConstructChunk(
                    t_chunk, Chunk::GetPrevChunk(t_chunk)->GetSize(), t_chunkSize, 1, 1);
            }
            // Update fields of the remaining chunk
            Chunk* splittedChunk =
                Chunk::ConstructChunk(reinterpret_cast<std::byte*>(chunk) + t_chunkSize,
                                      t_chunkSize,
                                      toSplitChunkSize - t_chunkSize,
                                      0,
                                      1);
            // Update previous size for the next chunk after the splitted one.
            // Memory layout: [user-returned][splitted part][next chunk after splitted]
            Chunk::GetNextChunk(splittedChunk)->SetPrevSize(toSplitChunkSize - t_chunkSize);

            // Keep track of remaining chunk by placing it into free list
            m_freedChunks.InsertChunk(splittedChunk);
            MPP_POISON_USER_DATA_INSIDE_CHUNK(splittedChunk);
        }
        return chunk;
    }

    void Arena::DeallocateChunk(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();

        // Update currently used space variable
        m_currentlyAllocatedSpace -= t_chunk->GetSize();

        MPP_SECURE_WIPE_CHUNK(t_chunk);

        // try to merge deallocated chunk forward and backwards
        Chunk* newChunk = MergeNeighborsChunks(t_chunk);
        if (newChunk != m_topChunk) {
            // Update free list
            m_freedChunks.InsertChunk(newChunk);
        }

#if MPP_STATS == 1
        m_arenaStats->IncreaseTotalFreed(t_chunk->GetSize());
#endif
    }

    // Remember to check if topChunk is nullptr. If it is then we must check that the chunk is top
    // chunk, and after merging everything, we should update topChunk to point to the new chunk.
    // TODO: Add more sanity checks to this function
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
        if (((m_topChunk == nullptr) &&
             (reinterpret_cast<std::byte*>(t_chunk) + t_chunk->GetSize() == m_End)) ||
            (Chunk::GetNextChunk(t_chunk) == m_topChunk)) {
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
            m_freedChunks.RemoveChunk(Chunk::GetNextChunk(t_chunk));
            newChunk = MergeTwoSequenceChunks(newChunk, Chunk::GetNextChunk(t_chunk));
        }

        // Merge backwards
        if ((reinterpret_cast<void*>(t_chunk) != m_Begin) &&
            Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            m_freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            newChunk = MergeTwoSequenceChunks(Chunk::GetPrevChunk(newChunk), newChunk);
        }

        // Magic rule, well to know: chunk->GetPrevSize() == 0 <=> chunk == this->begin
        // Set size of the previous chunk
        if (static_cast<void*>(newChunk) != m_Begin) {
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
        if ((static_cast<void*>(t_chunk) != m_Begin) &&
            Chunk::GetPrevChunk(t_chunk)->IsUsed() == 0) {
            m_freedChunks.RemoveChunk(Chunk::GetPrevChunk(t_chunk));
            newChunk = MergeTwoSequenceChunks(Chunk::GetPrevChunk(t_chunk), t_chunk);
        }

        // If top chunk is null, we need to create a new one
        if (m_topChunk == nullptr) {
            m_topChunk = newChunk;
            // Check, if top chunk isn't the first chunk in the arena
            if (static_cast<void*>(m_topChunk) != m_Begin) {
                m_topChunk->SetPrevSize(Chunk::GetPrevChunk(m_topChunk)->GetSize());
                // Check, if top chunk is the first chunk in the arena:
            } else {
                // ChunkSize is already set by MergeTwoSequenceChunks function
                m_topChunk->SetPrevSize(0);
            }
            m_topChunk->SetIsPrevInUse(1);
            m_topChunk->SetIsUsed(1);
            return m_topChunk;
        }
        // Merging with the topChunk if it isn't nullptr (merge forward)
        m_topChunk = MergeTwoSequenceChunks(newChunk, m_topChunk);
        m_topChunk->SetIsPrevInUse(1);
        m_topChunk->SetIsUsed(1);
        return m_topChunk;
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

    std::size_t Arena::GetUsedSpace() const
    {
        return m_currentlyAllocatedSpace;
    }

    void Arena::SetUsedSpace(std::size_t t_newSize)
    {
        m_currentlyAllocatedSpace = t_newSize;
    }

#if MPP_STATS == 1
    std::ostream& Arena::DumpArena(std::ostream& t_out,
                                   std::unique_ptr<Arena>& t_arena,
                                   bool t_dumpFreedChunks,
                                   bool t_dumpInUseChunks)
    {
        PROFILE_FUNCTION();

        const std::set<Chunk*> chunksInUse = t_arena->BuildChunksInUse();

        t_out << "-------------- Arena: " << reinterpret_cast<void*>(t_arena.get())
              << " --------------" << std::endl;

        t_out << "MPP - Total arena size           : "
              << utils::Statistics::FormattedSize(t_arena->m_size) << std::endl;
        t_out << "MPP - Currently Allocated Space  : "
              << utils::Statistics::FormattedSize(t_arena->m_currentlyAllocatedSpace) << std::endl;
        t_out << "MPP - Amount of free memory      : "
              << utils::Statistics::FormattedSize(t_arena->m_size -
                                                  t_arena->m_currentlyAllocatedSpace)
              << " (" << std::fixed << std::setprecision(4)
              << (float)(t_arena->m_size - t_arena->m_currentlyAllocatedSpace) /
                     float(t_arena->m_size) * 100.0f
              << "% of total arena size)" << std::endl;
        t_out << "MPP - Amount of allocated memory : "
              << utils::Statistics::FormattedSize(t_arena->m_currentlyAllocatedSpace) << " ("
              << std::fixed << std::setprecision(4)
              << (float)t_arena->m_currentlyAllocatedSpace / float(t_arena->m_size) * 100.0f
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
              << utils::Statistics::FormattedSize(chunksInUse.size() * sizeof(Chunk::ChunkHeader_t))
              << " (";
        if (t_arena->m_currentlyAllocatedSpace == 0) {
            t_out << "0% of currently allocated space)" << std::endl;
        } else {
            t_out << std::fixed << std::setprecision(4)
                  << (float)(chunksInUse.size() * sizeof(Chunk::ChunkHeader_t)) /
                         float(t_arena->m_currentlyAllocatedSpace) * 100.0f
                  << "% of currently allocated space)" << std::endl;
        }

        t_out << "MPP - TopChunk                   : ";
        if (t_arena->m_topChunk) {
            Chunk::DumpChunk(t_out, t_arena->m_topChunk);
        } else {
            t_out << "nullptr";
        }
        t_out << std::endl;

        t_out << "MPP - Arena begin pointer        : " << static_cast<void*>(t_arena->m_Begin)
              << std::endl;
        t_out << "MPP - Arena end pointer          : " << static_cast<void*>(t_arena->m_End)
              << std::endl;

        t_out << "MPP - Freed chunks nodes (" << t_arena->m_freedChunks.TotalFreeChunks() << ")"
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
        if (t_dumpFreedChunks) {
            Iterate(t_out, t_arena->m_freedChunks.GetRootNode());
        }

        t_out << "MPP - Chunks in use (" << chunksInUse.size() << ")" << std::endl;
        int32_t idx2 = 0;
        if (t_dumpInUseChunks) {
            for (auto* chunk : chunksInUse) {
                t_out << "\t" << idx2 << ". ";
                Chunk::DumpChunk(t_out, chunk) << std::endl;
                idx2++;
            }
        }
        return t_out;
    }
#endif
}