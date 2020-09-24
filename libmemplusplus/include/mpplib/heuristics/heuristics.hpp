#pragma once

#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/containers/vertex.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#include <memory>

namespace mpp {
    /**
     * @brief Implements heuristics, that helps to relayout heap,
     * to efficiently place objects in memory.
     */
    class Heuristics
    {
    private:
        /**
         * @brief All possible data structures, that heuristics
         * can identify.
         */
        enum class DataStructures
        {
            LinkedList,
            DoubleLinkedList,
            Tree,
            Graph,
            Undefined
        };
        /**
         * @brief Size required for new arena.
         */
        std::size_t m_neededSpace{ 0 };

        /**
         * @brief Fully layouted heap.
         */
        std::vector<Vertex*> m_layoutedHeap;

    public:
        Heuristics() = default;
        ~Heuristics() = default;

        /**
         * @brief Finds particular data structures in objects graph, e.g. LinkedList or
         * BinaryTree.
         * @param t_gcSubgraph subgraph, that extracted from objects graph.
         * @return vector of pairs of pointers to subgraphs, and types of found
         * datastructures.
         */
        std::vector<std::pair<GcGraph*, DataStructures>> ExtractGroups(
          std::unique_ptr<GcGraph>& t_gcSubgraph);

        /**
         * @brief Layouts heap.
         *
         * This method tries to find all possible data structures in graph, and layout
         * them in the most efficient way.
         * @param t_objectsGraph reference to unique_ptr to GcGraph (will be divided into subgraphs)
         * @return pair of vector of vertices and size of all chunks
         */
        std::pair<std::reference_wrapper<std::vector<Vertex*>>, std::reference_wrapper<std::size_t>>
        Layout(std::unique_ptr<GcGraph>& t_objectsGraph);
    };
}