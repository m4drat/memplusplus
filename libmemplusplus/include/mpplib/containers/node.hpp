#pragma once

#include "mpplib/chunk.hpp"
#include <cstdlib>
#include <utility>

#include <iostream>
#include <string>

namespace mpp {
    /**
     * Node class to use in ChunkTreap.
     */
    struct Node final
    {
    public:
        /**
         * Node priority in treep
         */
        int32_t priority{ 0 };
        /**
         * Сhunk related to the current node.
         */
        Chunk* chunk{ nullptr };
        /**
         * Reference to the left node.
         */
        Node* leftChild{ nullptr };
        /**
         * Reference to the right node.
         */
        Node* rightChild{ nullptr };

        /**
         * Constructor, that construct node from chunk.
         */
        Node(Chunk* t_chunk);

        /**
         * Copy-Constructor, that constructs node from const node reference.
         */
        Node(const Node& t_node);
        /**
         * Assigment operator, that constructs node from const node reference.
         */
        Node& operator=(const Node& t_node);
        /**
         * Copy-Constructor, that constructs node from r-value node reference.
         */
        Node(Node&& t_node);
        /**
         * Assigment operator, that constructs node from r-value node reference.
         */
        Node& operator=(Node&& t_node);

        /**
         * Default destructor. 
         * @sa Delete.
         */
        ~Node();
        
        /**
         * Dump text represenation of node.
         */
        static std::ostream& DumpNode(std::ostream& t_out, Node* t_node);
        /**
         * Output operator to print node using std::cout.
         */
        friend std::ostream& operator<<(std::ostream& t_out, Node* t_node);

    private:
        /**
         * Deleter method.
         */
        void Delete();
    };
}