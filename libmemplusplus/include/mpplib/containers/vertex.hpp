#pragma once

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "mpplib/utils/profiler_definitions.hpp"
#include <mpplib/chunk.hpp>
#include <mpplib/gcptr.hpp>

namespace mpp {
    /**
     * @brief Represent Vertex in the graph. Each vertex represents unique memory location
     * (potentially a chunk) in the graph.
     */
    class Vertex
    {
    private:
        /**
         * @brief Location linked with the current vertex.
         */
        std::byte* m_correspondingLocation;
        /**
         * @brief Set of vertices that the current vertex points to.
         */
        std::set<Vertex*> m_neighbors;
        /**
         * @brief Set of vertices, that are pointing the to current vertex.
         */
        std::set<Vertex*> m_pointingToVertices;
        /**
         * @brief Set of GcPtr's that are pointing to the current chunk.
         */
        std::set<GcPtr*> m_pointingToGcPtrs;
        /**
         * @brief Says whether the m_correspondingLocation is a pointer to a valid chunk or not.
         */
        bool m_currLocationIsAChunk;

    public:
        Vertex() = delete;
        /**
         * @brief Default vertex constructor.
         * @param t_loc location (possibly chunk) linked with current vertex.
         */
        explicit Vertex(std::byte* t_location)
            : m_correspondingLocation(t_location)
            , m_currLocationIsAChunk(false)
        {
        }

        explicit Vertex(Chunk* t_location)
            : m_correspondingLocation((std::byte*)t_location)
            , m_currLocationIsAChunk(true)
        {
        }

        explicit Vertex(std::byte* t_location, bool t_currLocationIsAChunk)
            : m_correspondingLocation(t_location)
            , m_currLocationIsAChunk(t_currLocationIsAChunk)
        {
        }

        /**
         * @brief Checks whether location is a chunk or not.
         *
         * @return true if location is a chunk, false otherwise.
         */
        bool IsChunk() const;

        /**
         * @brief Set new value for m_correspondingLocation.
         * @param t_location new value for location pointer.
         */
        void UpdateLocationPtr(std::byte* t_location);

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
         * @param t_neighbor vertex, to add to neighbors.
         */
        void AddNeighbor(Vertex* t_neighbor);

        /**
         * @brief Remove the vertex that the current vertex points to.
         * @param t_neighbor vertex, to remove from neighbors.
         */
        bool RemoveNeighbor(Vertex* t_neighbor);

        /**
         * @brief Get All vertices, that current vertex points to.
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
         * @brief Get the All gcptrs located inside current vertex (chunk).
         * @param t_gcPtrs set of pointers to GcPtrs, obtained by calling GetGcPtrs() on instance of
         * GC class.
         * @return std::set<GcPtr*>&
         */
        std::set<GcPtr*> GetAllOutgoingGcPtrs(std::set<GcPtr*>& t_gcPtrs);

        /**
         * @brief Get all GcPtr's, that points to current vertex (chunk).
         * @return std::set<GcPtr*>& pointing to current vertex GcPtr's
         */
        std::set<GcPtr*>& GetPointingToGcPtrs();

        /**
         * @brief Get corresponding location.
         * @return std::byte* location (potentially chunk), that current vertex represents
         */
        std::byte* GetLoc() const;

        /**
         * @brief Get corresponding location as a chunk object. The caller must check whether the
         * location is an actual chunk or not.
         * @sa GetCorrespondingLocation
         * @return Chunk* pointer that points to a chunk object
         */
        Chunk* GetLocationAsAChunk() const;

        /**
         * @brief Get string representation of the current vertex.
         * @return std::string string representation of the vertex
         */
        std::string ToString() const;
    };
}