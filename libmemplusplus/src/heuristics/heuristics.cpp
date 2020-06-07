#include "mpplib/heuristics/heuristics.hpp"

namespace mpp
{
    Heuristics::Heuristics(std::unique_ptr<GcGraph>& t_objectsGraph)
    {
        m_subgraphs = t_objectsGraph->ExtractSubgraphs();
    }

    std::pair<std::vector<Vertex*>, std::size_t> Heuristics::Layout()
    {
        for (GcGraph* gcGraph : m_subgraphs)
        {
            auto groups = ExtractGroups(gcGraph);
            for (auto [gcSubgraph, DSType] : groups)
            {
                switch (DSType)
                {
                case DataStructures::LinkedList:
                    layoutedGroup = // Somehow layout group
                    break;
                default:
                    break;
                }

                for ()
                {
                    m_layoutedHeap.push_back()
                }
            }
        }
    }

    std::vector<std::pair<GcGraph*, Heuristics::DataStructures>> Heuristics::ExtractGroups(GcGraph* t_gcSubgraph)
    {

    }
}