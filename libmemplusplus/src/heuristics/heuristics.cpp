#include "mpplib/heuristics/heuristics.hpp"
#include "mpplib/containers/vertex.hpp"
#include "mpplib/utils/macros.hpp"
#include <algorithm>

namespace mpp {
    Heuristics::LayoutedHeap Heuristics::LayoutGeneralGraph(
        std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>& t_graph)
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

    Heuristics::LayoutedHeap Heuristics::LayoutLinkedList(
        std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>& t_llGraph)
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
        auto m_subgraphs = m_objectsGraph->WeaklyConnectedComponents();

        for (auto& graph : m_subgraphs) {
            // Try to layout subgraph as a linked list
            LayoutedHeap layoutedLL = LayoutLinkedList(graph);
            m_layoutedHeap.insert(
                m_layoutedHeap.end(), layoutedLL.vertices.begin(), layoutedLL.vertices.end());
            m_neededSpace += layoutedLL.layoutedSize;

            if (graph->GetVerticesCount() != 0) {
                LayoutedHeap layoutedHeap = LayoutGeneralGraph(graph);
                m_layoutedHeap.insert(m_layoutedHeap.end(),
                                      layoutedHeap.vertices.begin(),
                                      layoutedHeap.vertices.end());
                m_neededSpace += layoutedHeap.layoutedSize;
            }
        }

        return LayoutedHeap{ m_layoutedHeap, m_neededSpace };
    }
}