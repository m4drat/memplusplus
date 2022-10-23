#pragma once

#include "mpplib/utils/profiler_definitions.hpp"
#include <algorithm>
#include <cassert>

namespace mpp { namespace utils {

    /**
     * @brief Default backtrace size.
     */
    static const uint32_t s_MAX_STACK_LEVELS = 50;

    /**
     * @brief Secure implementation of memset.
     * @param t_pointer Pointer to memory to be set.
     * @param t_targetBufferSize Destination buffer size.
     * @param t_fillChar Character to fill memory with.
     * @param t_sizeToRemove Size of memory to be removed.
     * @return void* Pointer to cleared memory.
     */
    void* SecureMemset(void* t_pointer,
                       size_t t_targetBufferSize,
                       unsigned char t_fillChar,
                       size_t t_sizeToRemove);

    /**
     * @brief Helper function to dump stacktrace.
     * @param t_out output stream to write to.
     * @param t_skip number of functions to skip from backtrace.
     */
    void DumpStackTrace(std::ostream& t_out, int32_t t_skip = 1);

    /**
     * @brief Function to print error message and terminate program.
     * @param message message to print
     */
    [[noreturn]] void ErrorAbort(const std::string& t_message);

    /**
     * @brief Behaves like an assert.
     * @param t_shouldAbort if true, calls utils::ErrorAbort.
     * @param t_message message to print.
     */
    inline void ConditionalAbort(bool t_shouldAbort, const std::string& t_message)
    {
        if (t_shouldAbort) {
            ErrorAbort(t_message);
        }
    }

    /**
     * @brief Converts pointer to string (hexadecimal: 0x1337) representation
     * @param t_ptr pointer to convert
     * @return std::string string representation of the t_ptr
     */
    std::string AddrToString(void* t_ptr);

    /**
     * @brief Finds first element, that is greater or equal to key.
     * @param first iterator to begin of the range
     * @param last iterator to end of the range
     * @param value element to find
     * @param comp comparator
     * @return iterator to found element
     */
    template<class ForwardIt, class T, class Compare>
    ForwardIt LowerBound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
    {
        using difference_type = typename std::iterator_traits<ForwardIt>::difference_type;

        PROFILE_FUNCTION();

        ForwardIt iter;
        difference_type count;
        difference_type step;
        count = std::distance(first, last);

        while (count > 0) {
            iter = first;
            step = count / 2;
            std::advance(iter, step);
            if (comp(*iter, value)) {
                first = ++iter;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return first;
    }

    /**
     * @brief Performs binary search in container.
     * @param first iterator to begin of the range
     * @param last iterator to end of the range
     * @param value element to find
     * @param comp comparator
     * @return iterator to found element
     */
    template<class T1, class ForwardIt, class T2, class Compare>
    T1* BinarySearch(ForwardIt first, ForwardIt last, const T2& value, Compare comp)
    {
        PROFILE_FUNCTION();

        first = std::lower_bound(first, last, value, comp);
        if (!(first == last) && !(comp(value, *first)))
            return *first;
        return nullptr;
    }
}}