//
// Created by Mohammed RHAZI on 02/05/2026.
//

#ifndef PHASE5_TIMER_H
#define PHASE5_TIMER_H
#include <iostream>
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point startTime;
public:
    void start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    double stop() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - startTime;

        //std::cout << "Execution time: " <<  elapsed.count() << " seconds" << std::endl;
        return elapsed.count();
    }

};

#endif //PHASE5_TIMER_H