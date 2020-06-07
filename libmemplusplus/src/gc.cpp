#include "mpplib/gc.hpp"

namespace mpp {
    std::vector<GcPtr*> GC::s_activeGcPtrs;
    std::size_t s_garbageSize = 0;
    std::size_t s_dataSize = 0;

    void GC::AddInfoToObjectsGraph(GcPtr* t_gcPtr, std::unique_ptr<GcGraph>& t_objectsGraph)
    {
        Chunk* gcPtrObjectChunk = MemoryManager::GetInUseChunkByPtr(t_gcPtr->GetVoid());
        Chunk* gcPtrLocationChunk = MemoryManager::GetInUseChunkByPtr(reinterpret_cast<void*>(t_gcPtr));

        if (gcPtrLocationChunk != nullptr)
        {
            //Check that "to" vertex is already exist
            Vertex* to = t_objectsGraph->FindVertex(gcPtrObjectChunk);
            if (to != nullptr)
            {
                to->AddGcPtr(t_gcPtr);           
            } else {
                to = new Vertex(gcPtrObjectChunk);
                to->AddGcPtr(t_gcPtr); 
            }
            //Check that "from" vertex is already exist
            Vertex* from = t_objectsGraph->FindVertex(gcPtrLocationChunk);
            if (from == nullptr)
                from = new Vertex(gcPtrLocationChunk);
            t_objectsGraph->AddEdge(from, to);    
        } else {
            Vertex* vertex = t_objectsGraph->FindVertex(gcPtrObjectChunk);
            if (vertex != nullptr)
            {
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
        for (auto gcPtr : s_activeGcPtrs)
        {
            AddInfoToObjectsGraph(gcPtr, objectsGraph);
        }

        std::unique_ptr<Heuristics> heuristics = std::make_unique<Heuristics>(objectsGraph);
        auto layoutedData = heuristics->Layout();

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