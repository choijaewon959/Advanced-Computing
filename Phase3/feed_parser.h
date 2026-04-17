//
// Created by Mohammed RHAZI on 15/04/2026.
//

#ifndef PHASE3_FEED_PARSER_H
#define PHASE3_FEED_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "logger.h"

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
    void print(Logger& log) const {
        switch (type) {
            case FeedType::BID:
                log.info("[NEW BID] " + std::to_string(price) + " x " + std::to_string(quantity));
                break;
            case FeedType::ASK:
                log.info("[NEW ASK] " + std::to_string(price) + " x " + std::to_string(quantity));
                break;
            case FeedType::EXECUTION:
                log.info("[EXECUTION] Order " + std::to_string(order_id) + " filled: " + std::to_string(quantity));
                break;
            default:
                log.error("[UNKNOWN]");
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