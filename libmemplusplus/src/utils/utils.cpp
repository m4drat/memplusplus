#include "mpplib/utils/utils.hpp"

#include <cstdio>
#include <cxxabi.h> // for __cxa_demangle
#include <dlfcn.h>  // for dladdr
#include <exception>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

namespace mpp { namespace utils {

    void DumpStackTrace(std::ostream& t_out, int32_t t_skip)
    {
        void* callstack[s_MAX_STACK_LEVELS];
        char buf[1024];
        int32_t frames = backtrace(callstack, s_MAX_STACK_LEVELS);
        char** symbols = backtrace_symbols(callstack, frames);

        for (int32_t i = t_skip; i < frames; ++i) {
            Dl_info info;
            if (dladdr(callstack[i], &info)) {
                char* demangled = NULL;
                int32_t status;
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
                std::snprintf(buf,
                              sizeof(buf),
                              "%-3d %*p %s + %zd\n",
                              i,
                              (int)(2 + sizeof(void*) * 2),
                              callstack[i],
                              status == 0 ? demangled : info.dli_sname,
                              (char*)callstack[i] - (char*)info.dli_saddr);
                free(demangled);
            } else {
                std::snprintf(
                  buf, sizeof(buf), "%-3d %*p\n", i, (int)(2 + sizeof(void*) * 2), callstack[i]);
            }
            t_out << buf;
            std::snprintf(buf, sizeof(buf), "%s\n", symbols[i]);
            t_out << buf;
        }

        if (frames == s_MAX_STACK_LEVELS) {
            t_out << "[truncated]\n";
        }

        free(symbols);
    }

    void ErrorAbort(const std::string& t_message)
    {
        // Prnt error message
        std::cerr << t_message;

#ifdef MPP_DEBUG
        // Dump stacktrace in debug
        DumpStackTrace(std::cerr);
#endif
        // terminate the program using default terminate handler
        std::terminate();
    }
}}