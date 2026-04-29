//
// Created by Mohammed RHAZI on 27/04/2026.
//

#include "OrderBook.h"

template <typename PriceType, typename OrderIdType>
OrderBook<PriceType, OrderIdType>::OrderBook(MarketDataHandler& m, TradeLogger& l) : market(m), logger(l) {}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::placeOrder(Order<PriceType, OrderIdType> o) {
    auto id = o.id;
    auto price = o.price;

    if (o.is_buy) {
        auto it = buys.emplace(price, std::make_unique<Order<PriceType, OrderIdType>>(std::move(o)));
        buyIndex[id] = it;
    }
    else {
        auto it = sells.emplace(price, std::make_unique<Order<PriceType, OrderIdType>>(std::move(o)));
        sellIndex[id] = it;
    }
}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::cancel(const OrderIdType& id) {
    auto it = buyIndex.find(id);
    if (it != buyIndex.end()) {
        it->second->second->state = State::Cancelled;
        buys.erase(it->second);
        buyIndex.erase(it);
        return;
    }
    auto it2 = sellIndex.find(id);
    if (it2 != sellIndex.end()) {
        it2->second->second->state = State::Cancelled;
        sells.erase(it2->second);
        sellIndex.erase(it2);
    }
}

template <typename PriceType, typename OrderIdType>
void OrderBook<PriceType, OrderIdType>::handleFill(const OrderIdType& id, int qty) {
    auto it = buyIndex.find(id);
    if (it != buyIndex.end()) {
        if (qty >= it->second->second->quantity) {
            it->second->second->state = State::Filled;
            buys.erase(it->second);
            buyIndex.erase(it);
        }
        else {
            it->second->second->state = State::Partial;
            it->second->second->quantity -= qty;
        }
        return;
    }
    auto it2 = sellIndex.find(id);
    if (it2 != sellIndex.end()) {
        if (qty >= it2->second->second->quantity) {
            it2->second->second->state = State::Filled;
            sells.erase(it2->second);
            sellIndex.erase(it2);
        }
        else {
            it2->second->second->state = State::Partial;
            it2->second->second->quantity -= qty;
        }
    }
}

