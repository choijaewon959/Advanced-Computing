#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "Order.h"
#include "Timer.h"
#include "OrderBook.h"
#include "MarketData.h"
#include "TradeLogger.h"
#include "MatchingEngine.h"

using OrderType = Order<double, int>;

int main() {
    std::vector<long long> latencies;
    latencies.reserve(10000);

    const int num_ticks = 10000;

    MarketDataHandler mkt;
    TradeLogger logger("logs.log");

    OrderBook<double, int> orderBook(mkt, logger);
    MatchingEngine matchingEngine(orderBook);

    for (int i = 0; i < num_ticks; ++i) {
        Timer timer;
        timer.start();

        bool isBuy = (i%2==0);
        double price = (i%2 == 0) ? 155.0 : 150.0;

        Tick t{"AAPL", price, isBuy ? Side::Bid : Side::Ask, std::chrono::high_resolution_clock::now()};

        mkt.handleTick(t);

        OrderType order{i, "AAPL", price, 100, isBuy};

        orderBook.placeOrder(order);
        matchingEngine.matchOrders();

        latencies.push_back(timer.stop());
    }

    //analyze latency
    auto min = *std::min_element(latencies.begin(), latencies.end());
    auto max = *std::max_element(latencies.begin(), latencies.end());
    double mean = std::accumulate(latencies.begin(), latencies.end(), 0.0)/latencies.size();

    std::cout << "Tick-to-Trade Latency (nanoseconds) \n";
    std::cout << "Min: " << min << " | Max: " << max <<  " | Mean: " << mean << "\n";

}