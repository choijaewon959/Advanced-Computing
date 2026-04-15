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
        market.cancel_bid(cur_price, cur_qty);
    }
    else {
        market.cancel_bid(cur_price, cur_qty);
    }
    //delete in orderr;
    orders.erase(it);
    cur_order->status = OrderStatus::Cancelled;
}
void OrderManager::handle_fill(int id, int filled_qty) {
    auto it = orders.find(id);
    if (it == orders.end()) return;

    MyOrder* cur_order = it->second.get();
    cur_order->quantity -= filled_qty;
    cur_order->filled += filled_qty;

    if (cur_order->quantity == 0) {
        cur_order->status = OrderStatus::Filled;
    }
    else {
        cur_order->status = OrderStatus::PartiallyFilled;
    }
}
void OrderManager::print_active_orders() const {
    if (orders.empty()) {
        std::cout << "NO ACTIVE ORDERS" << std::endl;
        return;
    }
    std::cout << " ID " << "\t" << " PRICE " << "\t" << " REMAINING " << "\t" << " FILLED " << std::endl;
    for (const auto& [id, order_ptr] : orders){
        const auto& order = *order_ptr;
        std::cout << order.id << "\t" << order.price << "\t" << order.quantity << "\t" << order.filled << std::endl;
    }
}