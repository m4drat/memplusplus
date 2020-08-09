#include "mpplib/containers/chunk_treap.hpp"

namespace mpp {

    ChunkTreap::ChunkTreap()
        : m_root{ nullptr }
        , m_freedChunks{ 0 }
        , m_freedMemory{ 0 }
    {}

    // TODO - smart pointers memory managment
    ChunkTreap::ChunkTreap(const ChunkTreap& t_treap)
        : m_root(new Node(*t_treap.m_root))
    {}

    ChunkTreap& ChunkTreap::operator=(const ChunkTreap& t_treap)
    {
        if (&t_treap == this)
            return *this;

        Delete();

        // TODO - smart pointers memory managment
        m_root = new Node(*t_treap.m_root);

        return *this;
    }

    ChunkTreap::ChunkTreap(ChunkTreap&& t_treap)
        : m_root(t_treap.m_root)
    {
        t_treap.m_root = nullptr;
    }

    ChunkTreap& ChunkTreap::operator=(ChunkTreap&& t_treap)
    {
        if (&t_treap == this)
            return *this;

        Delete();

        m_root = t_treap.m_root;
        t_treap.m_root = nullptr;

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
        if (t_root == nullptr)
            return;

        // Delete recursively each node
        Delete(t_root->leftChild);
        t_root->leftChild = nullptr;

        // Delete recursively each node
        Delete(t_root->rightChild);
        t_root->rightChild = nullptr;

        delete t_root;
        t_root = nullptr;
    }

    uint32_t ChunkTreap::GetFreedChunksSize()
    {
        return m_freedChunks;
    }

    std::size_t ChunkTreap::GetAmountOfFreedMemory()
    {
        return m_freedMemory;
    }

    // TODO
    // https://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
    // std::ostream& ChunkTreap::GenerateGraphvizLayout(std::ostream& t_out) const
    // {
    //     t_out << "digraph Objects {\n";
    //     for (auto v1 : m_adjList) {
    //         t_out << "\t\"" + v1->ToString() + "\"";
    //         if (v1->GetNeighbors().size() != 0)
    //             t_out << " -> ";

    //         for (auto it = v1->GetNeighbors().begin() ; it != v1->GetNeighbors().end();
    //         ++it) {
    //             if (auto tmpIt = it; (++tmpIt) == v1->GetNeighbors().end())
    //                 t_out << "\"" + (*it)->ToString() + "\"";
    //             else
    //                 t_out << "\"" + (*it)->ToString() + "\"" + " -> ";
    //         }

    //         t_out << ";\n";
    //     }

    //     t_out << "}";

    //     return t_out;
    // }

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

        // TODO - smart pointers memory managment
        InsertNode(new Node(t_chunk));
    }

    void ChunkTreap::InsertNode(Node* t_node)
    {
        PROFILE_FUNCTION();
        Node* leftSubtree = nullptr;
        Node* rightSubtree = nullptr;

        SplitNodesByElement(m_root, leftSubtree, rightSubtree, t_node->chunk);
        MergeNodes(leftSubtree, t_node, leftSubtree);
        MergeNodes(leftSubtree, rightSubtree, m_root);
    }

    void ChunkTreap::RemoveChunk(Chunk* t_chunk)
    {
        PROFILE_FUNCTION();
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
    }

    Chunk* ChunkTreap::FirstGreaterOrEqualThan(std::size_t desiredChunkSize) const
    {
        PROFILE_FUNCTION();
        Node* currentNode = m_root;

        while (currentNode) {
            if (currentNode->chunk->GetSize() < desiredChunkSize) {
                currentNode = currentNode->rightChild;
            } else {
                if (currentNode->leftChild &&
                    currentNode->leftChild->chunk->GetSize() >= desiredChunkSize) {
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