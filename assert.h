#ifndef EBT_UNIT_TEST_H
#define EBT_UNIT_TEST_H

#include <string>
#include <iostream>
#include <cmath>

namespace ebt {

    template <class T, class U = T>
    typename std::enable_if<!std::is_floating_point<T>::value, void>::type
    assert_equals(T const &expected, U const &actual)
    {
        if (expected != actual) {
            std::cerr << "expected: <" << expected << "> but was: <"
                << actual << ">" << std::endl;
            exit(1);
        }
    }
    
    template <class T, class U = T>
    typename std::enable_if<std::is_floating_point<T>::value, void>::type
    assert_equals(T expected, U actual)
    {
        if (std::fabs(expected - actual) > std::fabs(expected) * 1e-6) {
            std::cerr << "expected: <" << expected << "> but was: <"
                << actual << ">" << std::endl;
            exit(1);
        }
    }

    template <class T, class U = T>
    void assert_equals(T expected, U actual, double eps)
    {
        if (std::fabs(expected - actual) > eps) {
            std::cerr << "expected: <" << expected << "> but was: <"
                << actual << ">" << std::endl;
            exit(1);
        }
    }

}

#endif
