#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "mpplib/containers/vertex.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

namespace mpp {
    /**
     * @brief Implements Graph structure to use specifically with chunks and gcPtr objects.
     */
    class GcGraph
    {
    private:
        /**
         * @brief Defines comparison/uniqueness logic to use in adjList.
         */
        struct VertexComparator
        {
            bool operator()(const Vertex* lhs, const Vertex* rhs) const
            {
                return (lhs->GetLoc() < rhs->GetLoc());
            }
        };

        /**
         * @brief adjacency list to store graph.
         */
        std::set<Vertex*, VertexComparator> m_adjList;

    public:
        /**
         * @brief Default constructor for graph object.
         */
        GcGraph() = default;

        /**
         * @brief Constructor to initialize from reference to another graph.
         * @param t_other GcGraph, to copy from.
         * @warning This copy constructor performs only shallow copy!
         */
        GcGraph(GcGraph& t_other);

        /**
         * @brief Constructor to initialize from vector of vertices.
         * @param t_other vector of vertexes, to copy from.
         * @warning This copy constructor performs only shallow copy!
         */
        explicit GcGraph(const std::vector<Vertex*>& t_other);

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
         *
         * @return std::ostream
         */
        std::ostream& GenerateGraphvizLayoutSimple(std::ostream& t_out) const;

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
        void RemoveEdge(Vertex* t_from, Vertex* t_to);

        /**
         * @brief Adds vertex to the graph adjacency list.
         * @param t_vertex vertex, to create edge from.
         * @return pair of iterator to inserted element, and result of insertion (if
         * vertex already in the graph) result of insertion will be false
         */
        std::pair<std::set<Vertex*>::iterator, bool> AddVertex(Vertex* t_vertex);

        /**
         * @brief Removes vertex from the graphs adjacency list.
         * @param t_vertex vertex to remove from the graph.
         * @return true, if element removed successfully
         */
        bool RemoveVertex(Vertex* t_vertex);

        /**
         * @brief Find all weakly connected components in the graph.
         * @return vector of pointers to graphs, that forms weakly
         * connected components
         * @warning returns GcGraphs, which are formed based on original GcGraph.
         * So as soon, as original GcGraph is destroyed, all connected components will
         * also become invalid.
         */
        std::vector<std::unique_ptr<GcGraph, std::function<void(GcGraph*)>>>
        WeaklyConnectedComponents();

        /**
         * @brief Helper method to use with DirectedDFS.
         * @sa DirectedDFS
         */
        void DDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited);

        /**
         * @brief Perform Depth-First-Search in the directed version of the graph.
         *
         * This function takes into account, that graph is directed.
         * @param t_vertex vertex, from which we want to start directed DFS.
         * @return vector of vertices, that can be accessed from specified vertex
         */
        std::vector<Vertex*> DirectedDFS(Vertex* t_vertex);

        /**
         * @brief Helper method to use with DirectedDFS.
         * @sa UndirectedDFS
         */
        void UDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited);

        /**
         * @brief Perform Depth-First-Search in the undirected version of the graph.
         *
         * This function doesn't take into account, that the graph is directed. We
         * represent it with undirected version.
         * @param t_vertex vertex, from which we want to start undirected DFS.
         * @return vector of vertices, that can be accessed from specified vertex
         */
        std::vector<Vertex*> UndirectedDFS(Vertex* t_vertex);

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
        uint32_t GetGraphVerticesCount();

        /**
         * @brief Get the adjacency list, that represent current graph.
         * @return set of vertices (adjacency list)
         */
        std::set<Vertex*, VertexComparator>& GetAdjList();

        // GcGraph* GetUndirected();
        // std::vector<std::vector<>> GetAdjMatrix();
    };
}