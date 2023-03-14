#include "mpplib/gc.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/macros.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <unordered_map>

namespace mpp {
    GarbageCollector::GarbageCollector(MemoryManager& t_memoryManager)
        : m_totalInvocations(0)
        , m_memoryManager(t_memoryManager)
    {
#if MPP_STATS == 1
        m_gcStats = std::make_unique<utils::Statistics::GcStats>();
#endif
    }

    Chunk* GarbageCollector::FindChunkInUse(void* t_ptr)
    {
        PROFILE_FUNCTION();

        // Find arena by pointer
        auto arenaOpt = m_memoryManager.GetArenaByPtr(t_ptr);
        if (!arenaOpt.has_value())
            return nullptr;

        std::unique_ptr<Arena>& arena = arenaOpt.value().get();

        // Build chunks in use cache if not present
        if (!m_chunksInUseCache.contains(arena.get())) {
            m_chunksInUseCache[arena.get()] = arena->BuildChunksInUse();
        }

        const std::set<Chunk*>& chunksInUse = m_chunksInUseCache[arena.get()];

        // Find a chunk by pointer
        auto foundChunkIt = chunksInUse.lower_bound(reinterpret_cast<Chunk*>(t_ptr));
        if (foundChunkIt != chunksInUse.end() && *foundChunkIt == t_ptr) {
            return *foundChunkIt;
        }
        return (foundChunkIt != chunksInUse.begin()) ? *(--foundChunkIt) : nullptr;
    }

    bool GarbageCollector::Collect()
    {
#if MPP_STATS == 1
        utils::profile::Timer timer("GC::Collect()");
        timer.TimerStart();
#endif
        PROFILE_FUNCTION();

        // Ordered copy of m_activeGcPtrs
        std::set<GcPtr*> orderedActiveGcPtrs = GetOrderedGcPtrs();

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
        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>(*this, m_memoryManager);

        // Construct chunks graph
        for (auto* gcPtr : m_activeGcPtrs) {
            objectsGraph->AddObjectInfo(gcPtr);
        }

#if MPP_DEBUG == 1
        if (utils::EnvOptions::Get().GetMppDumpObjectsGraph() !=
            utils::ObjectsGraphDumpType::DISABLED) {
            std::ofstream objectsDot("objects_cycle" + std::to_string(m_totalInvocations) + ".dot");

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
        }
#endif

        // Create heuristics object
        std::unique_ptr<Heuristics> heuristics =
            std::make_unique<Heuristics>(objectsGraph, orderedActiveGcPtrs);

        // Layout heap in the most efficient way
        Heuristics::LayoutedHeap layoutedData = heuristics->LayoutHeap();

        // Create a new rena with enough memory to fit all objects
        std::size_t godArenaSize = (layoutedData.layoutedSize < MM::g_DEFAULT_ARENA_SIZE)
                                       ? MM::g_DEFAULT_ARENA_SIZE
                                       : layoutedData.layoutedSize;

        // If newly created arena is really small (we have less than 25% of free space)
        // Enlarge it by specified expandFactor
        if (static_cast<double>(godArenaSize - layoutedData.layoutedSize) / (double)godArenaSize <
            m_newAllocExtendThreshold) {
            godArenaSize = (std::size_t)((double)godArenaSize * m_newAllocExpandFactor);
        }
        godArenaSize = MM::Align(godArenaSize, MM::g_PAGE_SIZE);

        auto& godArena = m_memoryManager.CreateArena(godArenaSize);

#if MPP_STATS == 1
        m_gcStats->activeObjectsTotalSize = layoutedData.layoutedSize;
        godArena->GetArenaStats()->gcCreatedArena = true;
#endif

        std::byte* newChunkLocation{ godArena->BeginPtr() };
        Chunk* newChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Map that stores old gcptr location -> new gcptr location
        // Used to be able to update all data pointers inside gcptrs
        std::unordered_map<GcPtr*, std::byte*> gcPtrsToNewLocations;
        gcPtrsToNewLocations.reserve(orderedActiveGcPtrs.size());

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto* vertex : layoutedData.vertices) {
            // We don't care about non-heap gcptrs (it may be a local GcPtr, etc)
            if (!vertex->IsChunk()) {
                continue;
            }

            // Extract size of a chunk
            currSize = vertex->GetLocationAsAChunk()->GetSize();

#if MPP_STATS == 1
            godArena->GetArenaStats()->IncreaseTotalAllocated(currSize);
#endif
            // Update gcPtrsToNewLocations map with new location of a gcptr
            for (auto* gcPtr : vertex->GetAllOutgoingGcPtrs(orderedActiveGcPtrs)) {
                orderedActiveGcPtrs.erase(gcPtr);
                auto* updatedGcPtrLocation = reinterpret_cast<GcPtr*>(
                    newChunkLocation + (reinterpret_cast<std::byte*>(gcPtr) - vertex->GetLoc()));
                orderedActiveGcPtrs.insert(orderedActiveGcPtrs.end(), updatedGcPtrLocation);
                gcPtrsToNewLocations[gcPtr] = reinterpret_cast<std::byte*>(updatedGcPtrLocation);
            }

            // Update GcPtrs
            for (auto* gcPtr : vertex->GetPointingToGcPtrs()) {
                std::byte* newUserDataPtr = newChunkLocation + sizeof(Chunk);

                // Either the GcPtr is going to be copied to another chunk later
                gcPtr->UpdatePtr(newUserDataPtr);

                // Or we already copied it to another chunk and we need to update it again
                if (gcPtrsToNewLocations.find(gcPtr) != gcPtrsToNewLocations.end()) {
                    auto* gcPtrNewLoc = gcPtrsToNewLocations[gcPtr];
                    // Update GcPtr's internal pointer
                    // FIXME: this is an awful way to do it, but it works for now (might break
                    // if shared_gcptr's layout is changed / or another GcPtr inherited pointer
                    // with different layout is added). It even might break because compiler
                    // decides to reorder members of SharedGcPtr between different
                    // instantiations
                    // TODO: Maybe use pointer to member with the dynamic_cast?
                    auto* gcPtrInternalPointer = reinterpret_cast<std::size_t*>(
                        gcPtrNewLoc + offsetof(SharedGcPtr<int>, m_objectPtr));

                    MPP_DEBUG_ASSERT(
                        reinterpret_cast<std::byte*>(gcPtrInternalPointer + sizeof(std::size_t)) <=
                            godArena->EndPtr(),
                        "GcPtr's internal pointer is out of newly created arena's bounds");

                    *gcPtrInternalPointer = reinterpret_cast<std::size_t>(newUserDataPtr);
                }
            }

            // Copy chunk data to the new location
            std::memcpy(newChunkLocation, vertex->GetLoc(), currSize);

            // Update required fields
            newChunk = reinterpret_cast<Chunk*>(newChunkLocation);
            newChunk->SetPrevSize(prevSize);
            newChunk->SetIsUsed(1);
            newChunk->SetIsPrevInUse(1);

            prevSize = currSize;
            newChunkLocation = newChunkLocation + currSize;
        }

        // Update activeGcPtrs after all GcPtrs are updated
        m_activeGcPtrs =
            std::unordered_set<GcPtr*>(orderedActiveGcPtrs.begin(), orderedActiveGcPtrs.end());

        // We always have some free space in the arena, so we have to construct a top chunk
        Chunk* topChunk = Chunk::ConstructChunk(
            newChunkLocation, prevSize, godArenaSize - layoutedData.layoutedSize, 1, 1);
        godArena->SetUsedSpace(layoutedData.layoutedSize);
        godArena->TopChunk() = topChunk;

        auto& arenaList = m_memoryManager.GetArenaList();
        arenaList.erase(std::remove_if(
            arenaList.begin(), arenaList.end(), [&](std::unique_ptr<Arena>& t_arena) {
                if (t_arena.get() == godArena.get())
                    return false;
#if MPP_STATS == 1
                m_gcStats->memoryCleaned += t_arena->FreeMemoryInsideChunkTreap();
#endif
                t_arena.reset();
                return true;
            }));

#if MPP_STATS == 1
        timer.TimerEnd();
        m_gcStats->timeWasted = timer.GetElapsed<std::chrono::milliseconds>();
        utils::Statistics::GetInstance().AddGcCycleStats(std::move(m_gcStats));
        m_gcStats = std::make_unique<utils::Statistics::GcStats>();
#endif

        // GC completed successfully, increase number of successful GCs
        m_totalInvocations++;

        return true;
    }
}