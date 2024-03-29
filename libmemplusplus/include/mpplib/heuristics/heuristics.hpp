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

        //! @brief Fully layouted heap.
        std::vector<Vertex*> m_layoutedHeap;

        //! @brief Graph of all objects.
        std::unique_ptr<GcGraph>& m_objectsGraph;

    public:
        //! @brief Layouted heap structure. Represents compacted and layouted memory.
        struct LayoutedHeap
        {
            //! @brief All chunks inside layouted heap.
            std::vector<Vertex*> vertices;
            //! @brief Size of all chunks inside layouted heap.
            std::size_t layoutedSize;

            /**
             * @brief Construct a new Layouted Heap object
             * @param vertices All chunks inside layouted heap.
             * @param layoutedSize Size of all chunks inside layouted heap.
             */
            LayoutedHeap(std::vector<Vertex*>& vertices, std::size_t layoutedSize)
                : vertices(vertices)
                , layoutedSize(layoutedSize)
            {
            }
        };

        /**
         * @brief Construct a new Heuristics object
         * @param t_objectsGraph Graph of all objects.
         */
        explicit Heuristics(std::unique_ptr<GcGraph>& t_objectsGraph)
            : m_objectsGraph(t_objectsGraph)
        {
        }

        ~Heuristics() = default;

        //! @brief Deleted copy constructor.
        Heuristics(const Heuristics&) = delete;

        //! @brief Deleted copy assignment operator.
        Heuristics& operator=(const Heuristics&) = delete;

        //! @brief Deleted move constructor.
        Heuristics(Heuristics&&) = delete;

        //! @brief Deleted move assignment operator.
        Heuristics& operator=(Heuristics&&) = delete;

        /**
         * @brief Layouts heap.
         *
         * This method tries to find all possible data structures in graph, and layout
         * them in the most efficient way.
         * @param t_objectsGraph reference to unique_ptr to GcGraph (will be divided into subgraphs)
         * @return pair of vector of vertices and size of all chunks
         */
        LayoutedHeap LayoutHeap();

        /**
         * @brief Tries to layout LinkedList data structure in the most efficient way.
         * @param t_llGraph Graph that should (but not necessarily) represent LinkedList.
         * @return LayoutedHeap Successfully layouted t_llGraph or its part.
         */
        static LayoutedHeap LayoutLinkedList(std::unique_ptr<GcGraphView>& t_llGraph);

        /**
         * @brief Layouts unknown data structure in the most efficient way.
         * @param t_graph Graph with chunks that should be layouted.
         * @return LayoutedHeap Successfully layouted t_graph.
         */
        static LayoutedHeap LayoutGeneralGraph(std::unique_ptr<GcGraphView>& t_graph);
    };
}
