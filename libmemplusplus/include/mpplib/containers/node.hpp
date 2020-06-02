#pragma once

#include "mpplib/chunk.hpp"
#include <cstdlib>
#include <utility>

#include <iostream>
#include <string>

namespace mpp {
    struct Node final
    {
    public:
        int32_t priority{ 0 };
        Chunk* chunk{ nullptr };
        Node* leftChild{ nullptr };
        Node* rightChild{ nullptr };

        Node(Chunk* t_chunk);

        Node(const Node& t_node);
        Node& operator=(const Node& t_node);
        Node(Node&& t_node);
        Node& operator=(Node&& t_node);

        ~Node();

        static std::ostream& DumpNode(std::ostream& t_out, Node* t_node);
        friend std::ostream& operator<<(std::ostream& t_out, Node* t_node);
    private:
        void Delete();
    };
}