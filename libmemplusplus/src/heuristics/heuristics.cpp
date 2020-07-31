#include "mpplib/heuristics/heuristics.hpp"

namespace mpp {
    Heuristics::Heuristics(GcGraph* t_objectsGraph)
    {
        m_subgraphs = t_objectsGraph->WeaklyConnectedComponents();
    }

    std::pair<std::reference_wrapper<std::vector<Vertex*>>,
              std::reference_wrapper<std::size_t>>
    Heuristics::Layout()
    {
        for (auto& graph : m_subgraphs) {
            for (const auto& v : graph->GetAdjList()) {
                m_layoutedHeap.push_back(v);
                m_neededSpace += v->GetCorrespondingChunk()->GetSize();
            }
        }
        // for (auto& gcGraph : m_subgraphs)
        // {
        //     auto groups = ExtractGroups(gcGraph);
        //     for (auto [gcSubgraph, DSType] : groups)
        //     {
        //         switch (DSType)
        //         {
        //         case DataStructures::LinkedList:
        //             // layoutedGroup = // Somehow layout group
        //             break;
        //         default:
        //             break;
        //         }

        //         // for ()
        //         // {
        //         //     // m_layoutedHeap.push_back()
        //         // }
        //     }
        // }

        return std::make_pair<std::reference_wrapper<std::vector<Vertex*>>,
                              std::reference_wrapper<std::size_t>>(m_layoutedHeap,
                                                                   m_neededSpace);
    }

    // std::vector<std::pair<GcGraph*, Heuristics::DataStructures>>
    // Heuristics::ExtractGroups(std::unique_ptr<GcGraph>& t_gcSubgraph)
    // {
    //     return std::vector<std::pair<GcGraph*, Heuristics::DataStructures>>();
    // }
}