#pragma once

#include <vector>
#include <cstdint>

namespace mpp {
    class Graph
    {
        class Vertex; // 
        class Edge;
        struct Node
        {
            uint32_t flags;
            std::vector<Node*> Childs;
        };
    };
}