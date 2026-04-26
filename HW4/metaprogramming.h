//
// Created by Jae Won Choi on 23/4/2026.
//

#ifndef HW4_METAPROGRAMMING_H
#define HW4_METAPROGRAMMING_H

#include <iostream>
#include <type_traits>

// Factorial TMP
template<int N>
struct Factorial {
    static_assert(N >= 0, "Factorial is only defined for non-negative integers");
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Fibonacci TMP
template<int N>
struct Fibonacci {
    static_assert(N >= 0, "Fibonacci is only defined for non-negative integers");
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};


// IsOdd TMP
template<typename T, typename = void>
struct IsOdd : std::false_type {};

template<typename T>
struct IsOdd<T, std::void_t<decltype(T::value)>>
    : std::bool_constant<(T::value % 2 != 0)> {};

template<
    typename T,
    std::enable_if_t<
        std::is_integral_v<T> && (T{} % 2 != 0),
        int
    > = 0
>
void print_if_odd(T value) {
    std::cout << value << " is odd\n";
}

// Alternative: for TMP types with ::value
template<
    typename T,
    std::enable_if_t<IsOdd<T>::value, int> = 0
>
void print_if_odd() {
    std::cout << T::value << " is odd\n";
}

// printall
template<typename... Args>
void print_all(const Args&... args) {
    ((std::cout << args << " "), ...);
    std::cout << '\n';
}

// Compile time tests
static_assert(Factorial<5>::value == 120);
static_assert(Fibonacci<7>::value == 13);

struct Seven {
    static constexpr int value = 7;
};

struct Eight {
    static constexpr int value = 8;
};

static_assert(IsOdd<Seven>::value);
static_assert(!IsOdd<Eight>::value);



#endif //HW4_METAPROGRAMMING_H