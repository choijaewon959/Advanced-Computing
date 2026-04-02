//
// Created by Mohammed RHAZI on 30/03/2026.
//
#include <iostream>
#include <ostream>
#include <chrono>
#include <vector>
#include <random>

#include "benchmark.h"
#include "calculation.h"

int main() {
    //run_benchmarks();
    //run_benchmarks_aligned();
    run_benchmarks_mm_tb_blocked();
    /*
    run_benchmarks_mm_tb_blocked_16();
    run_benchmarks_mm_tb_blocked_32();
    run_benchmarks_mm_tb_blocked_64();
    */
}