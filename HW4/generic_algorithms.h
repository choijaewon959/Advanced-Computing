//
// Created by Mohammed RHAZI on 25/04/2026.
//

#ifndef HW4_GENERIC_ALGORITHMS_H
#define HW4_GENERIC_ALGORITHMS_H

template<typename InputIterator, typename Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate p) {
    while (first!=last) {
        if (p(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

#endif //HW4_GENERIC_ALGORITHMS_H