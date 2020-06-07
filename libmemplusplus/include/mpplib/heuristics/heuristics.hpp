#pragma once

#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/containers/vertex.hpp"

namespace mpp
{
    class Heuristics
    {
    private:
        enum class DataStructures
        {
            LinkedList,
            DoubleLinkedList,
            Tree,
            BinarySearchTree,
            Graph,
            Undefined
        };
        std::size_t m_neededSpace{ 0 };
        std::vector<GcGraph*> m_subgraphs;
        std::vector<Vertex*> m_layoutedHeap;

    public:
        Heuristics() = delete;
        Heuristics(std::unique_ptr<GcGraph>& t_objectsGraph);
        ~Heuristics() = default;

        std::vector<std::pair<GcGraph*, DataStructures>> ExtractGroups(GcGraph* t_gcSubgraph);
        // Layouts heap using heuristics
        std::pair<std::vector<Vertex*>, std::size_t> Layout();
    };
}