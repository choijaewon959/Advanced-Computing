//
// Created by Mohammed RHAZI on 15/04/2026.
//

#ifndef PHASE3_FEED_PARSER_H
#define PHASE3_FEED_PARSER_H

#include <iostream>
#include "order_manager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

enum class FeedType {
    BID,
    ASK,
    EXECUTION,
    UNKNOWN
};
struct FeedEvent {
    FeedType type = FeedType::UNKNOWN;
    double price = 0.0;
    int quantity = 0;
    int order_id = -1;

    //debug print
    void print() const {
        switch (type) {
            case FeedType::BID:
                std::cout << "[NEW BID] " << price << " x " << quantity << "\n";
                break;
            case FeedType::ASK:
                std::cout << "[NEW ASK] " << price << " x " << quantity << "\n";
                break;
            case FeedType::EXECUTION:
                std::cout << "[EXECUTION] Order " << order_id << " filled: " << quantity << "\n";
                break;
            default:
                std::cout << "[UNKNOWN]\n";
        }
    }
};
std::vector<FeedEvent> load_feed(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<FeedEvent> feed;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return feed;
    }

    while (std::getline(file,line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "BID") {
            double price;
            int qty;
            if (iss >> price >> qty) {
                feed.push_back({FeedType::BID, price, qty});
            }
        }
        else if (type == "ASK") {
            double price;
            int qty;
            if (iss >> price >> qty) {
                feed.push_back({FeedType::ASK, price, qty});
            }
        }
        else if (type == "EXECUTION") {
            int id;
            int qty;
            if (iss >> id >> qty) {
                feed.push_back({FeedType::EXECUTION, 0.0, qty, id});
            };
        }
        else {
            std::cerr << "Unknown event happened: " << line << "\n";
        }
    }
    return feed;
}
#endif //PHASE3_FEED_PARSER_H