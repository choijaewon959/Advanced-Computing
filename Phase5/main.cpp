#include <iostream>
#include "OrderBook.h"
#include "Timer.h"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>
#include "OptimizedOrderBook.h"

struct stats {
    double mean;
    double stddev;
    double maxe;
    double mine;
};

stats benchmark(const std::vector<double>& latencies) {
    double mean = std::accumulate(latencies.begin(), latencies.end(), 0.0) / (int)latencies.size();

    double var = 0.0;
    for (int i = 0; i < (int)latencies.size(); ++i) {
        var += (latencies[i] - mean)*(latencies[i] - mean);
    }
    var /= latencies.size();
    double stddev= std::sqrt(var);

    double maxe = *std::max_element(latencies.begin(), latencies.end());
    double mine = *std::min_element(latencies.begin(), latencies.end());

    return {mean, stddev, maxe, mine};
}

int main() {

    int ticks = 10000;

    OrderBook orderBook;
    Timer timer;
    OptimizedOrderBook optiBook(ticks, orderBook);

    std::vector<Order> orders;
    orders.reserve(ticks);

    for (int i = 0; i < ticks; ++i) {
        //orderBook.addOrder(std::to_string(i), (i%2 == 0) ? 150.0 : 155.0, 100, i%2);
        orders.push_back({std::to_string(i), (i%2 == 0) ? 150.0 : 155.0, 100, i%2 == 1});
    }

    optiBook.processOrders(orders);

    std::cout << "order count: " << orderBook.getOrderCount() << std::endl;

    std::vector<std::string> ids;
    ids.reserve(ticks);
    for (int i = 0; i < ticks; ++i) {
        ids.push_back(std::to_string(i));
    }
    std::vector<double> latencies;

    for (int i = 0; i < ticks; ++i) {
        timer.start();

        auto it = orderBook.orderLookup.find(ids[i]);
        if (it != orderBook.orderLookup.end()) {
            double price = it->second.price;
            orderBook.orderLevels[price];
        }

        latencies.push_back(timer.stop());
    }


    std::cout << "LATENCIES in LOOKUP\n";
    stats lat = benchmark(latencies);
    std::cout << "MEAN: " << lat.mean << " stddev " << lat.stddev << " maxe " << lat.maxe << " mine " << lat.mine << std::endl;

}