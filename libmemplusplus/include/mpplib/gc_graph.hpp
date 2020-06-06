#pragma once

#include <set>
#include <vector>
#include <cstdint>

#include "mpplib/gcptr.hpp"
#include "mpplib/chunk.hpp"

namespace mpp {
    class GcGraph
    {
    private:
        // Represents chunk in graph
        class Vertex
        {
            Chunk* m_correspondingChunk;
            std::vector<Vertex*> m_neighbors;
            // std::vector<GcPtr*> m_pointingToGcPtrs;
        };
        // m_adjList[0].first => corresponding vertex (chunk), 
        // m_adjList[0].second => corresponding vector of GcPtrs to current chunk
        std::set<std::pair<Vertex*, std::vector<GcPtr*>>> m_adjList;

    public:
        GcGraph(const std::vector<Vertex*> t_adjList);
        bool AddEdge(Vertex t_from, Vertex t_to);
        bool DeleteEdge(Vertex t_from, Vertex t_to);

        Vertex* GetVertex(Vertex* t_toFind)
        {
        }

        bool AddVertex(Vertex t_vertex);
        bool DeleteVertex(Vertex t_vertex);

        bool Clear();
    };
}