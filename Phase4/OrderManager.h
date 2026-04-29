//
// Created by Mohammed RHAZI on 27/04/2026.
//
#ifndef PHASE4_ORDERMANAGER_H
#define PHASE4_ORDERMANAGER_H
#include "OrderBook.h"
#include "OrderManager.h"

template <typename PriceType, typename OrderIdType>
class OrderManager {
    OrderBook<PriceType, OrderIdType>& book;

public:
    OrderManager(OrderBook<PriceType, OrderIdType>& book_) : book(book_) {}

    void placeOrder(Order<PriceType, OrderIdType> o) {
        book.placeOrder(o);
    }

    void cancel(const OrderIdType& id) {
        book.cancel(id);
    }

    void handleFill(const OrderIdType& id, int qty) {
        book.handleFill(id, qty);
    }
};


#endif //PHASE4_ORDERMANAGER_H