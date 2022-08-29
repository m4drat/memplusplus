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
        if (utils::EnvOptions::Get().GetMppDumpObjectsGraph() !=
            utils::ObjectsGraphDumpType::DISABLED) {
            std::ofstream objectsDot("objects_cycle" + std::to_string(m_currentCycle) + ".dot");

            switch (utils::EnvOptions::Get().GetMppDumpObjectsGraph()) {
                case utils::ObjectsGraphDumpType::SIMPLE:
                    objectsGraph->GenerateGraphvizLayoutSimple(objectsDot) << std::endl;
                    break;
                case utils::ObjectsGraphDumpType::ADVANCED:
                    objectsGraph->GenerateGraphvizLayoutAdvanced(objectsDot) << std::endl;
                    break;
                default:
                    break;
            }

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
        godArenaSize = MM::Align(godArenaSize, MM::g_PAGE_SIZE);

        Arena* godArena = MM::CreateArena(godArenaSize);

#if MPP_STATS == 1
        m_gcStats->activeObjectsTotalSize = layoutedData.layoutedSize;
        godArena->arenaStats->gcCreatedArena = true;
#endif

        std::byte* newChunkLocation{ godArena->begin };
        Chunk* newChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto* vertex : layoutedData.vertices) {
            // We don't care about non-heap gcptrs (it may be a local GcPtr, etc)
            if (!vertex->IsChunk()) {
                continue;
            }

            // Extract size of a chunk
            currSize = vertex->GetLocationAsChunk()->GetSize();

#if MPP_STATS == 1
            godArena->arenaStats->totalAllocated += currSize;
#endif

            // Copy chunk data to new location
            std::memcpy(newChunkLocation, vertex->GetLoc(), currSize);

            // Update required fields
            newChunk = reinterpret_cast<Chunk*>(newChunkLocation);
            newChunk->SetPrevSize(prevSize);
            newChunk->SetIsUsed(1);
            newChunk->SetIsPrevInUse(1);
            godArena->chunksInUse.insert(newChunk);

            // Update GcPtr
            for (auto* gcPtr : vertex->GetPointingToGcPtrs()) {
                std::byte* updatedPtr =
                    newChunkLocation +
                    (reinterpret_cast<std::byte*>(gcPtr->GetVoid()) - vertex->GetLoc());
                gcPtr->UpdatePtr(updatedPtr);
            }

            prevSize = currSize;
            newChunkLocation = newChunkLocation + currSize;
        }

        // We always have some free space in the arena, so we have to construct a top chunk
        Chunk* topChunk = Chunk::ConstructChunk(
            newChunkLocation, prevSize, godArenaSize - layoutedData.layoutedSize, 1, 1);
        godArena->SetUsedSpace(layoutedData.layoutedSize);
        godArena->topChunk = topChunk;

        MM::s_arenaList.erase(
            std::remove_if(MM::s_arenaList.begin(), MM::s_arenaList.end(), [&](Arena* t_arena) {
                if (t_arena == godArena)
                    return false;
#if MPP_STATS == 1
                m_gcStats->memoryCleaned += t_arena->FreeMemoryInsideChunkTreap();
#endif
                delete t_arena;
                t_arena = nullptr;
                return true;
            }));

#if MPP_STATS == 1
        timer.TimerEnd();
        m_gcStats->timeWasted = timer.GetElapsed<std::chrono::milliseconds>();
        utils::Statistics::GetInstance().AddGcCycleStats(std::move(m_gcStats));
        m_gcStats = std::make_unique<utils::Statistics::GcStats>();
#endif

        return true;
    }
}