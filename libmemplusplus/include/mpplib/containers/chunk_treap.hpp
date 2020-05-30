#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/node.hpp"

#include <iostream>

namespace mpp {
    class ChunkTreap final
    {
    public:
        // default constructor
        ChunkTreap();

        // copy/assign
        ChunkTreap(const ChunkTreap& t_treap);
        ChunkTreap& operator=(const ChunkTreap& t_treap);
        ChunkTreap(ChunkTreap&& t_treap);
        ChunkTreap& operator=(ChunkTreap&& t_treap);

        // destructor
        ~ChunkTreap();

        Chunk* MinSizeChunk() const;
        Chunk* MaxSizeChunk() const;

        // template<class... Args>
        // void EmplaceChunk(Args&&... t_arguments);

        void InsertChunk(Chunk* t_chunk);
        // void InsertChunk(NumberType&& t_element);

        void RemoveChunk(Chunk* t_chunk);

        Chunk* FirstGreaterOrEqualThan(std::size_t t_desiredChunkSize) const;

        Node* GetRootNode()
        {
            return m_root;
        }

    private:
        Node* m_root;

        void Delete();

        void InsertNode(Node* t_node);

        static void MergeNodes(Node* t_left, Node* t_right, Node*& t_root);
        static void SplitNodesByElement(Node* t_root,
                                        Node*& t_left,
                                        Node*& t_right,
                                        Chunk* t_chunk);
    };
}