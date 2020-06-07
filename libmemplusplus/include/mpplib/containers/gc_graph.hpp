#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>

#include "mpplib/containers/vertex.hpp"

namespace mpp {
    class GcGraph
    {
    private:
        struct VertexComparator {
            bool operator() (const Vertex* lhs, const Vertex* rhs) const
            {
                return (lhs->GetCorrespondingChunk() < rhs->GetCorrespondingChunk());
            }
        };
        std::set<Vertex*, VertexComparator> m_adjList;
    
    public:
        GcGraph();
        ~GcGraph();
        void AddEdge(Vertex* t_from, Vertex* t_to);
        void RemoveEdge(Vertex* t_from, Vertex* t_to);

        Vertex* FindVertex(Chunk* t_chunk);

        std::pair<std::set<Vertex *>::iterator, bool> AddVertex(Vertex* t_vertex);
        bool RemoveVertex(Vertex* t_vertex);

        bool Clear();
    };
}