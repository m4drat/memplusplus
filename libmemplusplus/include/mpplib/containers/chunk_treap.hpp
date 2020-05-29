#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/node.hpp"

namespace mpp {
    class ChunkTreap final
    {
        // default constructor
        ChunkTreap();
        
        // copy/assign
        ChunkTreap(const ChunkTreap& t_treap);
        ChunkTreap& operator=(const ChunkTreap& t_treap);
        ChunkTreap(ChunkTreap&& t_treap);
        ChunkTreap& operator=(ChunkTreap&& t_treap);

        // destruct
        ~ChunkTreap();

        Chunk* MinSizeChunk() const;
        Chunk* MaxSizeChunk() const;

        // TODO
        template<class... Args>
        void EmplaceElement(Args&&... t_arguments);

        // TODO
        void InsertElement(const NumberType& t_element);
        // TODO
        void InsertElement(NumberType&& t_element);

        void RemoveElement(const NumberType& t_element);

        const NumberType& FirstGreaterOrEqualThan(const NumberType& t_element) const;

        bool HasElement(const NumberType& t_element) const;

    private:
        Node* m_root;

        void Delete();

        void InsertNode(Node* t_node);

        static void MergeNodes(Node* t_left, Node* t_right, Node*& t_root);
        static void SplitNodesByElement(
            Node* t_root,
            Node*& t_left,
            Node*& t_right,
            const NumberType& t_element
        );
    };

    ChunkTreap::ChunkTreap():
        m_root(nullptr)
    {}

    ChunkTreap::ChunkTreap(const ChunkTreap& t_treap):
        m_root(new Node(*t_treap.m_root))
    {}

    ChunkTreap& ChunkTreap::operator=(const ChunkTreap& t_treap) {
        if (&t_treap == this) return *this;

        Delete();

        m_root = new Node(*t_treap.m_root);

        return *this;
    }

    ChunkTreap::ChunkTreap(ChunkTreap&& t_treap):
        m_root(t_treap.m_root)
    {
        t_treap.m_root = nullptr;
    }

    ChunkTreap& ChunkTreap::operator=(ChunkTreap&& t_treap) {
        if (&t_treap == this) return *this;

        Delete();

        m_root = t_treap.m_root;
        t_treap.m_root = nullptr;

        return *this;
    }

    ChunkTreap::~ChunkTreap() {
        Delete();
    }

    void ChunkTreap::Delete() {
        delete m_root;
    }

    Chunk* ChunkTreap::MinSizeChunk() const {
        Node* currentNode = m_root;

        for (; currentNode->leftChild; currentNode = currentNode->leftChild);

        return currentNode->chunk;
    }

    Chunk* ChunkTreap::MaxSizeChunk() const {
        Node* currentNode = m_root;

        for (; currentNode->rightChild; currentNode = currentNode->rightChild);

        return currentNode->chunk;
    }

    template<class... Args>
    void ChunkTreap::EmplaceElement(Args&&... t_args) {
        InsertNode(new Node(std::forward<ArgumentTypes>(t_args)...));
    }

    void ChunkTreap::InsertElement(Chunk* t_chunk) {
        InsertNode(new Node(t_chunk));
    }

    void ChunkTreap::InsertElement(Chunk&& t_chunk) {
        InsertNode(new Node(std::move(t_chunk)));
    }

    void ChunkTreap::InsertNode(Node* t_node) {
        Node* leftSubtree = nullptr;
        Node* rightSubtree = nullptr;

        SplitNodesByElement(m_root, leftSubtree, rightSubtree, t_node->element);
        MergeNodes(leftSubtree, t_node, leftSubtree);
        MergeNodes(leftSubtree, rightSubtree, m_root);
    }

    void ChunkTreap::RemoveElement(Chunk* t_chunk) {
        Node* leftSubtree = nullptr;
        Node* elementNode = nullptr;
        Node* rightSubtree = nullptr;

        SplitNodesByElement(m_root, leftSubtree, rightSubtree, t_chunk);
        SplitNodesByElement(rightSubtree, elementNode, rightSubtree, t_chunk + 1);
        MergeNodes(leftSubtree, rightSubtree, m_root);

        delete elementNode;
    }

    // TODO
    Chunk* ChunkTreap::FirstGreaterOrEqualThan(std::size_t desiredChunkSize) const {
        Node* currentNode = m_root;

        while (currentNode) {
            if (currentNode->chunk-> < desiredChunkSize) {
                currentNode = currentNode->rightChild;
            } else {
                if (currentNode->leftChild && currentNode->leftChild->chunk->GetSize() >= desiredChunkSize) {
                    currentNode = currentNode->leftChild;
                } else {
                    return currentNode->chunk;
                }
            }
        }

        return nullptr;
    }

    bool ChunkTreap::HasElement(const NumberType& t_element) const {
        return FirstGreaterOrEqualThan(t_element) == t_element;
    }

    void ChunkTreap::MergeNodes(Node* t_left, Node* t_right, Node*& t_root) {
        if (!t_left || !t_right) {
            root = t_left ? t_left : t_right;
            return;
        }

        if (t_left->priority > t_right->priority) {
            MergeNodes(t_left->rightChild, t_right, t_left->rightChild);
            root = t_left;
        } else {
            MergeNodes(t_left, t_right->leftChild, t_right->leftChild);
            root = t_right;
        }
    }

    void ChunkTreap::SplitNodesByElement(Node* t_root, Node*& t_left, 
                                         Node*& t_right, const NumberType& t_element)
    {
        if (!root) {
            left = right = nullptr;
            return;
        }

        if (root->element < element) {
            SplitNodesByElement(root->rightChild, root->rightChild, right, element);
            left = root;
        } else {
            SplitNodesByElement(root->leftChild, left, root->leftChild, element);
            right = root;
        }
    }
}