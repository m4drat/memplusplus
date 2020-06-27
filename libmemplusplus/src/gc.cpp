#include "mpplib/gc.hpp"

namespace mpp {
    std::vector<GcPtr*> GC::s_activeGcPtrs;
    std::size_t GC::s_garbageSize = 0;
    std::size_t GC::s_dataSize = 0;

    void GC::AddInfoToObjectsGraph(GcPtr* t_gcPtr,
                                   std::unique_ptr<GcGraph>& t_objectsGraph)
    {
        Chunk* gcPtrObjectChunk = MemoryManager::GetInUseChunkByPtr(t_gcPtr->GetVoid());
        Chunk* gcPtrLocationChunk =
          MemoryManager::GetInUseChunkByPtr(reinterpret_cast<void*>(t_gcPtr));

        if (gcPtrLocationChunk != nullptr) {
            // Check that "to" vertex is already exist
            Vertex* to = t_objectsGraph->FindVertex(gcPtrObjectChunk);
            if (to != nullptr) {
                to->AddGcPtr(t_gcPtr);
            } else {
                to = new Vertex(gcPtrObjectChunk);
                to->AddGcPtr(t_gcPtr);
            }
            // Check that "from" vertex is already exist
            Vertex* from = t_objectsGraph->FindVertex(gcPtrLocationChunk);
            if (from == nullptr)
                from = new Vertex(gcPtrLocationChunk);
            t_objectsGraph->AddEdge(from, to);
        } else {
            Vertex* vertex = t_objectsGraph->FindVertex(gcPtrObjectChunk);
            if (vertex != nullptr) {
                vertex->AddGcPtr(t_gcPtr);
            } else {
                vertex = new Vertex(gcPtrObjectChunk);
                vertex->AddGcPtr(t_gcPtr);
                t_objectsGraph->AddVertex(vertex);
            }
        }
    }

    bool GC::Collect()
    {
        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();

        // Construct chunks graph
        for (auto gcPtr : s_activeGcPtrs) {
            AddInfoToObjectsGraph(gcPtr, objectsGraph);
        }

        std::unique_ptr<Heuristics> heuristics =
          std::make_unique<Heuristics>(objectsGraph.get());
        auto layoutedData = heuristics->Layout();

        std::size_t godArenaSize = MemoryAllocator::Align(
          (layoutedData.second < g_DEFAULT_ARENA_SIZE) ? g_DEFAULT_ARENA_SIZE
                                                       : layoutedData.second,
          g_PAGE_SIZE);
        Arena* godArena = MemoryAllocator::CreateArena(godArenaSize);

        void* currPtr{ godArena->begin };
        Chunk* currChunk{ nullptr };
        std::size_t prevSize{ 0 };
        std::size_t currSize{ 0 };
        for (auto vertex : layoutedData.first.get()) {
            currSize = vertex->GetCorrespondingChunk()->GetSize();
            // void* memcpy(void* dest, const void* src, std::size_t count);
            std::memcpy(currPtr,
                        reinterpret_cast<void*>(vertex->GetCorrespondingChunk()),
                        currSize);
            currChunk = reinterpret_cast<Chunk*>(currPtr);
            currChunk->SetPrevSize(prevSize);
            currChunk->SetIsUsed(1);
            currChunk->SetIsPrevInUse(1);
            godArena->chunksInUse.insert(currChunk);

            // std::cout << "Arena dump: " << std::endl;
            // for (auto ch : godArena->chunksInUse)
            //     std::cout << ch << std::endl;
            // std::cout << "Arena dump End." << std::endl;

            for (auto gcPtr : vertex->GetPointingToGcPtrs()) {
                gcPtr->UpdatePtr(reinterpret_cast<void*>(
                  reinterpret_cast<std::size_t>(currPtr) +
                  (reinterpret_cast<std::size_t>(gcPtr->GetVoid()) -
                   reinterpret_cast<std::size_t>(vertex->GetCorrespondingChunk()))));
            }

            prevSize = currSize;
            currPtr =
              reinterpret_cast<void*>(reinterpret_cast<size_t>(currPtr) + currSize);
        }
        if (godArenaSize - layoutedData.second == 0) {
            godArena->topChunk = nullptr;
        } else {
            Chunk* topChunk = Chunk::ConstructChunk(
              currPtr, prevSize, godArenaSize - layoutedData.second, 1, 1);
            godArena->SetUsedSpace(layoutedData.second);
            godArena->topChunk = topChunk;
        }

        for (auto arena : s_ArenaList) {
            // TODO: Deallocate everything!!!!
            if (arena != godArena)
                delete arena;
        }
        s_ArenaList = { godArena };

        return true;
        // 1.
        // Divide graph into subgraps (by connected components)
        // for each component find structures, rearranges them
        // unite all of the components ->
        // Heuruistics returns pair<neededSpace, vector<Vertex*>>
        // 2.
        // iterate through arenas, try to find with enough space
        // reallocate chunks + update pointers
        // Delete unused arenas (including chunkTreap, etc)
        // reset GC state
    }
}