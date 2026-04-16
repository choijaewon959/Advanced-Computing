//
// Created by Mohammed RHAZI on 14/04/2026.
//

#include "market_snapshot.h"

void MarketSnapshot::update_bid(double price, int qty) {
    auto it = bids.find(price);
    if (qty == 0) {
        if (it != bids.end()) {
            bids.erase(it);
        }
        return;
    }
    if (it != bids.end()) {
        it->second->quantity = qty;
    }
    else {
        bids.emplace(price, std::make_unique<PriceLevel>(price, qty));
        std::cout << price << std::endl;
    }
}
void MarketSnapshot::update_ask(double price, int qty) {
    auto it = asks.find(price);
    if (qty == 0) {
        if (it != asks.end()) {
            asks.erase(it);
        }
        return;
    }
    if (it != asks.end()) {
        it->second->quantity = qty;
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
    auto it = bids.find(price);
    if (it != bids.end()) {
        it->second->quantity -= qty;
        if (it->second->quantity <= 0) {
            bids.erase(it);
        }
    }
}
void MarketSnapshot::cancel_ask(double price, int qty) {
    auto it = asks.find(price);
    if (it != asks.end()) {
        it->second->quantity -= qty;
        if (it->second->quantity <= 0) {
            asks.erase(it);
        }
    }
}