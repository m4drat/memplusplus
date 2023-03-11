#include "mpplib/utils/utils.hpp"

#include <cstdio>
#if MPP_DEBUG == 1
#include <cxxabi.h> // for __cxa_demangle
#include <dlfcn.h>  // for dladdr
#endif
#include <exception>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#define __STDC_WANT_LIB_EXT1__ 1
#include <cstdlib>
#include <string.h> // for memset_s

namespace mpp { namespace utils {

    void* SecureMemset(void* t_pointer,
                       size_t t_targetBufferSize,
                       unsigned char t_fillChar,
                       size_t t_sizeToRemove)
    {
#ifdef __STDC_LIB_EXT1__
        memset_s(pointer, size_data, t_fillChar, size_to_remove);
#else
        if (t_sizeToRemove > t_targetBufferSize)
            t_sizeToRemove = t_targetBufferSize;
        volatile unsigned char* dataPtr = static_cast<unsigned char*>(t_pointer);
        while ((t_sizeToRemove--) != 0u) {
            *dataPtr++ = t_fillChar;
        }
#endif
        return t_pointer;
    }

#if MPP_DEBUG == 1
    void DumpStackTrace(std::ostream& t_out, int32_t t_skip)
    {
        std::array<void*, s_MAX_STACK_LEVELS> callstack{};
        std::array<char, 2048> buf{}; // NOLINT
        int32_t frames = backtrace(callstack.data(), s_MAX_STACK_LEVELS);
        char** symbols = backtrace_symbols(callstack.data(), frames);

        for (int32_t i = t_skip; i < frames; ++i) {
            Dl_info info;
            if (dladdr(callstack.at(i), &info)) {
                char* demangled = NULL;
                int32_t status = 0;
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, nullptr, &status);
                // NOLINTNEXTLINE
                std::snprintf(buf.data(),
                              sizeof(buf),
                              "%3d: %p - %s + %zd\n",
                              i,
                              callstack.at(i),
                              status == 0 ? demangled : info.dli_sname,
                              reinterpret_cast<char*>(callstack.at(i)) -
                                  reinterpret_cast<char*>(info.dli_saddr));
                free(demangled); // NOLINT
            } else {
                // NOLINTNEXTLINE
                std::snprintf(buf.data(), sizeof(buf), "%-3d %p\n", i,
                              callstack.at(i)); // NOLINT
            }
            t_out << buf.data();
            // NOLINTNEXTLINE
            std::snprintf(buf.data(),
                          sizeof(buf),
                          "%*sat %s\n",
                          static_cast<int>((2 + sizeof(void*)) + 9), // NOLINT
                          "",
                          symbols[i]);
            t_out << buf.data();
        }

        if (frames == s_MAX_STACK_LEVELS) {
            t_out << "[truncated]\n";
        }

        free(symbols); // NOLINT
    }
#endif

    void ErrorAbort(const std::string& t_message)
    {
        // Print error message
        std::cerr << t_message;

#if MPP_DEBUG == 1
        // Dump stacktrace in debug
        DumpStackTrace(std::cerr);
#endif
        // terminate the program using default terminate handler
        std::terminate();
    }

    std::string AddrToString(void* t_ptr)
    {
        std::stringstream addrToStrSS;
        addrToStrSS << static_cast<const void*>(t_ptr);
        return addrToStrSS.str();
    }
}}