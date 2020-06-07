#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <string>

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

        std::string GenerateGraphvizLayout();

        void AddEdge(Vertex* t_from, Vertex* t_to);
        void RemoveEdge(Vertex* t_from, Vertex* t_to);

        std::pair<std::set<Vertex *>::iterator, bool> AddVertex(Vertex* t_vertex);
        bool RemoveVertex(Vertex* t_vertex);

        std::vector<GcGraph*> ExtractSubgraphs();
        Vertex* FindVertex(Chunk* t_chunk);
        int32_t GetGraphVerticesCount();
        std::set<Vertex*, VertexComparator>& GetAdjList();
        // std::vector<std::vector<>> GetAdjMatrix();

        bool Clear();
    };
}