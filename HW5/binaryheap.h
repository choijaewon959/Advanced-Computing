//
// Created by Jae Won Choi on 30/4/2026.
//

#ifndef HW5_BINARYHEAP_H
#define HW5_BINARYHEAP_H
#include <vector>
#include <queue>

struct Order {
    int id;
    double price;
};

// Max heap for bids: highest price first
class MaxHeap {
private:
    std::vector<Order> heap;

    bool better(Order a, Order b) {
        return a.price > b.price;
    }

public:
    void push(Order order) {
        heap.push_back(order);

        int i = heap.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (better(heap[parent], heap[i])) {
                break;
            }

            std::swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    Order pop() {
        Order best = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        int i = 0;

        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int bestChild = i;

            if (left < heap.size() && better(heap[left], heap[bestChild])) {
                bestChild = left;
            }

            if (right < heap.size() && better(heap[right], heap[bestChild])) {
                bestChild = right;
            }

            if (bestChild == i) {
                break;
            }

            std::swap(heap[i], heap[bestChild]);
            i = bestChild;
        }

        return best;
    }

    bool empty() {
        return heap.empty();
    }
};
#endif //HW5_BINARYHEAP_H