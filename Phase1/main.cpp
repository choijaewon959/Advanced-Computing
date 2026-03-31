//
// Created by Mohammed RHAZI on 30/03/2026.
//
#include <iostream>
#include <ostream>
#include "calculation.h"
#include "benchmark.h"

int main() {
    /*
    int rowsA=2, colsA=3;
    int rowsB=2, colsB=3;
    double* A = new double[rowsA * colsA];
    double* B = new double[rowsB * colsB];
    double* vec = new double[colsA];
    double* result = new double[rowsA];

    double A_vals[] = {1,2,3,4,5,6};
    double B_vals[] = {1,2,3,4,5,6};
    double vec_vals[] = {1,2,3};
    std::copy(A_vals, A_vals+rowsA*colsA, A);
    std::copy(vec_vals, vec_vals+colsA, vec);

    std::cout << benchmark_mv_row_major(A, rowsA, colsA, vec, result, 1000) << std::endl;
    std::cout << benchmark_mm_transposed_b(A, rowsA, colsA, B, rowsB, colsB, result, 1000) << std::endl;
*/
    run_benchmarks();
}