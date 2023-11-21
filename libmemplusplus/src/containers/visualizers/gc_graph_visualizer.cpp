#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/memory_manager.hpp"

namespace mpp {
    std::ostream& GcGraph::GenerateGraphvizLayoutSimple(std::ostream& t_out,
                                                        bool t_doNotDrawHeapConnections) const
    {
        PROFILE_FUNCTION();

        const std::string colorRed = "#fbb4ae";
        const std::string colorOrange = "#fed9a6";
        const std::string colorGreen = "#ccebc5";
        const std::string colorGray = "#cccccc";
        const std::string colorLightPurple = "#bcbddc";

        t_out << "digraph Objects {\n";
        t_out << "\tnode[ style=filled ];\n";

        // Create all chunks
        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\"" << chunkAddrStr << "\" [ fillcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                t_out << "\" label=\"chunk\\n"
                      << chunkAddrStr << "\\n"
                      << "size = " << currChunk->GetSize() << "\"];\n";
            }
        }

        // Draw connections between chunks
        for (auto* vtx1 : m_adjList) {
            // We don't want to draw GC pointers
            if (!vtx1->IsChunk())
                continue;

            // if current vertex has neighbors draw all connections
            // for each neighbor draw connection between vtx1 and its neighbour
            for (auto it = vtx1->GetNeighbors().begin(); it != vtx1->GetNeighbors().end(); ++it) {
                t_out << "\t\"" + vtx1->ToString() + "\""
                      << " -> "
                      << "\"" + (*it)->ToString() + "\";\n";
            }
        }

        if (t_doNotDrawHeapConnections) {
            t_out << "}";
            return t_out;
        }

        // Generate flat heap view
        t_out << "\tnode[ shape = none style = \"\" ];\n";
        t_out << "\theap[ label=<\n";
        t_out << "\t<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
        t_out << "\t\t<TR>\n";

        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\t\t"
                      << "<TD bgcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                constexpr uint32_t c_lsbNibbles = 5;

                t_out << "\" PORT=\"" << chunkAddrStr << "\">"
                      << chunkAddrStr.substr(chunkAddrStr.length() - c_lsbNibbles) << "</TD>"
                      << "\n";
            }
            t_out << "\t\t\t"
                  << "<TD>.....</TD>"
                  << "\n";
        }

        t_out << "\t\t</TR>\n";
        t_out << "\t</table>>];\n";

        // Draw connection to the flat heap view
        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                std::string chunkAddrStr = utils::AddrToString((void*)pos);
                t_out << "\t\"" << chunkAddrStr << "\" -> heap:\"" << chunkAddrStr
                      << "\" [style=dashed, color=\"" << colorLightPurple << "\"];\n";
            }
        }

        t_out << "}";

        return t_out;
    }

    std::ostream& GcGraph::GenerateGraphvizLayoutAdvanced(std::ostream& t_out) const // NOLINT
    {
        PROFILE_FUNCTION();

        const std::string colorRed = "#fbb4ae";
        const std::string colorOrange = "#fed9a6";
        const std::string colorGreen = "#ccebc5";
        const std::string colorGray = "#cccccc";
        const std::string colorLightPurple = "#bcbddc";

        t_out << "digraph Objects {\n";
        t_out << "\tcompound=true;\n";
        t_out << "\tratio=expand;\n";
        t_out << "\tgraph [ranksep=1.5]\n";
        t_out << "\tnewrank=true;\n\n";

        // Generate flat heap view
        t_out << "\t// Draw flat heap layout\n";
        t_out << "\theap[ shape = none style = \"\" ];\n";
        t_out << "\theap[ label=<\n";
        t_out << "\t<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
        t_out << "\t\t<TR>\n";

        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                t_out << "\t\t\t"
                      << "<TD bgcolor=\"";

                if (arena->TopChunk() == currChunk) {
                    t_out << colorOrange;
                } else if (currChunk->IsUsed()) {
                    t_out << colorGreen;
                } else {
                    t_out << colorRed;
                }

                constexpr uint32_t c_lsbNibbles = 5;

                t_out << "\" PORT=\"" << chunkAddrStr << "\">"
                      << chunkAddrStr.substr(chunkAddrStr.length() - c_lsbNibbles) << "</TD>"
                      << "\n";
            }
            t_out << "\t\t\t"
                  << "<TD>.....</TD>"
                  << "\n";
        }

        t_out << "\t\t</TR>\n";
        t_out << "\t</table>>];\n\n";

        t_out << "\t// Draw all chunks (begin)\n";
        t_out << "\tnode[ style=\"filled\" ];\n";

        std::set<GcPtr*> nonHeapGcPtrs = m_memoryManager.GetGC().GetOrderedGcPtrs();
        std::set<GcPtr*> orderedGcPtrs = nonHeapGcPtrs;

        uint32_t gcptrIndex = 1;

        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);
                std::string chunkLabel = "label=\"chunk\\n" + chunkAddrStr + "\\n" +
                                         "size = " + std::to_string(currChunk->GetSize()) + "\"";
                std::string chunkColor;

                if (arena->TopChunk() == currChunk) {
                    chunkColor = colorOrange;
                } else if (currChunk->IsUsed()) {
                    chunkColor = colorGreen;
                } else {
                    chunkColor = colorRed;
                }

                auto* chunkAsVertex = FindVertex(currChunk);
                if (!chunkAsVertex || chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()) {
                    // Current chunk doesn't have GC-pointers inside
                    t_out << "\t\"" << chunkAddrStr << "\" [fillcolor=\"" << chunkColor << "\", "
                          << chunkLabel << "];\n";
                } else {
                    // Current chunk does have GC-pointers inside
                    t_out << "\tsubgraph \"cluster-" << chunkAddrStr << "\" {\n";
                    t_out << "\t\trank=same;\n";
                    t_out << "\t\t" << chunkLabel << ";\n";
                    t_out << "\t\tstyle=\"rounded,filled\";\n";
                    t_out << "\t\tfillcolor=\"" << chunkColor << "\";\n";
                    t_out << "\t\tsubgraph \"cluster\" {\n";
                    t_out << "\t\t\tstyle=\"dashed\";\n";
                    t_out << "\t\t\tlabel=\"\";\n";

                    for (auto* gcPtr : chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs)) {
                        nonHeapGcPtrs.erase(gcPtr);
                        // std::cout << "Vertex: [" << chunkAsVertex << "] -> Chunk: [" <<
                        // chunkAddrStr
                        //           << "] -> GcPtr: " << utils::AddrToString(gcPtr->GetVoid())
                        //           << std::endl;
                        std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
                        t_out << "\t\t\t\"" << gcPtrAddrStr
                              << "\" [style=\"filled,dashed\", fillcolor=\"" << chunkColor
                              << "\", shape=box, label=\"gcptr-" << gcptrIndex++ << "\"];\n";
                    }

                    t_out << "\t\t}\n";
                    t_out << "\t}\n";
                }

                if (!chunkAsVertex)
                    continue;

                // Draw connections between GC-pointers and chunks
                t_out << "\n\t// Draw connections between GC-pointers from current chunk "
                      << chunkAddrStr << " and chunks\n";
                for (auto* gcPtr : chunkAsVertex->GetAllOutgoingGcPtrs(orderedGcPtrs)) {
                    std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
                    Chunk* pointsToChunk = m_gc.FindChunkInUse(gcPtr->GetVoid());
                    Vertex* pointsToVertex = FindVertex(pointsToChunk);
                    bool pointsToCluster =
                        (pointsToVertex && pointsToVertex->GetLocationAsAChunk())
                            ? !pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                            : false;

                    t_out
                        << "\t\"" << gcPtrAddrStr << "\":s -> \""
                        << ((pointsToCluster)
                                ? utils::AddrToString(
                                      *pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                                : utils::AddrToString(pointsToChunk))
                        << "\"";

                    if (pointsToCluster) {
                        t_out << " [lhead=\"cluster-" << utils::AddrToString(pointsToChunk)
                              << "\"]";
                    }

                    t_out << ";\n";
                }
            }
        }

        t_out << "\t// Draw all chunks (end)\n";

        // Draw GC-pointers that are not on the heap
        t_out << "\n\t// Draw connections between non-heap GC-pointers and chunks\n";
        for (auto* gcPtr : nonHeapGcPtrs) {
            std::string gcPtrAddrStr = utils::AddrToString((void*)gcPtr);
            Chunk* pointsToChunk = m_gc.FindChunkInUse(gcPtr->GetVoid());
            Vertex* pointsToVertex = FindVertex(pointsToChunk);
            bool pointsToCluster =
                (pointsToVertex && pointsToVertex->GetLoc())
                    ? !pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                    : false;

            t_out << "\t\"" << gcPtrAddrStr << "\" [style=filled, fillcolor=\"" << colorGray
                  << "\", shape=rect, label=\"gcptr-" << gcptrIndex++ << "\"];\n";

            // Draw connections between non-heap GC-pointers and chunks
            t_out << "\t\"" << gcPtrAddrStr << "\":s -> \""
                  << ((pointsToCluster)
                          ? utils::AddrToString(
                                *pointsToVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                          : utils::AddrToString(pointsToChunk))
                  << "\"";

            if (pointsToCluster) {
                t_out << " [lhead=\"cluster-" << utils::AddrToString(pointsToChunk) << "\"]";
            }

            t_out << ";\n";
        }

        // Draw connection to the flat heap view
        t_out << "\n\t// Draw connections from all chunks to the flat heap view\n";
        for (auto& arena : m_memoryManager.GetArenaList()) {
            for (std::byte* pos = arena->BeginPtr(); pos < arena->EndPtr();
                 pos += reinterpret_cast<Chunk*>(pos)->GetSize()) {
                auto* currChunk = reinterpret_cast<Chunk*>(pos);
                std::string chunkAddrStr = utils::AddrToString((void*)currChunk);

                Vertex* chunkVertex = FindVertex(currChunk);
                bool isCluster = (chunkVertex)
                                     ? !chunkVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).empty()
                                     : false;

                t_out << "\t\""
                      << ((isCluster)
                              ? utils::AddrToString(
                                    *chunkVertex->GetAllOutgoingGcPtrs(orderedGcPtrs).begin())
                              : utils::AddrToString(currChunk))
                      << "\" -> heap:\"" << chunkAddrStr << "\"";

                if (isCluster) {
                    t_out << " [ltail=\"cluster-" << chunkAddrStr << "\", style=dashed, color=\""
                          << colorLightPurple << "\"]";
                } else {
                    t_out << " [style=dashed, color=\"" << colorLightPurple << "\"]";
                }

                t_out << ";\n";
            }
        }

        t_out << "}";

        return t_out;
    }
}