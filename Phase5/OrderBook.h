//
// Created by Mohammed RHAZI on 02/05/2026.
//

#ifndef PHASE5_ORDERBOOK_H
#define PHASE5_ORDERBOOK_H
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

struct Order {
    std::string id;
    double price;
    int quantity;
    bool isBuy;
};

class OrderBook {
    std::map<double, std::unordered_map<std::string, Order>> orderLevels;
    std::unordered_map<std::string, Order> orderLookup;

public:
    void addOrder(const std::string& id, double price, int quantity, bool isBuy) {
        Order order{id, price, quantity, isBuy};
        orderLevels[price][id] = order;
        orderLookup[id] = order;
    }
    void deleteOrder(const std::string& id) {
        auto it = orderLookup.find(id);
        if (it != orderLookup.end()) {
            orderLevels[it->second.price].erase(id);
            orderLookup.erase(it);
        }
    }
    void modifyOrder(const std::string& id, double pr, double qty) {
        auto it = orderLookup.find(id);
        if (it != orderLookup.end()) {
            orderLevels[it->second.price].erase(id);
            addOrder(id, pr, qty, it->second.isBuy);
        }
    }
};



#endif //PHASE5_ORDERBOOK_H