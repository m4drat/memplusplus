#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <string>

#include "mpplib/containers/vertex.hpp"

namespace mpp {
    /**
     * Implements Graph structure to use specially with chunks and gcPtr objects.
     */
    class GcGraph
    {
    private:
        /**
         * Defines comparison/uniqueness logic to use in adjList.
         */
        struct VertexComparator {
            bool operator() (const Vertex* lhs, const Vertex* rhs) const
            {
                return (lhs->GetCorrespondingChunk() < rhs->GetCorrespondingChunk());
            }
        };
        /**
         * adjacency list to store graph.
         */ 
        std::set<Vertex*, VertexComparator> m_adjList;
    
    public:
        /**
         * Default constructor for graph object.
         */
        GcGraph();
        
        /**
         * Constructor to initialize from reference to another graph.
         * @param t_other GcGraph, to copy from.
         */
        GcGraph(GcGraph& t_other);
        
        /**
         * Constructor to initialize from reference to another graph.
         * @param t_other vector of vertexes, to copy from.
         * @warning This copy constructor performs only shallow copy!
         */
        GcGraph(const std::vector<Vertex*>& t_other);
        
        /**
         * Graph destructor. Iterates through each Vertex in adjList, deletes it, and
         * calls Destructor.
         * @warning This copy constructor performs only shallow copy!
         */ 
        ~GcGraph();

        /**
         * Generates graph representation in form, that can be used in dot (graphviz),
         * to visualize graph structure.
         * @return std::string with description of the graph
         */
        std::string GenerateGraphvizLayout();

        /**
         * Adds new edge to the graph. If edge already exists, creates new additional one.
         * If only one vertex of the edge already exists, creates another, and after that creates 
         * edge itself. If both vertexes is not in the graph, creates them, and constructs edge
         * between them.
         * @param t_from vertex, to create edge from.
         * @param t_to vertex, to create edge to
         */
        void AddEdge(Vertex* t_from, Vertex* t_to);
        
        /**
         * Simply removes edge between two vertices.
         * @param t_from vertex, to create edge from.
         * @param t_to vertex, to create edge to
         */
        void RemoveEdge(Vertex* t_from, Vertex* t_to);

        /**
         * Adds vertex to the graph adjacency list.
         * @param t_vertex vertex, to create edge from.
         * @return pair of iterastor to inserted element, and result of insertion (if vertex already in graph)
         * result of insertion will be false
         */
        std::pair<std::set<Vertex *>::iterator, bool> AddVertex(Vertex* t_vertex);
        
        /**
         * Removes vertex from the graphs adjacency list.
         * @param t_vertex vertex to remove from the graph.
         * @return true, if element removed successfully
         */
        bool RemoveVertex(Vertex* t_vertex);

        /**
         * Find all weakly connected components in the graph.
         * @return vector of unique_ptr's to graphs, that forms weakly
         * connected components
         */
        std::vector<std::unique_ptr<GcGraph>> WeaklyConnectedComponents();


        /**
         * Helper method to use with DirectedDFS.
         * @sa DirectedDFS
         */
        void DDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited);
        
        /**
         * Perform Depth-First-Search in the graph. This function takes into
         * account, that graph is directed.
         * @param t_vertex vertex, from which we want to start directed DFS.
         * @return vector of vertices, that can be accessed from specified vertex
         */
        std::vector<Vertex*> DirectedDFS(Vertex* t_vertex);
        
        /**
         * Helper method to use with DirectedDFS.
         * @sa UndirectedDFS
         */
        void UDFS(Vertex* t_vertex, std::vector<Vertex*>& t_visited);
        
        /**
         * Perform Depth-First-Search in the graph. This function doesn't take into
         * account, that the graph is directed. We represent it with undirected version.
         * @param t_vertex vertex, from which we want to start undirected DFS.
         * @return vector of vertices, that can be accessed from specified vertex
         */
        std::vector<Vertex*> UndirectedDFS(Vertex* t_vertex);

        /**
         * Search for specified chunk in adjacency list of current graph.
         * @param t_chunk chunk, that associated with some vertex, that we want to find.
         * @return Vertex linked with specified chunk
         */
        Vertex* FindVertex(Chunk* t_chunk);

        /**
         * Get the number of vertices in current graph.
         * @return number of vertices in graph
         */
        int32_t GetGraphVerticesCount();

        /**
         * Get the adjacency list, that represent current graph.
         * @return set of vertices (adjacency list)
         */
        std::set<Vertex*, VertexComparator>& GetAdjList();
        // GcGraph* GetUndirected();
        // std::vector<std::vector<>> GetAdjMatrix();

        /**
         * Clear current graph, by deleteing each vertex, and caling destructor on it.
         * @return true, if clear was successfull
         */
        bool Clear();
    };
}