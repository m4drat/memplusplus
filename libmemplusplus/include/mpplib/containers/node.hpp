#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#include <cstdlib>
#include <utility>

#include <iostream>
#include <string>

namespace mpp {
/**
 * @brief Node class to use in ChunkTreap.
 */
struct Node final
{
public:
    /**
     * @brief Node priority in treap
     */
    int32_t priority{ 0 };

    /**
     * @brief Сhunk related to the current node.
     */
    Chunk* chunk{ nullptr };
    
    /**
     * @brief Reference to the left node.
     */
    Node* leftChild{ nullptr };
    
    /**
     * @brief Reference to the right node.
     */
    Node* rightChild{ nullptr };

    /**
     * @brief Constructor, that construct node from chunk.
     */
    Node(Chunk* t_chunk);

    /**
     * @brief Copy-Constructor, that constructs node from const node reference.
     */
    Node(const Node& t_node);
    
    /**
     * @brief Assigment operator, that constructs node from const node reference.
     */
    Node& operator=(const Node& t_node);
    
    /**
     * @brief Copy-Constructor, that constructs node from r-value node reference.
     */
    Node(Node&& t_node);
    
    /**
     * @brief Assigment operator, that constructs node from r-value node reference.
     */
    Node& operator=(Node&& t_node);

    /**
     * @brief Default destructor.
     * @sa Delete.
     */
    ~Node();

#if MPP_STATS == 1
    /**
     * @brief Dump text represenation of the node.
     */
    static std::ostream& DumpNode(std::ostream& t_out, Node* t_node);
    
    /**
     * @brief Overloaded output operator to print node using std::cout.
     */
    friend std::ostream& operator<<(std::ostream& t_out, Node* t_node);
#endif

private:
    /**
     * @brief Deleter method.
     */
    void Delete();
};
}