#pragma once

#include "mpplib/chunk.hpp"
#include <utility>
#include <utility>
#include <cstdlib>

namespace mpp {
    struct Node final 
    {
    public:
        int32_t priority{ 0 };
        Chunk* chunk{ nullptr };
        Node* leftChild{ nullptr };
        Node* rightChild{ nullptr };

        Node::Node(Chunk* t_chunk);

        Node(const Node& t_node);
        Node& operator=(const Node& t_node);
        Node(Node&& t_node);
        Node& operator=(Node&& t_node);

        ~Node();

    private:
        void Delete();
    };

    // TODO: ??????
    Node::Node(Chunk* t_chunk):
        priority(std::rand()),
        chunk(t_chunk),
        leftChild(nullptr),
        rightChild(nullptr)
    {}

    Node::Node(const Node& t_node):
        priority(t_node.priority),
        chunk(t_node.chunk)
    {
        leftChild = t_node.leftChild ? new Node(*t_node.leftChild) : nullptr;
        rightChild = t_node.rightChild ? new Node(*t_node.rightChild) : nullptr;
    }

    Node& Node::operator=(const Node& t_node) {
        if (&t_node == this) return *this;

        Delete();

        priority = t_node.priority;
        chunk = t_node.chunk;
        leftChild = t_node.leftChild ? new Node(*t_node.leftChild) : nullptr;
        rightChild = t_node.rightChild ? new Node(*t_node.rightChild) : nullptr;

        return *this;
    }

    Node::Node(Node&& t_node):
        priority(t_node.priority),
        chunk(std::move(t_node.chunk)),
        leftChild(leftChild),
        rightChild(rightChild)
    {
        t_node.chunk = nullptr;
        t_node.leftChild = nullptr;
        t_node.rightChild = nullptr;
    }

    Node& Node::operator=(Node&& t_node) {
        if (&t_node == this) return *this;

        Delete();

        priority = t_node.priority;
        chunk = std::move(t_node.chunk);
        leftChild = t_node.leftChild;
        rightChild = t_node.rightChild;

        t_node.chunk = nullptr;
        t_node.leftChild = nullptr;
        t_node.rightChild = nullptr;

        return *this;
    }

    Node::~Node() {
        Delete();
    }

    void Node::Delete() {
        delete leftChild;
        delete rightChild;
    }
}