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
        for (auto* gcPtr : m_activeGcPtrs) {
            objectsGraph->AddObjectInfo(gcPtr);
        }

#if MPP_DEBUG == 1
        if (utils::EnvOptions::Get().GetMppDumpObjectsGraph()) {
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

        // Create a new rena with enough memory to fit all objects
        std::size_t godArenaSize = (layoutedData.layoutedSize < MM::g_DEFAULT_ARENA_SIZE)
                                       ? MM::g_DEFAULT_ARENA_SIZE
                                       : layoutedData.layoutedSize;

        // If newly created arena is really small (we have less than 20% of free space)
        // Enlarge it by specified expandFactor
        if (static_cast<float>(godArenaSize - layoutedData.layoutedSize) / godArenaSize <
            m_newAllocExtendThreshold) {
            godArenaSize *= m_newAllocExpandFactor;
        }

        Arena* godArena = MM::CreateArena(MM::Align(godArenaSize, MM::g_PAGE_SIZE));

#if MPP_STATS == 1
        m_gcStats->activeObjectsTotalSize = layoutedData.layoutedSize;
        godArena->m_arenaStats->gcCreatedArena = true;
#endif

        void* newChunkLocation{ godArena->begin };
        Chunk* newChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto vertex : layoutedData.vertices) {
            // Extract size of chunk
            currSize = vertex->GetCorrespondingChunk()->GetSize();

#if MPP_STATS == 1
            godArena->m_arenaStats->totalAllocated += currSize;
#endif

            // Copy chunk data to new location
            std::memcpy(newChunkLocation,
                        reinterpret_cast<void*>(vertex->GetCorrespondingChunk()),
                        currSize);

            // Update required fields
            newChunk = reinterpret_cast<Chunk*>(newChunkLocation);
            newChunk->SetPrevSize(prevSize);
            newChunk->SetIsUsed(1);
            newChunk->SetIsPrevInUse(1);
            godArena->chunksInUse.insert(newChunk);

            // Update GcPtr
            for (auto gcPtr : vertex->GetPointingToGcPtrs()) {
                std::size_t updatedPtr =
                    reinterpret_cast<std::size_t>(newChunkLocation) +
                    (reinterpret_cast<std::size_t>(gcPtr->GetVoid()) -
                     reinterpret_cast<std::size_t>(vertex->GetCorrespondingChunk()));
                gcPtr->UpdatePtr(reinterpret_cast<void*>(updatedPtr));
            }

            prevSize = currSize;
            newChunkLocation =
                reinterpret_cast<void*>(reinterpret_cast<std::size_t>(newChunkLocation) + currSize);
        }

        // If we have used all space in the arena
        if (godArenaSize - layoutedData.layoutedSize == 0) {
            godArena->topChunk = nullptr;
            // We still have some space in top chunk
        } else {
            Chunk* topChunk = Chunk::ConstructChunk(
                newChunkLocation, prevSize, godArenaSize - layoutedData.layoutedSize, 1, 1);
            godArena->SetUsedSpace(layoutedData.layoutedSize);
            godArena->topChunk = topChunk;
        }

        // Delete all arenas except newly created one
        auto it = MM::s_arenaList.begin();
        while (it != MM::s_arenaList.end()) {
            if (*it != godArena) {
#if MPP_STATS == 1
                m_gcStats->memoryCleaned += (*it)->FreeMemoryInsideChunkTreap();
#endif
                delete *it;
                *it = nullptr;
                it = MM::s_arenaList.erase(it);
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