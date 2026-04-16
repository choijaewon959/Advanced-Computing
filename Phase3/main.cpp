#include <iostream>
#include "order_manager.h"
#include "feed_parser.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

            std::cout << "ID "<< id << ": Placed BUY order at " << snapshot.get_best_bid()->price << """\n";
        }
        if (update.filled_order_id != -1) {
            om.handle_fill(update.filled_order_id, update.qty);
        }
    }
}
