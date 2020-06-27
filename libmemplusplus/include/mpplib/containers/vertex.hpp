#pragma once

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <mpplib/chunk.hpp>
#include <mpplib/gcptr.hpp>

namespace mpp {
    /**
     * @brief Represent Vertex in the graph. Each vertex represents unique chunk in graph.
     */
    class Vertex
    {
    private:
        /**
         * @brief Chunk linked with the current vertex.
         */
        Chunk* m_correspondingChunk;
        /**
         * @brief Set of vertices that the current vertex points to.
         */
        std::set<Vertex*> m_neighbors;
        /**
         * @brief The set of vertices, that points to current vertex.
         */
        std::set<Vertex*> m_pointingToVertices;
        /**
         * @brief Vector of GcPtr's that are pointing to current chunk.
         */
        std::vector<GcPtr*> m_pointingToGcPtrs;

    public:
        Vertex() = delete;
        /**
         * @brief Default vertex constructor.
         * @param t_chunk chunk linked with current vertex.
         */
        Vertex(Chunk* t_chunk)
            : m_correspondingChunk(t_chunk)
        {}

        /**
         * @brief Set new value for m_correspondingChunk.
         * @param t_chunk new value for chunk pointer.
         */
        void UpdateChunkPtr(Chunk* t_chunk);

        /**
         * @brief Add new vertex, that points to the current vertex.
         * @param t_pointingVertex pointer to vertex.
         */
        void AddPointingVertex(Vertex* t_pointingVertex);

        /**
         * @brief Get all vertices, that points to the current vertex.
         * @return reference to set of pointers to vertices
         */
        std::set<Vertex*>& GetPointingVertices();

        /**
         * @brief Add the vertex, that current vertex points to.
         * @param t_neigbor vertex, to add to neighbors.
         */
        void AddNeighbor(Vertex* t_neigbor);

        /**
         * @brief Remove the vertex that the current vertex points to.
         * @param t_neigbor vertex, to remove from neighbors.
         */
        bool RemoveNeighbor(Vertex* t_neigbor);

        /**
         * @brief Get All vertices, that cureent vertex points to.
         * @return set of vertices
         */
        std::set<Vertex*>& GetNeighbors();

        /**
         * @brief Adds GcPtr, that points to the current vertex (chunk).
         * @param t_gcPtr pointer to GcPtr to add to the current vertex.
         */
        void AddGcPtr(GcPtr* t_gcPtr);
        /**
         * @brief Removes GcPtr from list of pointing to the current vertex GcPtr's.
         * @param t_gcPtr pointer to GcPtr to delete from list
         * @return true if GcPtr was deleted successfully, false - otherwise
         */
        bool RemoveGcPtr(GcPtr* t_gcPtr);
        /**
         * @brief Get all GcPtr's, that points to current vertex (chunk).
         * @return std::vector<GcPtr*>& pointing to current vertex GcPtr's
         */
        std::vector<GcPtr*>& GetPointingToGcPtrs();

        /**
         * @brief Get corresponding chunk object.
         * @return Chunk* chunk, that current vertex represents
         */
        Chunk* GetCorrespondingChunk() const;

        /**
         * @brief Get string representation of the current vertex.
         * @return std::string string representation of the vertex
         */
        std::string ToString() const;
    };
}