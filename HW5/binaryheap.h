#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>

struct Order {
    double price;
    int timestamp;

    bool operator<(const Order& other) const {
        return price < other.price; // max-heap by price
    }
};

class MaxHeap {
private:
    std::vector<Order> heap;

public:
    MaxHeap() = default;

    explicit MaxHeap(int capacity) {
        heap.reserve(capacity);
    }

    bool empty() const {
        return heap.empty();
    }

    int size() const {
        return static_cast<int>(heap.size());
    }

    void push(const Order& order) {
        heap.push_back(order);

        int i = static_cast<int>(heap.size()) - 1;
        Order value = heap[i];

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (!(heap[parent] < value)) {
                break;
            }

            heap[i] = heap[parent];
            i = parent;
        }

        heap[i] = value;
    }

    const Order& top() const {
        return heap[0];
    }

    void pop() {
        if (heap.empty()) {
            return;
        }

        Order value = heap.back();
        heap.pop_back();

        if (heap.empty()) {
            return;
        }

        int i = 0;
        int n = static_cast<int>(heap.size());

        while (true) {
            int left = 2 * i + 1;
            int right = left + 1;

            if (left >= n) {
                break;
            }

            int child = left;

            if (right < n && heap[left] < heap[right]) {
                child = right;
            }

            if (!(value < heap[child])) {
                break;
            }

            heap[i] = heap[child];
            i = child;
        }

        heap[i] = value;
    }
};

#endif