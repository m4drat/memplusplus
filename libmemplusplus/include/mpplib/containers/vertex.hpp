#pragma once

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include <mpplib/chunk.hpp>
#include <mpplib/gcptr.hpp>

namespace mpp {
    /**
     * Represent Vertex in graph. Each vertex represent unique chunk in graph.
     */
    class Vertex
    {
    private:
        /**
         * Chunk linked with current vertex.
         */
        Chunk* m_correspondingChunk;
        /**
         * Set set of vertexes that the current vertex points to.
         */
        std::set<Vertex*> m_neighbors;
        /**
         * The set of vertices, that points to current vertex.
         */
        std::set<Vertex*> m_pointingToVertices;
        /**
         * Vector of GcPtr's that are pointing to current chunk.
         */
        std::vector<GcPtr*> m_pointingToGcPtrs;

    public:
        Vertex() = delete;
        /**
         * Default vertex constructor.
         * @param t_chunk chunk linked with current vertex.
         */
        Vertex(Chunk* t_chunk)
            : m_correspondingChunk(t_chunk)
        {}
        
        /**
         * Set new value for m_correspondingChunk.
         * @param t_chunk new value for chunk pointer.
         */
        void UpdateChunkPtr(Chunk* t_chunk);
        
        /**
         * Add new vertex, that points to the current vertex.
         * @param t_pointingVertex pointer to vertex.
         */
        void AddPointingVertex(Vertex* t_pointingVertex);
        
        /**
         * Get all vertices, that points to the current vertex.
         * @return reference to set of pointers to vertices
         */
        std::set<Vertex*>& GetPointingVertices();
        
        /**
         * Add the vertex, that current vertex points to.
         * @param t_neigbor vertex, to add to neighbors.
         */
        void AddNeighbor(Vertex* t_neigbor);
        
        /**
         * Remove the vertex that the current vertex points to.
         * @param t_neigbor vertex, to remove from neighbors.
         */
        bool RemoveNeighbor(Vertex* t_neigbor);

        /**
         * Get All vertices, that cureent vertex points to.
         * @return set of vertices
         */
        std::set<Vertex*>& GetNeighbors();

        void AddGcPtr(GcPtr* t_gcPtr);
        bool RemoveGcPtr(GcPtr* t_gcPtr);
        std::vector<GcPtr*>& GetPointingToGcPtrs();

        Chunk* GetCorrespondingChunk() const;
        std::string ToString() const;
    };
}