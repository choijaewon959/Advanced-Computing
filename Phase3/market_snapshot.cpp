//
// Created by Mohammed RHAZI on 14/04/2026.
//

#include "market_snapshot.h"

void MarketSnapshot::update_bid(double price, int qty) {
    auto iter = bids.find(price);
    if (iter != bids.end()) {
        iter->second->quantity += qty;
    }
    else {
        bids.emplace(price, std::make_unique<PriceLevel>(price, qty));
    }
}
void MarketSnapshot::update_ask(double price, int qty) {
    auto it = asks.find(price);
    if (it != asks.end()) {
        it->second->quantity += qty;
    }
    else {
        asks.emplace(price, std::make_unique<PriceLevel>(price, qty));
    }
}
const PriceLevel* MarketSnapshot::get_best_bid() const {
    if (bids.empty()) {
        return nullptr;
    }
    auto it = bids.rbegin();
    return it->second.get();
}
const PriceLevel* MarketSnapshot::get_best_ask() const {
    if (asks.empty()) {
        return nullptr;
    }
    auto it = asks.begin();
    return it->second.get();
}
void MarketSnapshot::cancel_bid(double price, int qty) {
    auto it_bid = bids.find(price);
    if (it_bid != bids.end()) {
        it_bid->second->quantity -= qty;
        if (it_bid->second->quantity <= 0) {
            bids.erase(it_bid);
        }
    }
}
void MarketSnapshot::cancel_ask(double price, int qty) {
    auto it_ask = asks.find(price);
    if (it_ask != asks.end()) {
        it_ask->second->quantity -= qty;
        if (it_ask->second->quantity <= 0) {
            asks.erase(it_ask);
        }
    }
}