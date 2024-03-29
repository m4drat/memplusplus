#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "mpplib/containers/vertex.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

namespace mpp {
    class GarbageCollector;
    class MemoryManager;
    class GcGraphView;

    //! @brief Implements Graph structure to use specifically with chunks and gcPtr objects.
    class GcGraph
    {
    protected:
        //! @brief Defines comparison/uniqueness logic to use in adjList.
        struct VertexComparator
        {
            bool operator()(const Vertex* lhs, const Vertex* rhs) const
            {
                return (lhs->GetLoc() < rhs->GetLoc());
            }
        };

        //! @brief adjacency list to store the graph.
        std::set<Vertex*, VertexComparator> m_adjList;

        //! @brief Set of all root nodes (non-heap pointers).
        std::set<Vertex*, VertexComparator> m_roots;

        //! @brief Reference to parent GarbageCollector object.
        GarbageCollector& m_gc;

        //! @brief Reference to parent MemoryManager object.
        MemoryManager& m_memoryManager;

        /**
         * @brief Constructor to initialize from reference to another graph.
         * @param t_other GcGraph, to copy from.
         * @warning This copy constructor creates only shallow copy!
         */
        GcGraph(GcGraph& t_other)
            : m_adjList(t_other.GetAdjList())
            , m_roots(t_other.GetRoots())
            , m_gc(t_other.m_gc)
            , m_memoryManager(t_other.m_memoryManager)
        {
        }

        /**
         * @brief Constructor to initialize from vector of vertices.
         * @param t_vertices T1& of vertices, to copy from.
         * @param t_roots T2& of roots for newly-created graph.
         * @warning This copy constructor creates only shallow copy!
         */
        template<class T1, class T2>
        GcGraph(const T1& t_vertices,
                const T2& t_roots,
                GarbageCollector& t_gc,
                MemoryManager& t_memoryManager)
            : m_adjList(t_vertices.begin(), t_vertices.end())
            , m_roots(t_roots.begin(), t_roots.end())
            , m_gc(t_gc)
            , m_memoryManager(t_memoryManager)
        {
        }

    public:
        /**
         * @brief Constructor to initialize graph with parent GarbageCollector and MemoryManager.
         * @param t_gc - reference to parent GarbageCollector object.
         * @param t_memoryManager - reference to parent MemoryManager object.
         */
        GcGraph(GarbageCollector& t_gc, MemoryManager& t_memoryManager)
            : m_gc(t_gc)
            , m_memoryManager(t_memoryManager)
        {
        }

        //! @brief Deleted copy constructor.
        GcGraph& operator=(const GcGraph& t_other) = delete;

        //! @brief Deleted move constructor.
        GcGraph(GcGraph&& t_other) noexcept = delete;

        //! @brief Deleted move assignment operator.
        GcGraph& operator=(GcGraph&& t_other) noexcept = delete;

        /**
         * @brief Graph destructor. Iterates through each Vertex in adjList, deletes it,
         * and calls Destructor.
         */
        ~GcGraph();

        /**
         * @brief Clear current graph, by deleting each vertex, and caling destructor on
         * it.
         * @return true, if clear was successfull
         */
        bool Clear();

        /**
         * @brief Add information about GcPtr and the object it controls to objects graph.
         * @param t_gcPtr GcPtr that is going to be added to t_objectsGraph.
         */
        void AddObjectInfo(GcPtr* t_gcPtr);

        /**
         * @brief Generates graph representation in form, that can be used in dot
         * (graphviz), to visualize graph structure.
         * @param t_out output stream.
         * @param t_doNotDrawHeapConnections skip drawing flat heap view.
         * @return std::ostream
         */
        std::ostream& GenerateGraphvizLayoutSimple(std::ostream& t_out,
                                                   bool t_doNotDrawHeapConnections = true) const;

        /**
         * @brief Generates graph representation in form, that can be used in dot
         * (graphviz), to visualize graph structure. This method takes into account all gcptrs.
         *
         * @return std::ostream
         */
        std::ostream& GenerateGraphvizLayoutAdvanced(std::ostream& t_out) const;

        /**
         * @brief Adds new edge to the graph.
         *
         * If edge already exists, creates new additional one.
         * If only one vertex of the edge already exists, creates another, and after that
         * creates edge itself. If both vertexes is not in the graph, creates them, and
         * constructs edge between them.
         * @param t_from vertex, to create edge from.
         * @param t_to vertex, to create edge to
         */
        void AddEdge(Vertex* t_from, Vertex* t_to);

        /**
         * @brief Checks whether the edge exists between two vertices.
         * @warning: this methods takes direction into account!
         *
         * @param t_from vertex, to check edge from.
         * @param t_to vertex, to check edge to.
         * @return true if edge exists, false otherwise.
         */
        bool HasEdge(Vertex* t_from, Vertex* t_to) const;

        /**
         * @brief Removes edge between two vertices.
         * @param t_from vertex, to create edge from.
         * @param t_to vertex, to create edge to
         */
        static void RemoveEdge(Vertex* t_from, Vertex* t_to);

        /**
         * @brief Adds vertex to the graph adjacency list.
         * @param t_vertex vertex, to create edge from.
         * @return pair of iterator to inserted element, and result of insertion (if
         * vertex already in the graph) result of insertion will be false
         */
        std::pair<std::set<Vertex*>::iterator, bool> AddVertex(Vertex* t_vertex);

        /**
         * @brief Adds a vertex to a set of root vertices.
         * @param t_vertex vertex, to save as a root.
         * @return result of the insertion.
         */
        std::pair<std::set<mpp::Vertex*>::iterator, bool> AddRootVertex(Vertex* t_vertex);

        /**
         * @brief Removes vertex from the graphs adjacency list.
         * @param t_vertex vertex to remove from the graph.
         * @return true, if element removed successfully
         */
        bool RemoveVertex(Vertex* t_vertex);

        /**
         * @brief Find all weakly connected components in the graph.
         * @return vector of pointers to graphs, that forms weakly connected components
         * @warning returns GcGraphView's, which are formed based on original GcGraph. So as soon,
         * as original GcGraph is destroyed, all connected components will also become invalid.
         */
        std::vector<std::unique_ptr<GcGraphView>> WeaklyConnectedComponents();

        /**
         * @brief Finds all weakly connected components and then find all vertices reachable from
         * root nodes.
         * @return Vector of pointers to reachable sub-graphs.
         * @warning returns GcGraphView's, which are formed based on original GcGraph. So as soon,
         * as original GcGraph is destroyed, all connected components will also become invalid.
         */
        std::vector<std::unique_ptr<GcGraphView>> ReachableWeaklyConnectedComponents();

        /**
         * @brief Perform directed Depth-First-Search starting from t_vertex.
         * @param t_vertex Vertex, from which we want to start directed DFS.
         * @param t_externalVisited Optional parameter that allows to skip specific vertices.
         * @return GcGraphView - view of the original graph that is built from the vertices
         * found using UDFS.
         */
        std::unique_ptr<GcGraphView> DirectedDFS(
            Vertex* t_vertex,
            const std::unordered_set<Vertex*>& t_externalVisited = {});

        /**
         * @brief Perform undirected Depth-First-Search starting from t_vertex.
         * @param t_vertex vertex, from which we want to start undirected DFS.
         * @return GcGraphView - view of the original graph that is built from the vertices found
         * using UDFS.
         */
        std::unique_ptr<GcGraphView> UndirectedDFS(Vertex* t_vertex);

        /**
         * @brief Search for specified chunk in adjacency list of current graph.
         * @param t_chunk chunk, that associated with some vertex, that we want to find.
         * @return Vertex linked with specified chunk
         */
        Vertex* FindVertex(Chunk* t_chunk) const;

        /**
         * @brief Get the number of vertices in current graph.
         * @return number of vertices in graph
         */
        uint32_t GetVerticesCount();

        /**
         * @brief Get the adjacency list, that represent current graph.
         * @return set of vertices (adjacency list)
         */
        std::set<Vertex*, VertexComparator>& GetAdjList();

        /**
         * @brief Get root nodes.
         * @return std::set<Vertex*, VertexComparator>& of root vertices.
         */
        std::set<Vertex*, VertexComparator>& GetRoots();
    };

    //! @brief A view of the GcGraph.
    class GcGraphView : public GcGraph
    {
    public:
        //! @brief Deleted copy constructor.
        GcGraphView(const GcGraphView& t_other) = delete;

        //! @brief Deleted copy assignment operator.
        GcGraphView& operator=(const GcGraphView& t_other) = delete;

        //! @brief Deleted move constructor.
        GcGraphView(GcGraphView&& t_other) noexcept = delete;

        //! @brief Deleted move assignment operator.
        GcGraphView& operator=(GcGraphView&& t_other) noexcept = delete;

        //! @brief Cleans-up shallow copy.
        ~GcGraphView()
        {
            GetAdjList().clear();
        }

        /**
         * @brief Constructor to initialize from reference to GcGraph.
         * @param t_other GcGraph, to copy from.
         * @warning This copy constructor creates only shallow copy!
         */
        explicit GcGraphView(GcGraph& t_other)
            : GcGraph(t_other)
        {
        }

        /**
         * @brief Constructor to initialize from vector of roots and vertices.
         * @param t_vertices T& of vertices, to copy from.
         * @param t_roots T& of roots for newly-created graph.
         * @warning This copy constructor creates only shallow copy!
         */
        template<class T1, class T2>
        GcGraphView(const T1& t_vertices,
                    const T2& t_roots,
                    GarbageCollector& t_gc,
                    MemoryManager& t_memoryManager)
            : GcGraph(t_vertices, t_roots, t_gc, t_memoryManager)
        {
        }
    };
}