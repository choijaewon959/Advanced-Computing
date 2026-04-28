//
// Created by Mohammed RHAZI on 27/04/2026.
//

#include "OrderBook.h"

template <typename PriceType, typename OrderIdType>
OrderBook<PriceType, OrderIdType>::OrderBook(MarketDataHandler& m) : market(m) {}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::placeOrder(Order<PriceType, OrderIdType> o) {
    orders[o.id] = std::make_unique<Order<PriceType, OrderIdType>>(std::move(o));
}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::cancel(const OrderIdType& id) {
    auto it = orders.find(id);
    if (it == orders.end()) return;

    it->second->state = State::Cancelled;
    orders.erase(it);
}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::handleFill(const OrderIdType& id, int qty) {
    auto it = orders.find(id);
    if (it != orders.end()) {
        if (qty >= it->second->quantity) {
            it->second->state = State::Filled;
            orders.erase(it);
        }
        else {
            it->second->state = State::Partial;
            it->second->quantity -= qty;
        }
    }
}

