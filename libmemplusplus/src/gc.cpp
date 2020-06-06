#include "mpplib/gc.hpp"

// struct Node
// {
//     std::vector<GcPtr*> currentChunkGcPtrs;
// }


// | | | |

// |X|0|1|2|
// |0| | | |
// |1| | | |
// |2| | | |

namespace mpp {
    std::vector<GcPtr*> GC::s_activeGcPtrs;
    std::size_t s_garbageSize = 0;
    std::size_t s_dataSize = 0;
    GcGraph m_objectsGraph(); // Initialize empty graph

    bool GC::Collect()
    {
        std::cout << "======================" << std::endl;
        for (GcPtr* gcPtr : s_activeGcPtrs)
        {
            std::cout << "GcPtr: " << (void*)gcPtr << std::endl;
            std::cout << "Ptr:   " << gcPtr->GetVoid() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
}