#include "mpplib/gc.hpp"

namespace mpp {
#if MPP_DEBUG == 1
    uint32_t GC::m_currentCycle;
#endif

    GC::GC()
    {
#if MPP_DEBUG == 1
        m_currentCycle = 1;
#endif
#if MPP_STATS == 1
        m_gcStats = std::make_unique<utils::Statistics::GcStats>();
#endif
    }

    bool GC::Collect()
    {
#if MPP_STATS == 1
        utils::profile::Timer timer("GC::Collect()");
        timer.TimerStart();
#endif
        PROFILE_FUNCTION();
        /*
        1.
            1.1 Divide graph into subgraphs (by connected components)
            1.2 for each component find structures, rearranges them
                unite all of the components
            1.3 Heuristics returns pair<neededSpace, vector<Vertex*>>
        2.
            2.1 iterate through all arenas
            2.2 reallocate chunks + update pointers
            2.3 Delete unused arenas (including chunkTreap, etc)
            2.4 reset GC state
        */
        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();

        // Construct chunks graph
        for (auto* gcPtr : s_activeGcPtrs) {
            objectsGraph->AddObjectInfo(gcPtr);
        }

#if MPP_DEBUG == 1
        if (utils::Options::GetMppDumpObjectsGraph()) {
            std::ofstream objectsDot("objects_cycle" + std::to_string(m_currentCycle) + ".dot");
            objectsGraph->GenerateGraphvizLayout(objectsDot) << std::endl;
            objectsDot.close();
            m_currentCycle++;
        }
#endif

        // Create heuristics object
        std::unique_ptr<Heuristics> heuristics = std::make_unique<Heuristics>();

        // Layout heap in the most efficient way
        auto layoutedData = heuristics->Layout(objectsGraph);

        // Create arena with enough size to fit all objects
        std::size_t godArenaSize = MemoryAllocator::Align(
            (layoutedData.second < g_DEFAULT_ARENA_SIZE) ? g_DEFAULT_ARENA_SIZE
                                                         : layoutedData.second,
            g_PAGE_SIZE);
        Arena* godArena = MemoryAllocator::CreateArena(godArenaSize);

#if MPP_STATS == 1
        m_gcStats->activeObjectsTotalSize = layoutedData.second;
        godArena->m_arenaStats->gcCreatedArena = true;
#endif

        void* currPtr{ godArena->begin };
        Chunk* currChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto vertex : layoutedData.first.get()) {
            // Extract size of chunk
            currSize = vertex->GetCorrespondingChunk()->GetSize();

#if MPP_STATS == 1
            godArena->m_arenaStats->totalAllocated += currSize;
#endif

            // Copy chunk data to new location
            std::memcpy(
                currPtr, reinterpret_cast<void*>(vertex->GetCorrespondingChunk()), currSize);

            // Update required fields
            currChunk = reinterpret_cast<Chunk*>(currPtr);
            currChunk->SetPrevSize(prevSize);
            currChunk->SetIsUsed(1);
            currChunk->SetIsPrevInUse(1);
            godArena->chunksInUse.insert(currChunk);

            // Update GcPtr
            for (auto gcPtr : vertex->GetPointingToGcPtrs()) {
                gcPtr->UpdatePtr(reinterpret_cast<void*>(
                    reinterpret_cast<std::size_t>(currPtr) +
                    (reinterpret_cast<std::size_t>(gcPtr->GetVoid()) -
                     reinterpret_cast<std::size_t>(vertex->GetCorrespondingChunk()))));
            }

            prevSize = currSize;
            currPtr = reinterpret_cast<void*>(reinterpret_cast<std::size_t>(currPtr) + currSize);
        }

        // If we have used all space in the arena
        if (godArenaSize - layoutedData.second == 0) {
            godArena->topChunk = nullptr;
            // We still have some space in top chunk
        } else {
            Chunk* topChunk =
                Chunk::ConstructChunk(currPtr, prevSize, godArenaSize - layoutedData.second, 1, 1);
            godArena->SetUsedSpace(layoutedData.second);
            godArena->topChunk = topChunk;
        }

        // Delete all arenas
        auto it = s_arenaList.begin();
        while (it != s_arenaList.end()) {
            if (*it != godArena) {
#if MPP_STATS == 1
                m_gcStats->memoryCleaned += (*it)->FreeMemoryInsideChunkTreap();
#endif
                delete *it;
                *it = nullptr;
                it = s_arenaList.erase(it);
            } else {
                ++it;
            }
        }

#if MPP_STATS == 1
        timer.TimerEnd();
        m_gcStats->timeWasted = timer.GetElapsed<std::chrono::milliseconds>();
        utils::Statistics::GetInstance().AddGcCycleStats(std::move(m_gcStats));
        m_gcStats = std::make_unique<utils::Statistics::GcStats>();
#endif

        return true;
    }
}