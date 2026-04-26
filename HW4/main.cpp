#include <iostream>

#include "constexpr_math.h"
#include "metaprogramming.h"
#include "OrderBookBuffer.h"
#include "generic_algorithms.h"
#include "StaticVector.h"

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


    //part 2
    //compile time
    static_assert(square(5) == 25);
    static_assert(factorial(5) == 120);
    static_assert(fibonacci(5) == 5);
    static_assert(price_bucket(101.73) == 101.70);

    constexpr int n = square(5);
    int arr[n];

    //runtime
    int x = 5;
    std::cout << "square "<< x << ": " << square(x) << '\n';
    std::cout << "factorial " << x << ": " << factorial(x) << '\n';
    std::cout << "fibonacci " << x << ": " << fibonacci(x) << '\n';

    double price = 101.73;
    std::cout << "price_bucket "<< price << ": " << price_bucket(price) << '\n';

    std::cout << "array size: " << n << "\n";

    //part 3
    StaticVector<int, 5> v;
    v.push_back(2);
    v.push_back(1);

    std::sort(v.begin(), v.end());

    for (auto x : v) {
        std::cout << x << " " << '\n';
    }

    //find if (part5)
    std::cout << "part 5" << "\n";
    int arr_t[] = {1,3,4,8,9};

    auto it = ::find_if(arr_t, arr_t+5, [](int x){ return x%2 == 0;});
    if (it!=arr_t+5) {
        std::cout << "first even number: " << *it << '\n';
    }

    std::vector<Order> orders;
    orders.push_back(Order({1, 101, 3, "B"}));
    orders.push_back(Order({2, 90, 40, "S"}));

    //all orders with price > 100;
    std::cout << "orders with price > 100: " << "\n";
    auto it2 = orders.begin();

    while ((it2 = ::find_if(it2, orders.end(), [](const Order& o) {
        return o.price > 100;
    })) != orders.end()) {
        std::cout << *it2 << "\n";
        ++it2;
    };

    //first order with order divisible by 10
    std::cout << "first order with order divisible by 10: " << "\n";
    auto it3 = ::find_if(orders.begin(), orders.end(), [](const Order& o) {
        return o.quantity % 10 == 0;
    });

    if (it3!=orders.end()) {
        std::cout << *it3 << "\n";
    }

    //replace T with a struct in staticVector
    std::cout << "replace T with a struct in staticVector: \n";
    StaticVector<Order, 5> orders2;

    orders2.push_back(Order({1, 101, 3, "B"}));
    orders2.push_back(Order({2, 90, 40, "S"}));

    for (const auto& x : orders2) {
        std::cout << x << "\n";
    }


    return 0;
}