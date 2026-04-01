//
// Created by Mohammed RHAZI on 30/03/2026.
//
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include "calculation.h"

#ifndef ADVANCED_COMPUTING_BENCHMARK_H
#define ADVANCED_COMPUTING_BENCHMARK_H
struct stats{
    double mean;
    double stddev;
};

stats benchmark_mv_row_major(const double*A, int rowsA, int colsA, const double* vec, double* result, int runs);

stats benchmark_mv_col_major(const double*A, int rowsA, int colsA, const double* vec, double* result, int runs);

stats benchmark_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result, int runs);

stats benchmark_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result, int runs);

stats benchmark_mm_blocked(const double* matrixA, const double* matrixB, double* matrixC, int N, int BS, int runs);

double* allocate_aligned(std::size_t count, std::size_t alignment);

void run_benchmarks();

void run_benchmarks_aligned();

void run_benchmarks_mm_tb_blocked_16();

void run_benchmarks_mm_tb_blocked_32();

void run_benchmarks_mm_tb_blocked_64();


#endif //ADVANCED_COMPUTING_BENCHMARK_H