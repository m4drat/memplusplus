#pragma once

#include "mpplib/utils/utils.hpp"
#include <iostream>
#include <sanitizer/asan_interface.h>

namespace mpp {
#define MPP_STRINGIFY(x) #x
#define MPP_TO_STRING(x) MPP_STRINGIFY(x)

#define PRIVATE__MPP_ASSERT(expr, msg)                                                             \
    ((expr) ? (void)0                                                                              \
            : mpp::utils::ErrorAbort("Assertation " #expr " failed in: " __FILE__                  \
                                     ":" MPP_TO_STRING(__LINE__) "\n"))

#ifdef MPP_DEBUG
#define MPP_ASSERT(expr, msg) PRIVATE__MPP_ASSERT((expr), (msg))
#else
#define MPP_ASSERT(expr, msg)
#endif

#define MPP_RELEASE_ASSERT(expr, msg) PRIVATE__MPP_ASSERT((expr), (msg))

#if defined MPP_FULL_DEBUG || defined MPP_SECURE
#define MPP_SECURE_MEMSET(ptr, value, size)                                                        \
    do {                                                                                           \
        MPP_ASSERT(ptr != nullptr, "Null pointer");                                                \
        MPP_ASSERT(size > 0, "Size must be greater than 0");                                       \
        std::memset(ptr, value, size);                                                             \
    } while (0)
#else
#define MPP_SECURE_MEMSET(ptr, value, size)
#endif

#if defined MPP_FULL_DEBUG || defined MPP_SECURE
#define MPP_SECURE_WIPE_CHUNK(chunk)                                                               \
    do {                                                                                           \
        MPP_SECURE_MEMSET(Chunk::GetUserDataPtr(chunk),                                            \
                          MPP_FILL_CHAR,                                                           \
                          chunk->GetSize() - sizeof(Chunk::ChunkHeader));                          \
    } while (0)
#else
#define MPP_SECURE_WIPE_CHUNK(chunk)
#endif

#if defined MPP_SANITIZERS
#define MPP_UNPOISON_MEM(ptr, size) ASAN_UNPOISON_MEMORY_REGION(ptr, size);
#define MPP_POISON_MEM(ptr, size) ASAN_POISON_MEMORY_REGION(ptr, size);
#define MPP_UNPOISON_USER_DATA_INSIDE_CHUNK(chunk)                                                 \
    MPP_UNPOISON_MEM(Chunk::GetUserDataPtr(chunk), chunk->GetSize() - sizeof(Chunk::ChunkHeader));
#define MPP_POISON_USER_DATA_INSIDE_CHUNK(chunk)                                                   \
    MPP_POISON_MEM(Chunk::GetUserDataPtr(chunk), chunk->GetSize() - sizeof(Chunk::ChunkHeader));
#else
#define MPP_UNPOISON_MEM(ptr, size)
#define MPP_POISON_MEM(ptr, size)
#define MPP_UNPOISON_USER_DATA_INSIDE_CHUNK(chunk)
#define MPP_POISON_USER_DATA_INSIDE_CHUNK(chunk)
#endif
}