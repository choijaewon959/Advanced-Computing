//
// Created by Mohammed RHAZI on 02/05/2026.
//

#ifndef PHASE5_OPTIMIZEDORDERBOOK_H
#define PHASE5_OPTIMIZEDORDERBOOK_H
#include <vector>
#include "OrderBook.h"
class OptimizedOrderBook {
    OrderBook& orderBook;

public:
    std::vector<Order> orderPool;

    void handleOrder(const Order& order) {
        orderBook.addOrder(order.id, order.price, order.quantity, order.isBuy);
    }

    OptimizedOrderBook(size_t size, OrderBook& ob) : orderBook(ob) {
        orderPool.reserve(size);
    }
    void processOrders(const std::vector<Order>& orders) {
        for (size_t i=0; i<orders.size(); i+=2) {
            orderPool.push_back(orders[i]);
            handleOrder(orderPool.back());

            if (i+1 < orders.size()) {
                orderPool.push_back(orders[i+1]);
                handleOrder(orderPool.back());
            }
        }
    }
};
#endif //PHASE5_OPTIMIZEDORDERBOOK_H