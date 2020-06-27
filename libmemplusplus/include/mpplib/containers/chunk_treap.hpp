#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/node.hpp"

#include <iostream>

namespace mpp {
    /**
     * @brief ChunkTreap (CTreap) - Container class, that provides easy way of
     * inserting/finding freed chunks in arena.
     *
     * Data structure itself is a treap (tree + heap). Provides easy way to work with
     * chunks. Complexity (in general): Insert: O(logn) Remove: O(logn) Find[min/max]:
     * O(logn)
     */
    class ChunkTreap final
    {
    public:
        /**
         * @brief Constructs empty chunk treap.
         *
         * Root node is nullptr.
         */
        ChunkTreap();

        // copy/assign
        ChunkTreap(const ChunkTreap& t_treap);
        ChunkTreap& operator=(const ChunkTreap& t_treap);
        ChunkTreap(ChunkTreap&& t_treap);
        ChunkTreap& operator=(ChunkTreap&& t_treap);

        /**
         * @brief Destructs chunk treap.
         */
        ~ChunkTreap();

        /**
         * @brief Finds min freed chunk in chunk treap in logN.
         * @return chunk of minimum size
         */
        Chunk* MinSizeChunk() const;
        /**
         * @brief Finds max freed chunk in chunk treap in logN.
         * @return chunk of maximum size
         */
        Chunk* MaxSizeChunk() const;

        /**
         * @brief Inserts new chunk in chunk treap in logN.
         * @param t_chunk the chunk to insert
         */
        void InsertChunk(Chunk* t_chunk);
        /**
         * @brief Remove chunk from chunk treap in logN.
         * @param t_chunk the chunk to remove
         */
        void RemoveChunk(Chunk* t_chunk);

        /**
         * @brief Finds first chunk that size is greater or equal, to desiredSize.
         * @param t_desiredChunkSize desired chunk size
         * @return Found chunk of suitable size or nullptr
         */
        Chunk* FirstGreaterOrEqualThan(std::size_t t_desiredChunkSize) const;

        /**
         * @brief Get root node.
         * @return root node
         */
        Node* GetRootNode()
        {
            return m_root;
        }

        /**
         * @brief Chunk treap deleteion logic.
         */
        void Delete();

    private:
        /**
         * @brief Chunk treap root node.
         */
        Node* m_root;

        /**
         * @brief Inserts new node into ctreap.
         * @param t_node node to insert into chunk treap
         */
        void InsertNode(Node* t_node);

        /**
         * @brief Сombines two subtrees t_left and t_right and returns the new tree.
         * @param t_left left subtree to merge
         * @param t_right right subtree to merge
         * @param t_root[out] new tree root
         */
        static void MergeNodes(Node* t_left, Node* t_right, Node*& t_root);
        /**
         * @brief Separates tree into two subtrees by t_chunk.
         * @param t_root root, from which we shoul start splitting
         * @param t_chunk chunk to split by
         * @param[out] t_left left subtree
         * @param[out] t_right right subtree
         */
        static void SplitNodesByElement(Node* t_root,
                                        Node*& t_left,
                                        Node*& t_right,
                                        Chunk* t_chunk);
    };
}