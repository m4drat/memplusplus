#pragma once
#include <bits/stdc++.h>
#include <vector>

namespace mpp {

    class Graph
    {
    using Pair = std::pair<int, int>;
    private:
        int m_NodesCount{ 0 };
        std::vector<std::vector<Pair>> m_ColList;

    public:
        struct Edge
        {
            int src, dest, weight;
        };

        Graph(std::vector<Edge> const& edges, int t_NodesCount);
        void printGraph();
    };
}