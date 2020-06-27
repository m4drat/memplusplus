#pragma once

// Utils to create graphical representation
// of objects graph

#include <algorithm>
#include <iostream>

namespace mpp {
    namespace utils {
        /**
         * @brief Finds first elemet, that is greater or equal to key.
         * @param first iterator to begin of the range
         * @param last iterator to end of the range
         * @param value element to find
         * @param comp comparator
         * @return iterator to found element
         */
        template<class ForwardIt, class T, class Compare>
        ForwardIt LowerBound(ForwardIt first,
                             ForwardIt last,
                             const T& value,
                             Compare comp)
        {
            ForwardIt it;
            typename std::iterator_traits<ForwardIt>::difference_type count, step;
            count = std::distance(first, last);

            while (count > 0) {
                it = first;
                step = count / 2;
                std::advance(it, step);
                if (comp(*it, value)) {
                    first = ++it;
                    count -= step + 1;
                } else
                    count = step;
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
            first = std::lower_bound(first, last, value, comp);
            if (!(first == last) && !(comp(value, *first)))
                return *first;
            return nullptr;
        }
    }
}