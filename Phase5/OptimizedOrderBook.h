//
// Created by Mohammed RHAZI on 02/05/2026.
//

#ifndef PHASE5_OPTIMIZEDORDERBOOK_H
#define PHASE5_OPTIMIZEDORDERBOOK_H
#include <vector>
#include "OrderBook.h"
class OptimizedOrderBook {
    std::vector<Order> orderPool;
    OrderBook& orderBook;

    void handleOrder(const Order& order) {
        orderBook.addOrder(order.id, order.price, order.quantity, order.isBuy);
    }
public:
    OptimizedOrderBook(size_t size, OrderBook& ob) : orderBook(ob) {
        orderPool.reserve(size);
    }
    void processOrders(const std::vector<Order>& orders) {
        for (size_t i=0; i<orders.size(); i+=2) {
            handleOrder(orders[i]);
            if (i+1 < orders.size()) handleOrder(orders[i+1]);
        }
    }
};
#endif //PHASE5_OPTIMIZEDORDERBOOK_H