#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/containers/vertex.hpp"
#include "mpplib/utils/macros.hpp"
#include <algorithm>

namespace mpp {
    Heuristics::LayoutedHeap Heuristics::LayoutGeneralGraph(std::unique_ptr<GcGraphView>& t_graph)
    {
        PROFILE_FUNCTION();

        std::vector<Vertex*> layoutedHeap;
        std::size_t neededSpace = 0;

        for (const auto& vertex : t_graph->GetAdjList()) {
            if (!vertex->IsChunk())
                continue;
            layoutedHeap.push_back(vertex);
            neededSpace += vertex->GetLocationAsAChunk()->GetSize();
        }

        return LayoutedHeap{ layoutedHeap, neededSpace };
    }

    Heuristics::LayoutedHeap Heuristics::LayoutLinkedList(std::unique_ptr<GcGraphView>& t_llGraph)
    {
        PROFILE_FUNCTION();

        std::vector<Vertex*> layoutedLL;
        std::size_t neededSpace = 0;

        // Lambda to check if vertex is the list head
        auto isListHead = [](Vertex* t_vertex) {
            return (t_vertex->GetNeighbors().size() == 1 &&
                    t_vertex->GetPointingToGcPtrs().size() == 1 &&
                    !(*t_vertex->GetPointingVertices().begin())->IsChunk());
        };

        Vertex* head = nullptr;
        // Find head of the list
        auto headIt = std::find_if(
            t_llGraph->GetAdjList().begin(), t_llGraph->GetAdjList().end(), isListHead);

        if (headIt != t_llGraph->GetAdjList().end())
            head = *headIt;

        // Layout linked list starting from head
        while (head != nullptr) {
            Vertex* oldHead = head;
            if (head->IsChunk()) {
                layoutedLL.push_back(head);
                neededSpace += head->GetLocationAsAChunk()->GetSize();
            }

            head = (!head->GetNeighbors().empty()) ? *head->GetNeighbors().begin() : nullptr;
            t_llGraph->RemoveVertex(oldHead);
        }

        return LayoutedHeap{ layoutedLL, neededSpace };
    }

    Heuristics::LayoutedHeap Heuristics::LayoutHeap()
    {
        PROFILE_FUNCTION();

        // Divide the graph into weakly connected components, but remove all unreachable vertices.
        auto subgraphs = m_objectsGraph->ReachableWeaklyConnectedComponents();

        for (auto& graph : subgraphs) {
            LayoutedHeap layoutedHeap = LayoutGeneralGraph(graph);
            m_layoutedHeap.insert(
                m_layoutedHeap.end(), layoutedHeap.vertices.begin(), layoutedHeap.vertices.end());
            m_neededSpace += layoutedHeap.layoutedSize;
        }

        return LayoutedHeap{ m_layoutedHeap, m_neededSpace };
    }
}