#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

struct BookOrder {
    int id;
    double price;
    int quantity;
    char side; // 'B' for bid, 'S' for ask
};

class OrderBook {
private:
    std::unordered_map<int, BookOrder> orders_by_id;

    std::map<double, std::vector<int>> bids;
    std::map<double, std::vector<int>> asks;

public:
    void add_order(int id, double price, int quantity, char side) {
        orders_by_id[id] = {id, price, quantity, side};

        if (side == 'B') {
            bids[price].push_back(id);
        } else {
            asks[price].push_back(id);
        }
    }

    void modify_order(int id, int new_quantity) {
        auto it = orders_by_id.find(id);

        if (it == orders_by_id.end()) {
            std::cout << "Order not found\n";
            return;
        }

        it->second.quantity = new_quantity;
    }

    void delete_order(int id) {
        auto it = orders_by_id.find(id);

        if (it == orders_by_id.end()) {
            std::cout << "Order not found\n";
            return;
        }

        double price = it->second.price;
        char side = it->second.side;

        auto& book = (side == 'B') ? bids : asks;
        auto& level = book[price];

        level.erase(
            std::remove(level.begin(), level.end(), id),
            level.end()
        );

        if (level.empty()) {
            book.erase(price);
        }

        orders_by_id.erase(id);
    }

    void query_price_level(double price, char side) {
        auto& book = (side == 'B') ? bids : asks;

        auto it = book.find(price);

        if (it == book.end()) {
            std::cout << "No orders at price " << price << "\n";
            return;
        }

        std::cout << "Orders at price " << price << ":\n";

        for (int id : it->second) {
            BookOrder& order = orders_by_id[id];

            std::cout << "ID: " << order.id
                      << ", Qty: " << order.quantity
                      << ", Side: " << order.side
                      << "\n";
        }
    }

    void best_bid() {
        if (bids.empty()) {
            std::cout << "No bids\n";
            return;
        }

        auto it = bids.rbegin();

        std::cout << "Best bid: " << it->first << "\n";
    }

    void best_ask() {
        if (asks.empty()) {
            std::cout << "No asks\n";
            return;
        }

        auto it = asks.begin();

        std::cout << "Best ask: " << it->first << "\n";
    }

    void print_bbo() {
        best_bid();
        best_ask();
    }
};

#endif