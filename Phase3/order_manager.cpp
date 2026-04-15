//
// Created by Mohammed RHAZI on 14/04/2026.
//

#include "order_manager.h"

int OrderManager::place_order(Side side, double price, int qty) {
    int id=new_id++;
    orders.emplace(id, std::make_unique<MyOrder>(id, side, price, qty, 0, OrderStatus::New));
    return id;
}
void OrderManager::cancel(int id) {
    auto it = orders.find(id);
    if (it == orders.end()) return;

    MyOrder* cur_order = it->second.get();
    double cur_price = cur_order->price;
    int cur_qty = cur_order->quantity;

    //update book
    if (cur_order->side == Side::Bid) {
        auto bid_it = market.bids.find(cur_price);
        if (bid_it != market.bids.end()) {
            bid_it->second->quantity -= cur_qty;
            if (bid_it->second->quantity <= 0) {
                market.bids.erase(bid_it);
            }
        }
    }
    else {
        auto ask_it = market.asks.find(cur_price);
        if (ask_it != market.asks.end()) {
            ask_it->second->quantity -= cur_qty;
            if (ask_it->second->quantity <= 0) {
                market.asks.erase(ask_it);
            }
        }
    }
}