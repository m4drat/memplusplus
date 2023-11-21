#include "mpplib/containers/chunk_treap.hpp"

namespace mpp {

    ChunkTreap::ChunkTreap()
        : m_root{ nullptr }
        , m_freedChunks{ 0 }
        , m_freedMemory{ 0 }
    {
    }

    // @TODO: smart pointers memory management
    ChunkTreap::ChunkTreap(const ChunkTreap& t_treap)
        : m_root(new Node(*t_treap.m_root))
        , m_freedChunks{ t_treap.m_freedChunks }
        , m_freedMemory{ t_treap.m_freedMemory }
    {
    }

    ChunkTreap& ChunkTreap::operator=(const ChunkTreap& t_treap)
    {
        if (&t_treap == this)
            return *this;

        Delete();

        // TODO - smart pointers memory management
        m_root = new Node(*t_treap.m_root);
        m_freedChunks = t_treap.m_freedChunks;
        m_freedMemory = t_treap.m_freedMemory;

        return *this;
    }

    ChunkTreap::ChunkTreap(ChunkTreap&& t_treap) noexcept
        : m_root(t_treap.m_root)
        , m_freedChunks{ t_treap.m_freedChunks }
        , m_freedMemory{ t_treap.m_freedMemory }
    {
        t_treap.m_root = nullptr;
        t_treap.m_freedChunks = 0;
        t_treap.m_freedMemory = 0;
    }

    ChunkTreap& ChunkTreap::operator=(ChunkTreap&& t_treap) noexcept
    {
        if (&t_treap == this) {
            return *this;
        }

        Delete();

        m_root = t_treap.m_root;
        m_freedChunks = t_treap.m_freedChunks;
        m_freedMemory = t_treap.m_freedMemory;

        t_treap.m_root = nullptr;
        t_treap.m_freedChunks = 0;
        t_treap.m_freedMemory = 0;

        return *this;
    }

    ChunkTreap::~ChunkTreap()
    {
        Delete();
    }

    void ChunkTreap::Delete()
    {
        PROFILE_FUNCTION();
        Delete(m_root);
    }

    void ChunkTreap::Delete(Node* t_root)
    {
        if (t_root == nullptr) {
            return;
        }

        // Delete recursively each node
        Delete(t_root->leftChild);
        t_root->leftChild = nullptr;

        // Delete recursively each node
        Delete(t_root->rightChild);
        t_root->rightChild = nullptr;

        delete t_root;
        t_root = nullptr;
    }

    uint32_t ChunkTreap::TotalFreeChunks() const
    {
        return m_freedChunks;
    }

    std::size_t ChunkTreap::TotalFreeMemory() const
    {
        return m_freedMemory;
    }

    Chunk* ChunkTreap::MinSizeChunk() const
    {
        Node* currentNode = m_root;

        for (; currentNode->leftChild; currentNode = currentNode->leftChild)
            ;

        return currentNode->chunk;
    }

    Chunk* ChunkTreap::MaxSizeChunk() const
    {
        Node* currentNode = m_root;

        for (; currentNode->rightChild; currentNode = currentNode->rightChild)
            ;

        return currentNode->chunk;
    }

    void ChunkTreap::InsertChunk(Chunk* t_chunk)
    {
        m_freedChunks++;
        m_freedMemory += t_chunk->GetSize();

        // TODO - smart pointers memory management
        InsertNode(new Node(t_chunk));
    }

    void ChunkTreap::InsertNode(Node* t_node)
    {
        PROFILE_FUNCTION();

        Node* leftSubtree = nullptr;
        Node* rightSubtree = nullptr;

        // GenerateGraphvizLayout(std::cout, "root", m_root) << std::endl;
        SplitNodesByElement(m_root, leftSubtree, rightSubtree, t_node->chunk);
        // GenerateGraphvizLayout(std::cout, "leftSubtree", leftSubtree) << std::endl;
        // GenerateGraphvizLayout(std::cout, "rightSubtree", rightSubtree) << std::endl;
        MergeNodes(leftSubtree, t_node, leftSubtree);
        MergeNodes(leftSubtree, rightSubtree, m_root);
    }

    bool ChunkTreap::RemoveChunk(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();

        if (m_root == nullptr) {
            return false;
        }

        m_freedChunks--;
        m_freedMemory -= t_chunk->GetSize();

        Node* leftSubtree = nullptr;
        Node* rightSubtree = nullptr;

        SplitNodesByElement(m_root, leftSubtree, rightSubtree, t_chunk);

        Node* parent = rightSubtree;
        Node* nodeToRemove = rightSubtree;
        for (; nodeToRemove->leftChild;
             parent = nodeToRemove, nodeToRemove = nodeToRemove->leftChild)
            ;

        if (nodeToRemove == rightSubtree) {
            rightSubtree = nodeToRemove->rightChild;
        } else {
            parent->leftChild = nodeToRemove->rightChild;
        }
        nodeToRemove->rightChild = nullptr;

        delete nodeToRemove;
        nodeToRemove = nullptr;

        MergeNodes(leftSubtree, rightSubtree, m_root);

        return true;
    }

    Chunk* ChunkTreap::FirstGreaterOrEqualTo(std::size_t t_desiredChunkSize) const
    {
        PROFILE_FUNCTION();

        Node* currentNode = m_root;

        while (currentNode) {
            if (currentNode->chunk->GetSize() < t_desiredChunkSize) {
                currentNode = currentNode->rightChild;
            } else {
                if (currentNode->leftChild &&
                    currentNode->leftChild->chunk->GetSize() >= t_desiredChunkSize) {
                    currentNode = currentNode->leftChild;
                } else {
                    return currentNode->chunk;
                }
            }
        }

        return nullptr;
    }

    void ChunkTreap::MergeNodes(Node* t_left, Node* t_right, Node*& t_root)
    {
        if (!t_left || !t_right) {
            t_root = t_left ? t_left : t_right;
            return;
        }

        if (t_left->priority > t_right->priority) {
            MergeNodes(t_left->rightChild, t_right, t_left->rightChild);
            t_root = t_left;
        } else {
            MergeNodes(t_left, t_right->leftChild, t_right->leftChild);
            t_root = t_right;
        }
    }

    void ChunkTreap::SplitNodesByElement(Node* t_root,
                                         Node*& t_left,
                                         Node*& t_right,
                                         Chunk* t_chunk)
    {
        if (!t_root) {
            t_left = t_right = nullptr;
            return;
        }

        if ((t_root->chunk->GetSize() < t_chunk->GetSize()) ||
            ((t_root->chunk->GetSize() == t_chunk->GetSize()) && t_root->chunk < t_chunk)) {
            SplitNodesByElement(t_root->rightChild, t_root->rightChild, t_right, t_chunk);
            t_left = t_root;
        } else {
            SplitNodesByElement(t_root->leftChild, t_left, t_root->leftChild, t_chunk);
            t_right = t_root;
        }
    }
}