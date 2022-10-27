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

        std::unique_ptr<GcGraph>& m_objectsGraph;

        const std::set<GcPtr*>& m_gcPtrs;

    public:
        struct LayoutedHeap
        {
            std::vector<Vertex*> vertices;
            std::size_t layoutedSize;

            LayoutedHeap(std::vector<Vertex*>& vertices, std::size_t layoutedSize)
                : vertices(vertices)
                , layoutedSize(layoutedSize)
            {
            }
        };

        Heuristics(std::unique_ptr<GcGraph>& t_objectsGraph, const std::set<GcPtr*>& t_gcPtrs)
            : m_objectsGraph(t_objectsGraph)
            , m_gcPtrs(t_gcPtrs)
        {
        }

        ~Heuristics() = default;

        /**
         * @brief Layouts heap.
         *
         * This method tries to find all possible data structures in graph, and layout
         * them in the most efficient way.
         * @param t_objectsGraph reference to unique_ptr to GcGraph (will be divided into subgraphs)
         * @return pair of vector of vertices and size of all chunks
         */
        LayoutedHeap LayoutHeap();

        LayoutedHeap LayoutLinkedList(
            std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>& t_llGraph);

        LayoutedHeap LayoutGeneralGraph(
            std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>& t_graph);
    };
}