#pragma once

#include <cstdint>
#include <set>

#include "mpplib/shared_gcptr.hpp"

namespace mpp { namespace fuzzer {
    constexpr uint32_t c_maxPointers = 32;
    constexpr uint32_t c_maxPointersInAVertex = 16;

    class Vertex
    {
    private:
        std::array<SharedGcPtr<Vertex>, c_maxPointersInAVertex> m_gcs;
        uint64_t m_data;

    public:
        Vertex()
            : m_data(0x13371337deadbeef)
        {
        }

        void AddPointerAtIndex(uint32_t t_idx, const SharedGcPtr<Vertex>& t_ptr)
        {
            m_gcs.at(t_idx) = t_ptr;
        }

        uint64_t& GetData()
        {
            return m_data;
        }
    };
}}