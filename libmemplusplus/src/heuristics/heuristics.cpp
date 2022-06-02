#include "mpplib/heuristics/heuristics.hpp"

namespace mpp {
    Heuristics::LayoutedHeap Heuristics::Layout(std::unique_ptr<GcGraph>& t_objectsGraph)
    {
        PROFILE_FUNCTION();
        auto m_subgraphs = t_objectsGraph->WeaklyConnectedComponents();

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

        return { m_layoutedHeap, m_neededSpace };
    }

    // std::vector<std::pair<GcGraph*, Heuristics::DataStructures>>
    // Heuristics::ExtractGroups(std::unique_ptr<GcGraph>& t_gcSubgraph)
    // {
    //     return std::vector<std::pair<GcGraph*, Heuristics::DataStructures>>();
    // }
}