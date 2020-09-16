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

std::ostream& ChunkTreap::GenerateGraphvizLayout(std::ostream& t_out) const
{
    PROFILE_FUNCTION();

    std::function<std::ostream&(Node*, std::ostream&)> DumpNode = [](Node* t_node, std::ostream& t_out) -> std::ostream&
    {
        t_out << " [label=\"chunk = " << reinterpret_cast<void*>(t_node->chunk) << "\n" << "chunk.size = " << t_node->chunk->GetSize() << std::endl; 
        t_out << "priority = " << t_node->priority << "\"];";
        return t_out;
    };

    std::function<void(Node*, uint32_t, std::ostream&)> GenerateNull = [&DumpNode](Node* t_node, uint32_t t_nullCount, std::ostream& t_out)
    {
        t_out << "    null" << t_nullCount << " [shape=point];" << std::endl;
        t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority); 
        DumpNode(t_node, t_out) << std::endl;
        t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority) << " -> null" << t_nullCount << ";\n" << std::endl;
    };

    std::function<void(Node*, std::ostream&)> GenerateRecursive = [&GenerateNull, &GenerateRecursive, &DumpNode](Node* t_node, std::ostream& t_out)
    {
        static uint32_t nullCount = 0;

        if (t_node->leftChild != nullptr)
        {
            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority);
            DumpNode(t_node, t_out) << std::endl;
            
            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->leftChild->chunk) ^ t_node->leftChild->priority);
            DumpNode(t_node->leftChild, t_out) << std::endl;

            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority) << " -> " << (reinterpret_cast<intptr_t>(t_node->leftChild->chunk) ^ t_node->leftChild->priority) << ";\n" << std::endl;
            GenerateRecursive(t_node->leftChild, t_out);
        } else {
            GenerateNull(t_node, nullCount++, t_out);
        }

        if (t_node->rightChild != nullptr)
        {
            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority);
            DumpNode(t_node, t_out) << std::endl;

            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->rightChild->chunk) ^ t_node->rightChild->priority);
            DumpNode(t_node->rightChild, t_out) << std::endl;

            t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority) << " -> " << (reinterpret_cast<intptr_t>(t_node->rightChild->chunk) ^ t_node->rightChild->priority) << ";\n" << std::endl;
            GenerateRecursive(t_node->rightChild, t_out);
        } else {
            GenerateNull(t_node, nullCount++, t_out);
        }
    };

    t_out << "digraph Treap {\n";
    t_out << "    node [shape=rectangle]";

    if (m_root == nullptr)
    {
        t_out << std::endl;
    } 
    else if (m_root->leftChild == nullptr && m_root->rightChild == nullptr)
    {
        t_out << "    " << (reinterpret_cast<intptr_t>(m_root->chunk) ^ m_root->priority) 
              << " [label=\"chunk: " << reinterpret_cast<void*>(m_root->chunk) << "\npriority: " << m_root->priority << "\"];" << std::endl;
    }
    else 
    {
        GenerateRecursive(m_root, t_out);
    }

    t_out << "}" << std::endl;

    return t_out;
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
    for (; nodeToRemove->leftChild; parent = nodeToRemove, nodeToRemove = nodeToRemove->leftChild)
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

void ChunkTreap::SplitNodesByElement(Node* t_root, Node*& t_left, Node*& t_right, Chunk* t_chunk)
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