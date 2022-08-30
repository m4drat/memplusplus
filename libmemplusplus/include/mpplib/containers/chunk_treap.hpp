#pragma once

#include "mpplib/chunk.hpp"
#include "mpplib/containers/node.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

#include <functional>
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
        // TODO
        /**
         * @brief Implements iteration logic for ChunkTreap.
         */
        struct Iterator
        {};

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
         * @warning Chunk must be in chunk treap! Otherwise this function segfaults.
         * @param t_chunk the chunk to remove
         * @return true if chunk was removed, false otherwise
         */
        bool RemoveChunk(Chunk* t_chunk);

        /**
         * @brief Finds first chunk that size is greater or equal, to desiredSize.
         * @param t_desiredChunkSize desired chunk size
         * @return Found chunk of suitable size or nullptr
         */
        Chunk* FirstGreaterOrEqualTo(std::size_t t_desiredChunkSize) const;

        /**
         * @brief Get root node.
         * @return root node
         */
        Node* GetRootNode()
        {
            return m_root;
        }

        /**
         * @brief Wrapper around Delete(Node* t_root), to delete from the root.
         * @sa Delete(Node* t_root)
         */
        void Delete();

        /**
         * @brief Delete all nodes starting from t_root.
         */
        void Delete(Node* t_root);

        /**
         * @brief Get number of nodes (aka freed chunks).
         * @return uint32_t number of freed chunks.
         */
        uint32_t TotalFreeChunks();

        /**
         * @brief Get the amount of total memory held by chunks
         * inside chunk treap
         * @return std::size_t total amount of freed memory
         */
        std::size_t TotalFreeMemory();

        /**
         * @brief Generates tree representation in form, that can be used in dot
         * (graphviz), to visualize tree structure. As inspiration i've used this article:
         * https://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
         *
         * @param t_out std::ostream& to write to
         * @param t_treapName std::string - name of digraph
         * @param t_root root, to start from, if parameter is nullptr, dump whole
         * tree starting from m_root.
         * @return std::ostream that was passed as parameter
         */
        std::ostream& GenerateGraphvizLayout(std::ostream& t_out,
                                             std::string t_treapName = "Treap",
                                             Node* t_root = nullptr) const;

    private:
        /**
         * @brief Chunk treap root node.
         */
        Node* m_root;

        /**
         * @brief Keeps track of amount of freed chunks.
         */
        uint32_t m_freedChunks;

        /**
         * @brief keeps track of total amount
         * of freed memory inside ChunkTreap
         */
        std::size_t m_freedMemory;

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
         * @param t_root root, from which we should start splitting
         * @param[out] t_left left subtree
         * @param[out] t_right right subtree
         * @param t_chunk chunk to split by
         */
        static void SplitNodesByElement(Node* t_root,
                                        Node*& t_left,
                                        Node*& t_right,
                                        Chunk* t_chunk);
    };
}