#pragma once

#include "mpplib/utils/utils.hpp"

#include <iostream>

#if defined MPP_SANITIZERS
#include <sanitizer/asan_interface.h>
#endif

#if defined MPP_VALGRIND
#include <memcheck.h>
#include <valgrind.h>
#endif

namespace mpp {
#define MPP_STRINGIFY(x) #x
#define MPP_TO_STRING(x) MPP_STRINGIFY(x)

#define PRIVATE_MPP_ASSERT(expr, msg)                                                              \
    ((expr) ? (void)0                                                                              \
            : mpp::utils::ErrorAbort("Assertation " #expr " failed in: " __FILE__                  \
                                     ":" MPP_TO_STRING(__LINE__) "\n"))

#if MPP_DEBUG == 1
#define MPP_DEBUG_ASSERT(expr, msg) PRIVATE_MPP_ASSERT((expr), (msg))
#else
#define MPP_DEBUG_ASSERT(expr, msg)
#endif

#define MPP_RELEASE_ASSERT(expr, msg) PRIVATE_MPP_ASSERT((expr), (msg))

#if MPP_DEBUG == 1 || MPP_ENABLE_LOGGING == 1
#define MPP_LOG(level, msg)                                                                        \
    std::cout << level << " " << __FILE__ << ":" << __LINE__ << " > " << msg << std::endl;
#define MPP_LOG_DBG(msg) MPP_LOG("❓  DBG:", msg)
#define MPP_LOG_WARN(msg) MPP_LOG("🚧 WARN:", msg)
#define MPP_LOG_INFO(msg) MPP_LOG("📘 INFO:", msg)
#define MPP_LOG_ERROR(msg) MPP_LOG("❌  ERR:", msg)
#else
#define MPP_LOG(level, msg)
#define MPP_LOG_DBG(msg)
#define MPP_LOG_WARN(msg)
#define MPP_LOG_INFO(msg)
#define MPP_LOG_ERROR(msg)
#endif

#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
#define MPP_SECURE_MEMSET(ptr, value, size)                                                        \
    do {                                                                                           \
        MPP_DEBUG_ASSERT(ptr != nullptr, "Null pointer");                                          \
        MPP_DEBUG_ASSERT(size > 0, "Size must be greater than 0");                                 \
        utils::SecureMemset(ptr, size, value, size);                                               \
    } while (0)
#else
#define MPP_SECURE_MEMSET(ptr, value, size)
#endif

#if MPP_FULL_DEBUG == 1 || MPP_SECURE == 1
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

#if defined MPP_VALGRIND
#define MPP_RUNNING_ON_VALGRIND (RUNNING_ON_VALGRIND)
#define MPP_VALGRIND_MALLOCLIKE_BLOCK(ptr, size)                                                   \
    VALGRIND_MALLOCLIKE_BLOCK((ptr), (size), 0, 0);                                        // NOLINT
#define MPP_VALGRIND_FREELIKE_BLOCK(ptr) VALGRIND_FREELIKE_BLOCK((ptr), 0);                // NOLINT
#define MPP_VALGRIND_MAKE_MEM_DEFINED(ptr, size) VALGRIND_MAKE_MEM_DEFINED((ptr), (size)); // NOLINT
#define MPP_VALGRIND_MAKE_MEM_UNDEFINED(ptr, size)                                                 \
    VALGRIND_MAKE_MEM_UNDEFINED((ptr), (size)); // NOLINT
#define MPP_VALGRIND_DEFINE_CHUNK_HEADER(chunk)                                                    \
    MPP_VALGRIND_MAKE_MEM_DEFINED((chunk), sizeof(Chunk::ChunkHeader));
#define MPP_VALGRIND_DEFINE_CHUNK(chunk)                                                           \
    do {                                                                                           \
        MPP_VALGRIND_MALLOCLIKE_BLOCK(chunk, (chunk)->GetSize());                                  \
        MPP_VALGRIND_DEFINE_CHUNK_HEADER(chunk);                                                   \
        MPP_VALGRIND_MAKE_MEM_UNDEFINED(Chunk::GetUserDataPtr(chunk),                              \
                                        (chunk)->GetSize() - sizeof(Chunk::ChunkHeader));          \
    } while (0)
#define MPP_VALGRIND_UNDEFINE_CHUNK(chunk)                                                         \
    do {                                                                                           \
        MPP_VALGRIND_FREELIKE_BLOCK(chunk);                                                        \
        MPP_VALGRIND_DEFINE_CHUNK_HEADER(chunk);                                                   \
    } while (0)
#else
#define MPP_RUNNING_ON_VALGRIND (0)
#define MPP_VALGRIND_MALLOCLIKE_BLOCK(ptr, size)
#define MPP_VALGRIND_FREELIKE_BLOCK(ptr)
#define MPP_VALGRIND_MAKE_MEM_DEFINED(ptr, size)
#define MPP_VALGRIND_MAKE_MEM_UNDEFINED(ptr, size)
#define MPP_VALGRIND_DEFINE_CHUNK_HEADER(chunk)
#define MPP_VALGRIND_DEFINE_CHUNK(chunk)
#define MPP_VALGRIND_UNDEFINE_CHUNK(chunk)
#endif
}