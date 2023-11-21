#include "mpplib/containers/chunk_treap.hpp"

namespace mpp {
    std::ostream& ChunkTreap::GenerateGraphvizLayout(std::ostream& t_out,
                                                     const std::string& t_treapName,
                                                     Node* t_root) const
    {
        PROFILE_FUNCTION();

        std::function<std::ostream&(Node*, std::ostream&)> DumpNode =
            [](Node* t_node, std::ostream& t_out) -> std::ostream& {
            t_out << " [label=\"chunk = " << reinterpret_cast<void*>(t_node->chunk) << "\n"
                  << "chunk.size = " << t_node->chunk->GetSize() << std::endl;
            t_out << "priority = " << t_node->priority << "\"];";
            return t_out;
        };

        std::function<void(Node*, uint32_t, std::ostream&)> GenerateNull =
            [&DumpNode](Node* t_node, uint32_t t_nullCount, std::ostream& t_out) {
                t_out << "    null" << t_nullCount << " [shape=point];" << std::endl;
                t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority);
                DumpNode(t_node, t_out) << std::endl;
                t_out << "    " << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority)
                      << " -> null" << t_nullCount << ";\n"
                      << std::endl;
            };

        std::function<void(Node*, std::ostream&)> GenerateRecursive =
            [&GenerateNull, &GenerateRecursive, &DumpNode](Node* t_node, std::ostream& t_out) {
                static uint32_t nullCount = 0;

                if (t_node->leftChild != nullptr) {
                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority);
                    DumpNode(t_node, t_out) << std::endl;

                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->leftChild->chunk) ^
                              t_node->leftChild->priority);
                    DumpNode(t_node->leftChild, t_out) << std::endl;

                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority)
                          << " -> "
                          << (reinterpret_cast<intptr_t>(t_node->leftChild->chunk) ^
                              t_node->leftChild->priority)
                          << ";\n"
                          << std::endl;
                    GenerateRecursive(t_node->leftChild, t_out);
                } else {
                    GenerateNull(t_node, nullCount++, t_out);
                }

                if (t_node->rightChild != nullptr) {
                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority);
                    DumpNode(t_node, t_out) << std::endl;

                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->rightChild->chunk) ^
                              t_node->rightChild->priority);
                    DumpNode(t_node->rightChild, t_out) << std::endl;

                    t_out << "    "
                          << (reinterpret_cast<intptr_t>(t_node->chunk) ^ t_node->priority)
                          << " -> "
                          << (reinterpret_cast<intptr_t>(t_node->rightChild->chunk) ^
                              t_node->rightChild->priority)
                          << ";\n"
                          << std::endl;
                    GenerateRecursive(t_node->rightChild, t_out);
                } else {
                    GenerateNull(t_node, nullCount++, t_out);
                }
            };

        t_out << "digraph " << t_treapName << " {\n";
        t_out << "    node [shape=rectangle]\n";

        Node* startRoot = (t_root == nullptr) ? m_root : t_root;

        if (startRoot == nullptr) {
            t_out << std::endl;
        } else if (startRoot->leftChild == nullptr && startRoot->rightChild == nullptr) {
            t_out << "    " << (reinterpret_cast<intptr_t>(startRoot->chunk) ^ startRoot->priority)
                  << " [label=\"chunk: " << reinterpret_cast<void*>(startRoot->chunk)
                  << "\npriority: " << startRoot->priority << "\"];" << std::endl;
        } else {
            GenerateRecursive(startRoot, t_out);
        }

        t_out << "}" << std::endl;

        return t_out;
    }
}