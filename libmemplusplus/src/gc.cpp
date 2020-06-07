#include "mpplib/gc.hpp"
#include "mpplib/containers/gc_graph.hpp"

#include <memory>

namespace mpp {
    std::vector<GcPtr*> GC::s_activeGcPtrs;
    std::size_t s_garbageSize = 0;
    std::size_t s_dataSize = 0;

    bool GC::Collect()
    {
        std::unique_ptr<GcGraph> objectsGraph = std::make_unique<GcGraph>();

        // Construct chunks graph
        for (auto gcPtr : s_activeGcPtrs)
        {
            Chunk* gcPtrObjectChunk = MemoryManager::GetInUseChunkByPtr(gcPtr->GetVoid());
            Chunk* gcPtrLocationChunk = MemoryManager::GetInUseChunkByPtr(reinterpret_cast<void*>(gcPtr));

            if (gcPtrLocationChunk != nullptr)
            {
                //Check that "to" vertex is already exsist
                Vertex* to = objectsGraph->FindVertex(gcPtrObjectChunk);
                if (to != nullptr)
                {
                    to->AddGcPtr(gcPtr);           
                } else {
                    to = new Vertex(gcPtrObjectChunk);
                    to->AddGcPtr(gcPtr); 
                }
                //Check that "from" vertex is already exsist
                Vertex* from = objectsGraph->FindVertex(gcPtrLocationChunk);
                if (from == nullptr)
                    from = new Vertex(gcPtrLocationChunk);
                objectsGraph->AddEdge(from, to);    
            } else {
                Vertex* vertex = objectsGraph->FindVertex(gcPtrObjectChunk);
                if (vertex != nullptr)
                {
                    vertex->AddGcPtr(gcPtr);           
                } else {
                    vertex = new Vertex(gcPtrObjectChunk);
                    vertex->AddGcPtr(gcPtr);
                    objectsGraph->AddVertex(vertex);
                }
            }
        }
    }
}