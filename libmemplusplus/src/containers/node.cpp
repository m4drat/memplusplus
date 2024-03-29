#include "mpplib/containers/node.hpp"

namespace mpp {
    Node::Node(Chunk* t_chunk)
        : priority(std::rand())
        , chunk(t_chunk)
        , leftChild(nullptr)
        , rightChild(nullptr)
    {
    }

    Node::Node(const Node& t_node)
        : priority(t_node.priority)
        , chunk(t_node.chunk)
        , leftChild(t_node.leftChild ? new Node(*t_node.leftChild) : nullptr)
        , rightChild(t_node.rightChild ? new Node(*t_node.rightChild) : nullptr)
    {
        // @TODO: - smart pointers memory management
    }

    Node& Node::operator=(const Node& t_node)
    {
        if (&t_node == this)
            return *this;

        Delete();

        priority = t_node.priority;
        chunk = t_node.chunk;

        // TODO - smart pointers memory management
        leftChild = t_node.leftChild ? new Node(*t_node.leftChild) : nullptr;
        rightChild = t_node.rightChild ? new Node(*t_node.rightChild) : nullptr;

        return *this;
    }

    Node::Node(Node&& t_node) noexcept
        : priority(t_node.priority)
        , chunk(t_node.chunk)
        , leftChild(t_node.leftChild)
        , rightChild(t_node.rightChild)
    {
        t_node.chunk = nullptr;
        t_node.leftChild = nullptr;
        t_node.rightChild = nullptr;
    }

    Node& Node::operator=(Node&& t_node) noexcept
    {
        if (&t_node == this)
            return *this;

        // Delete current object
        Delete();

        // Construct new one
        priority = t_node.priority;
        chunk = t_node.chunk;
        leftChild = t_node.leftChild;
        rightChild = t_node.rightChild;

        t_node.chunk = nullptr;
        t_node.leftChild = nullptr;
        t_node.rightChild = nullptr;

        return *this;
    }

    Node::~Node()
    {
        Delete();
    }

    void Node::Delete()
    {
        delete leftChild;
        leftChild = nullptr;
        delete rightChild;
        rightChild = nullptr;
    }

#if MPP_STATS == 1
    std::ostream& DumpNode(std::ostream& t_out, Node* t_node)
    {
        t_out << "[" << reinterpret_cast<void*>(t_node) << "]"
              << "(" << std::to_string(t_node->priority) << ", {" << t_node->chunk
              << "}, L:" << reinterpret_cast<void*>(t_node->leftChild)
              << ", R:" << reinterpret_cast<void*>(t_node->rightChild);
        return t_out;
    }

    std::ostream& operator<<(std::ostream& t_out, Node* t_node)
    {
        DumpNode(t_out, t_node);
        return t_out;
    }
#endif

}