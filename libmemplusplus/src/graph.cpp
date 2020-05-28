#include "mpplib/graph.hpp"
#include <vector>

namespace mpp {
    Graph::Graph(std::vector<Edge> const& edges, int t_NodesCount)
    {
        m_ColList.resize(t_NodesCount);
        this->m_NodesCount = t_NodesCount;

        for (auto& edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            if (src <= t_NodesCount && dest <= t_NodesCount) {
                m_ColList[src].push_back(std::make_pair(dest, weight));
                m_ColList[dest].push_back(std::make_pair(src, weight));
            }
        }
    }

    void Graph::printGraph()
    {
        for (int i = 0; i < this->m_NodesCount; i++) {
            for (Pair edge : this->m_ColList[i])
                std::cout << i << "    " << edge.first << " -- " << edge.second;
            std::cout << std::endl;
        }
    }
}