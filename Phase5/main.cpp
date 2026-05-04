#include <iostream>
#include "OrderBook.h"
#include "Timer.h"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>
#include "OptimizedOrderBook.h"
#include <random>

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

std::vector<Order> generateOrders(int numOrders) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> priceDist(50.0, 100.0);
    std::uniform_int_distribution<int> quantityDist(1,500);
    std::bernoulli_distribution sideDist(0.5);

    std::vector<Order> orders;

    for (int i = 0; i < numOrders; ++i) {
        orders.push_back(
            {"ORD" + std::to_string(i)
                , priceDist(rng)
                , quantityDist(rng)
                , sideDist(rng)
            });
    }
    return orders;
}

int main() {

    int ticks = 100000;

    OrderBook orderBook;
    Timer timer;

    std::vector<Order> orders = generateOrders(ticks);
    /*

    //baseline timer
    timer.start();
    for (const auto& od : orders) {
        orderBook.addOrder(od.id, od.price, od.quantity, od.isBuy);
    }
    std::cout << "baseline latency: " << timer.stop() << std::endl;

    */
    //include Pooling
    std::vector<Order> basePool;
    basePool.reserve(orders.size());

    timer.start();
    for (const auto& od : orders) {
        basePool.push_back(od);
        orderBook.addOrder(basePool.back().id,
                           basePool.back().price,
                           basePool.back().quantity,
                           basePool.back().isBuy);
    }
    double baseTime = timer.stop();

    std::cout << "baseTime(pooling): " << baseTime << std::endl;

    OrderBook optStorage;
    OptimizedOrderBook optiBook(ticks, optStorage);

    //optimized timer
    timer.start();
    optiBook.processOrders(orders);
    std::cout << "optimized latency: " << timer.stop() << std::endl;

    std::cout << "order count: " << orderBook.getOrderCount() << std::endl;

    std::vector<std::string> ids;
    ids.reserve(ticks);
    for (int i = 0; i < ticks; ++i) {
        ids.push_back("ORD" + std::to_string(i));
    }
    std::vector<double> latencies;

    for (int i = 0; i < ticks; ++i) {
        //post storage lookup timer
        timer.start();

        auto it = orderBook.orderLookup.find(ids[i]);
        if (it != orderBook.orderLookup.end()) {
            double price = it->second.price;
            orderBook.orderLevels[price];
        }

        latencies.push_back(timer.stop());
    }


    stats lat = benchmark(latencies);
    std::cout << "lookup latency: " << "MEAN: " << lat.mean << " stddev " << lat.stddev << " maxe " << lat.maxe << " mine " << lat.mine << std::endl;

}