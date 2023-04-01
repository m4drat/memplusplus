#include "mpplib/gc.hpp"
#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/exception.hpp"
#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/utils.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <sstream>
#include <unordered_map>

namespace mpp {
    GarbageCollector::GarbageCollector(MemoryManager& t_memoryManager)
        : m_totalInvocations(0)
        , m_memoryManager(t_memoryManager)
    {
    }

    void GarbageCollector::DumpCurrentObjectsGraph(utils::ObjectsGraphDumpType t_dumpType,
                                                   const std::string& t_filename)
    {
        m_chunksInUseCache.clear();

        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>(*this, m_memoryManager);

        // Construct chunks graph
        for (auto* gcPtr : m_activeGcPtrs) {
            objectsGraph->AddObjectInfo(gcPtr);
        }

        SaveObjectsGraph(objectsGraph, t_filename, t_dumpType);

        m_chunksInUseCache.clear();
    }

    void GarbageCollector::SaveObjectsGraph(std::unique_ptr<GcGraph>& t_graph,
                                            const std::string& t_filename,
                                            utils::ObjectsGraphDumpType t_dumpType)
    {
        std::ofstream objectsDot(t_filename);

        switch (t_dumpType) {
            case utils::ObjectsGraphDumpType::SIMPLE:
                t_graph->GenerateGraphvizLayoutSimple(objectsDot) << std::endl;
                break;
            case utils::ObjectsGraphDumpType::ADVANCED:
                t_graph->GenerateGraphvizLayoutAdvanced(objectsDot) << std::endl;
                break;
            default:
                throw Exception("Invalid gc-graph dump type specified!");
                break;
        }

        objectsDot.close();
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

    std::unique_ptr<Arena>& GarbageCollector::CreateGodArena(uint64_t t_requestedSize)
    {
        const std::size_t minArenaSize = (t_requestedSize < MM::g_DEFAULT_ARENA_SIZE)
                                             ? MM::g_DEFAULT_ARENA_SIZE
                                             : t_requestedSize;
        std::size_t godArenaSize = minArenaSize;

        // If newly created arena is really small (we have less than 25% of free space)
        // Enlarge it by specified expandFactor
        if (static_cast<double>(godArenaSize - t_requestedSize) / (double)godArenaSize <
            m_newAllocExtendThreshold) {
            godArenaSize = (std::size_t)((double)godArenaSize * m_newAllocExpandFactor);
        }
        godArenaSize = MM::Align(godArenaSize, MM::g_PAGE_SIZE);

        return m_memoryManager.CreateArena(godArenaSize);
    }

    void GarbageCollector::RelocatePointers(std::unique_ptr<Arena>& t_godArena,
                                            Heuristics::LayoutedHeap& t_layoutedData)
    {
        std::byte* newChunkLocation{ t_godArena->BeginPtr() };
        [[maybe_unused]] Chunk* newChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Map that stores old gcptr location -> new gcptr location
        // Used to be able to update all data pointers inside gcptrs
        std::unordered_map<GcPtr*, std::byte*> gcPtrsToNewLocations;
        gcPtrsToNewLocations.reserve(m_orderedActiveGcPtrs.size());

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto* vertex : t_layoutedData.vertices) {
            // We don't care about non-heap gcptrs (it may be a local GcPtr, etc)
            if (!vertex->IsChunk()) {
                continue;
            }

            // Extract size of a chunk
            currSize = vertex->GetLocationAsAChunk()->GetSize();

            // Update gcPtrsToNewLocations map with new location of a gcptr
            for (auto* gcPtr : vertex->GetAllOutgoingGcPtrs(m_orderedActiveGcPtrs)) {
                m_orderedActiveGcPtrs.erase(gcPtr);
                auto* updatedGcPtrLocation = reinterpret_cast<GcPtr*>(
                    newChunkLocation + (reinterpret_cast<std::byte*>(gcPtr) - vertex->GetLoc()));
                m_orderedActiveGcPtrs.insert(m_orderedActiveGcPtrs.end(), updatedGcPtrLocation);
                gcPtrsToNewLocations[gcPtr] = reinterpret_cast<std::byte*>(updatedGcPtrLocation);
            }

            // Update GcPtrs
            for (auto* gcPtr : vertex->GetPointingToGcPtrs()) {
                std::byte* newUserDataPtr = newChunkLocation + sizeof(Chunk);

                // Either the GcPtr is going to be copied to another chunk later
                gcPtr->UpdatePtr(newUserDataPtr);

                // Or we already copied it to another chunk and we need to update it again
                if (gcPtrsToNewLocations.contains(gcPtr)) {
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
                        reinterpret_cast<std::byte*>(gcPtrInternalPointer) + sizeof(void*) <=
                            t_godArena->EndPtr(),
                        "GcPtr's internal pointer is out of newly created arena's bounds");

                    *gcPtrInternalPointer = reinterpret_cast<std::size_t>(newUserDataPtr);
                }
            }

            // Copy chunk data to the new location.
            std::memcpy(newChunkLocation, vertex->GetLoc(), currSize);

            // Construct a chunk at the new location.
            newChunk = Chunk::ConstructChunk(newChunkLocation, prevSize, currSize, 1, 1);

            // @FIXME: This is a hacky solution that kinda works.
            MPP_VALGRIND_DEFINE_CHUNK(newChunk);
            MPP_VALGRIND_MAKE_MEM_DEFINED(newChunk, newChunk->GetSize());
            MPP_VALGRIND_UNDEFINE_CHUNK(vertex->GetLocationAsAChunk());
            MPP_VALGRIND_MAKE_MEM_DEFINED(vertex->GetLocationAsAChunk(),
                                          vertex->GetLocationAsAChunk()->GetSize());

            prevSize = currSize;
            newChunkLocation = newChunkLocation + currSize;
        }

        // We always have some free space in the arena, so we have to construct a top chunk.
        Chunk* topChunk = Chunk::ConstructChunk(
            newChunkLocation, prevSize, t_godArena->GetSize() - t_layoutedData.layoutedSize, 1, 1);
        t_godArena->SetUsedSpace(t_layoutedData.layoutedSize);
        t_godArena->TopChunk() = topChunk;
    }

    bool GarbageCollector::Collect()
    {
        PROFILE_FUNCTION();

        // Ordered copy of m_activeGcPtrs.
        m_orderedActiveGcPtrs = BuildOrderedGcPtrs();

        // Construct objects graph.
        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>(*this, m_memoryManager);
        for (auto* gcPtr : m_activeGcPtrs) {
            objectsGraph->AddObjectInfo(gcPtr);
        }

#if MPP_DEBUG == 1
        if (utils::EnvOptions::Get().GetMppDumpObjectsGraph() !=
            utils::ObjectsGraphDumpType::DISABLED) {
            std::string filename = "objects_cycle" + std::to_string(m_totalInvocations) + ".dot";
            auto dumpMode = utils::EnvOptions::Get().GetMppDumpObjectsGraph();
            SaveObjectsGraph(objectsGraph, filename, dumpMode);
        }
#endif

        // Create heuristics object
        std::unique_ptr<Heuristics> heuristics = std::make_unique<Heuristics>(objectsGraph);

        // Layout heap in the most efficient way
        Heuristics::LayoutedHeap layoutedData = heuristics->LayoutHeap();

        // Create new arena with enough memory to fit all objects.
        auto& godArena = CreateGodArena(layoutedData.layoutedSize);

        // Move all the data to newly-allocated heap space.
        RelocatePointers(godArena, layoutedData);

        // Clear chunksInUse cache and update m_activeGcPtrs after all GcPtrs are updated.
        m_chunksInUseCache.clear();
        m_activeGcPtrs =
            std::unordered_set<GcPtr*>(m_orderedActiveGcPtrs.begin(), m_orderedActiveGcPtrs.end());

        // Clear orderedActiveGcPtrs
        m_orderedActiveGcPtrs.clear();

        // Remove old arenas.
        auto& arenaList = m_memoryManager.GetArenaList();
        arenaList.erase(std::remove_if(arenaList.begin(),
                                       arenaList.end(),
                                       [&godArena = godArena](std::unique_ptr<Arena>& t_arena) {
                                           if (t_arena.get() == godArena.get())
                                               return false;
                                           t_arena.reset();
                                           return true;
                                       }));

        // GC completed successfully, increase number of successful GCs.
        m_totalInvocations++;

        return true;
    }
}