//
// Created by Mohammed RHAZI on 25/04/2026.
//

#ifndef HW4_CONSTEXPR_MATH_H
#define HW4_CONSTEXPR_MATH_H

//part 2
constexpr int factorial(int n) {
    if (n<0) {
        throw std::invalid_argument("n must be non negative");
    }
    return (n<=1) ? 1 : n * factorial(n-1);
}

static_assert(factorial(4) == 24);

constexpr int fibonacci(int n) {
    if (n<0) {
        throw std::invalid_argument("n must be non negative");
    }
    return (n<=1) ? n : fibonacci(n-1) + fibonacci(n-2);
}

static_assert(fibonacci(4) == 3);

constexpr double price_bucket(double price) {
    return static_cast<int> (price*20.0) / 20.0;
}

static_assert(price_bucket(2.27) == 2.25);

constexpr int square(int x) {
    return x*x;
}

static_assert(square(5) == 25);
static_assert(price_bucket(101.73) == 101.70);

constexpr int n = square(5);
int arr[n];


#endif //HW4_CONSTEXPR_MATH_H