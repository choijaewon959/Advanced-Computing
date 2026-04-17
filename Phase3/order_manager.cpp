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

    if (cur_order->side == Side::Bid) {
        market.cancel_bid(cur_price, cur_qty);
    }
    else {
        market.cancel_bid(cur_price, cur_qty);
    }
    orders.erase(it);
    cur_order->status = OrderStatus::Cancelled;
}
void OrderManager::handle_fill(int id, int filled_qty) {
    auto it = orders.find(id);
    if (it == orders.end()) {
        log.info("[ORDER] fill ignored: order " + std::to_string(id) + " not active");
        return;
    }

    MyOrder* cur_order = it->second.get();

    if (filled_qty > cur_order->quantity) {
        log.info("[ORDER] invalid overfill in order " + std::to_string(id));
        return;
    }

    if (cur_order->side == Side::Bid) {
        market.cancel_bid(cur_order->price, filled_qty);
    }
    else {
        market.cancel_ask(cur_order->price, filled_qty);
    }

    cur_order->quantity -= filled_qty;
    cur_order->filled += filled_qty;

    log.info("[EXECUTION] Order " + std::to_string(id) + " filled: " + std::to_string(filled_qty));

    if (cur_order->quantity == 0) {
        cur_order->status = OrderStatus::Filled;
        log.info("[ORDER] order " + std::to_string(id) + " completed and removed");
        orders.erase(it);
    }
    else {
        cur_order->status = OrderStatus::PartiallyFilled;
        log.info("[ORDER] order " + std::to_string(id) + " partially filled: " +
            std::to_string(cur_order->filled) + " / " + std::to_string(cur_order->filled + cur_order->quantity));
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