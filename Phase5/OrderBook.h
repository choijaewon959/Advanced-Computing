//
// Created by Mohammed RHAZI on 02/05/2026.
//

#ifndef PHASE5_ORDERBOOK_H
#define PHASE5_ORDERBOOK_H
#include <string>
#include <map>
#include <unordered_map>

struct Order {
    std::string id;
    double price;
    int quantity;
    bool isBuy;
};

class OrderBook {
public:
    std::map<double, std::unordered_map<std::string, Order>> orderLevels;
    std::unordered_map<std::string, Order> orderLookup;

    void addOrder(const std::string& id, double price, int quantity, bool isBuy) {
        Order order{id, price, quantity, isBuy};
        orderLevels[price][id] = order;
        orderLookup[id] = order;
    }
    void deleteOrder(const std::string& id) {
        auto it = orderLookup.find(id);
        auto levelIt = orderLevels.find(it->second.price);

        if (it != orderLookup.end()) {
            levelIt->second.erase(id);
            if (levelIt->second.empty()) {
                orderLevels.erase(levelIt);
            }
            orderLookup.erase(it);
        }
    }
    void modifyOrder(const std::string& id, double newPrice, int newQuantity) {
        auto it = orderLookup.find(id);
        if (it == orderLookup.end()) return;

        bool isBuy = it->second.isBuy;
        double oldPrice = it->second.price;

        auto levelIt = orderLevels.find(oldPrice);
        if (levelIt != orderLevels.end()) {
            levelIt->second.erase(id);
            if (levelIt->second.empty()) {
                orderLevels.erase(levelIt);
            }
        }

        Order updated {id, newPrice, newQuantity, isBuy};
        orderLevels[newPrice][id] = updated;
        orderLookup[id] = updated;
    }
};


#endif //PHASE5_ORDERBOOK_H