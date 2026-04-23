#include <iostream>

#include "metaprogramming.h"

int main() {
    std::cout << "Factorial<5>: " << Factorial<5>::value << '\n';
    std::cout << "Fibonacci<7>: " << Fibonacci<7>::value << '\n';

    print_if_odd<Seven>();

    print_all(1, 2.5, "hello", 'J');

    return 0;
}