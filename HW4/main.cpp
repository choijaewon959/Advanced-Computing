#include <iostream>

#include "metaprogramming.h"
#include "OrderBookBuffer.h"

int main() {
    // Part1. Metaprogramming
    std::cout << "Factorial<5>: " << Factorial<5>::value << '\n';
    std::cout << "Fibonacci<7>: " << Fibonacci<7>::value << '\n';

    print_if_odd<Seven>();

    print_all(1, 2.5, "hello", 'J');

    // Part4. Policy-Based Design
    OrderBookBuffer<Order, StackAllocator, NoLock> book1(10);
    OrderBookBuffer<Order, HeapAllocator, MutexLock> book2(10);

    book1.add_order({1, 100.5, 10, "BUY"});
    book1.add_order({2, 101.0, 20, "SELL"});

    book2.add_order({3, 99.5, 15, "BUY"});
    book2.add_order({4, 102.0, 25, "SELL"});

    std::cout << "book1:\n";
    book1.print_orders();

    std::cout << "\nbook2:\n";
    book2.print_orders();

    return 0;
}