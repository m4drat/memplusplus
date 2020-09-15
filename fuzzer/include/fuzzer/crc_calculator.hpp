#pragma once

#include <cstdint>

namespace mpp { namespace fuzzer {

    uint32_t CRC32(const uint8_t *buf, std::size_t len)
    {
        uint32_t val, crc;
        uint8_t i;

        crc = 0xFFFFFFFF;
        while(len--)
        {
            val=(crc ^ *buf++) & 0xFF;
            for(i = 0; i < 8; i++){
                val = val & 1 ? (val >> 1) ^ 0xEDB88320 : val >> 1;
            }
            crc = val ^ crc >> 8;
        }
        return crc ^ 0xFFFFFFFF;
    }
}}