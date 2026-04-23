//
// Created by Jae Won Choi on 23/4/2026.
//

#ifndef HW4_ORDERBOOKBUFFER_H
#define HW4_ORDERBOOKBUFFER_H
#pragma once

#include <iostream>
#include <mutex>

struct Order {
    int id;
    double price;
    int quantity;
    std::string side;
};

std::ostream& operator<<(std::ostream& os, const Order& o) {
    os << "Order(id=" << o.id
       << ", price=" << o.price
       << ", qty=" << o.quantity
       << ", side=" << o.side << ")";
    return os;
}

// Heap Allocator
struct HeapAllocator {
    template<typename T>
    T* allocate(std::size_t n) {
        return new T[n];
    }

    template<typename T>
    void deallocate(T* ptr) {
        delete[] ptr;
    }
};

struct StackAllocator {
    template<typename T>
    T* allocate(std::size_t n) {
        static T buffer[100];
        return buffer;
    }

    template<typename T>
    void deallocate(T*) {}
};

// Policies
struct NoLock {
    void lock() {}
    void unlock() {}
};

struct MutexLock {
    std::mutex m;

    void lock() {
        m.lock();
    }

    void unlock() {
        m.unlock();
    }
};

// Orderbook buffer
template<typename T, typename AllocatorPolicy, typename ThreadingPolicy>
class OrderBookBuffer {
    T* data;
    std::size_t capacity;
    std::size_t size;

    AllocatorPolicy allocator;
    ThreadingPolicy lock_policy;

public:
    OrderBookBuffer(std::size_t cap)
        : capacity(cap), size(0) {
        data = allocator.template allocate<T>(capacity);
    }

    ~OrderBookBuffer() {
        allocator.template deallocate<T>(data);
    }

    void add_order(const T& order) {
        lock_policy.lock();

        if (size < capacity) {
            data[size] = order;
            ++size;
        }

        lock_policy.unlock();
    }

    void print_orders() {
        lock_policy.lock();

        for (std::size_t i = 0; i < size; ++i) {
            std::cout << data[i] << '\n';
        }

        lock_policy.unlock();
    }
};
#endif //HW4_ORDERBOOKBUFFER_H