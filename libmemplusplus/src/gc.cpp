#include "mpplib/gc.hpp"

namespace mpp {
    std::vector<GcPtr*> GC::s_activeGcPtrs;
    std::size_t GC::s_garbageSize = 0;
    std::size_t GC::s_dataSize = 0;

    bool GC::Collect()
    {
        /*
        1.
            1.1 Divide graph into subgraps (by connected components)
            1.2 for each component find structures, rearranges them
                unite all of the components
            1.3 Heuruistics returns pair<neededSpace, vector<Vertex*>>
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
        if (utils::Options::GetMppDumpObjectsGraph())
        {
            std::ofstream objectsDot("objects.dot");
            objectsGraph->GenerateGraphvizLayout(objectsDot) << std::endl;
            objectsDot.close();
        }
#endif

        // Create heuristics object
        std::unique_ptr<Heuristics> heuristics = std::make_unique<Heuristics>();

        // Layout heap in the most efficient way
        auto layoutedData = heuristics->Layout(objectsGraph);

        // Create arena with enough size to fit all objects
        std::size_t godArenaSize = MemoryAllocator::Align(
          (layoutedData.second < g_DEFAULT_ARENA_SIZE) ? g_DEFAULT_ARENA_SIZE : layoutedData.second,
          g_PAGE_SIZE);
        Arena* godArena = MemoryAllocator::CreateArena(godArenaSize);

        void* currPtr{ godArena->begin };
        Chunk* currChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };

        // Iterate through all vertices (aka chunks) in layouted vector
        for (auto vertex : layoutedData.first.get()) {
            // Extract size of chunk
            currSize = vertex->GetCorrespondingChunk()->GetSize();

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
            currPtr = reinterpret_cast<void*>(reinterpret_cast<size_t>(currPtr) + currSize);
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
        auto it = s_ArenaList.begin();
        while (it != s_ArenaList.end()) {
            if (*it != godArena) {
                delete *it;
                *it = nullptr;
                it = s_ArenaList.erase(it);
            } else {
                ++it;
            }
        }

        return true;
    }
}