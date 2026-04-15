#include <iostream>
#include "market_snapshot.h"
#include "order_manager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct LiveFeed {
    bool has_bid = false;
    bool has_ask = false;

    double bid_price = 0.0;
    double ask_price = 0.0;
    int bid_qty = 0;
    int ask_qty = 0;
    int filled_order_id = -1;
    int qty = 0;
};
std::vector<LiveFeed> load_feed(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<LiveFeed> feed;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return feed;
    }

    while (std::getline(file,line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;
        LiveFeed cur_feed;

        if (type == "BID") {
            double price;
            int qty;
            iss >> price >> qty;

            cur_feed.has_bid = true;
            cur_feed.bid_price = price;
            cur_feed.bid_qty = qty;
            feed.push_back(cur_feed);
        }
        else if (type == "ASK") {
            double price;
            int qty;
            iss >> price >> qty;

            cur_feed.has_ask = true;
            cur_feed.ask_price = price;
            cur_feed.ask_qty = qty;
            feed.push_back(cur_feed);
        }
        else if (type == "EXECUTION") {
            double id;
            int qty;
            iss >> id >> qty;

            cur_feed.filled_order_id = id;
            cur_feed.qty = qty;
            feed.push_back(cur_feed);
        }
    }
    return feed;
}
bool should_trade(MarketSnapshot& snapshot) {
    const PriceLevel* best_bid = snapshot.get_best_bid();
    const PriceLevel* best_ask = snapshot.get_best_ask();

    if (best_bid==nullptr || best_ask == nullptr ) {
        return false;
    }
    return best_bid->price >= best_ask->price;
}
int main() {
    MarketSnapshot snapshot;
    OrderManager om(snapshot);

    for (auto& update : load_feed("sample_feed.txt")) {
        if (update.has_bid) {
            snapshot.update_bid(update.bid_price, update.bid_qty);
        }
        else if (update.has_ask) {
            snapshot.update_ask(update.ask_price, update.ask_qty);
        }
        if (should_trade(snapshot)) {
            int id = om.place_order(Side::Bid, snapshot.get_best_bid()->price, 10); // 10?
            std::cout << "Placed BUY order at " << snapshot.get_best_bid()->price << "\n";
        }

        if (update.filled_order_id != -1) {
            om.handle_fill(update.filled_order_id, update.qty);
        }
    }
}
