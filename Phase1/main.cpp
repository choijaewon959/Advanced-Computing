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

const int MATRIX_ROW_SIZE = 1024;
const int MATRIX_COL_SIZE = 1024;

int main() {
    //run_benchmarks();
    run_benchmarks_mm_tb_blocked();
    /*
    // Generate a large random matrix
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-100, 100);

    double *matrix = new double[MATRIX_ROW_SIZE * MATRIX_COL_SIZE];
    for (int i=0; i<MATRIX_ROW_SIZE * MATRIX_COL_SIZE; ++i) {
        matrix[i] = distrib(gen);
    }

    // Generate a large random vector
    double *vector = new double[MATRIX_COL_SIZE];
    for (int i=0; i<MATRIX_COL_SIZE; ++i) {
        vector[i] = distrib(gen);
    }



    // 1. row major vs col major
    // Generate result matrix for 1
    double *result = new double[MATRIX_ROW_SIZE];

    auto start_row_mj = std::chrono::high_resolution_clock::now();
    multiply_mv_row_major(matrix, MATRIX_ROW_SIZE, MATRIX_COL_SIZE, vector, result);
    auto end_row_mj = std::chrono::high_resolution_clock::now();
    auto duration_row_mj = std::chrono::duration_cast<std::chrono::milliseconds>(end_row_mj - start_row_mj);

    std::cout << "Row Major Matrix * Vector: " << std::endl;
    std::cout << "Basic Time: " << duration_row_mj.count() << " milliseconds" << std::endl;

    auto start_col_mj = std::chrono::high_resolution_clock::now();
    multiply_mv_col_major(matrix, MATRIX_ROW_SIZE, MATRIX_COL_SIZE, vector, result);
    auto end_col_mj = std::chrono::high_resolution_clock::now();
    auto duration_col_mj = std::chrono::duration_cast<std::chrono::milliseconds>(end_col_mj - start_col_mj);

    std::cout << "Col Major Matrix * Vector: " << std::endl;
    std::cout << "Basic Time: " << duration_col_mj.count() << " milliseconds" << std::endl;


    // 2. Matrix multiplication Naive vs Matrix multiplication Transpose
    // generate result matrix for 2
    double *result2 = new double[MATRIX_ROW_SIZE * MATRIX_ROW_SIZE];
    auto start_mm_naive = std::chrono::high_resolution_clock::now();
    multiply_mm_naive(matrix, MATRIX_ROW_SIZE, MATRIX_COL_SIZE, matrix, MATRIX_COL_SIZE, MATRIX_ROW_SIZE, result2);
    auto end_mm_naive = std::chrono::high_resolution_clock::now();
    auto duration_mm_naive = std::chrono::duration_cast<std::chrono::milliseconds>(end_mm_naive - start_mm_naive);

    std::cout << "Naive Matrix * Matrix: " << std::endl;
    std::cout << "Basic Time: " << duration_mm_naive.count() << " milliseconds" << std::endl;

    double* matrix_T = new double[MATRIX_ROW_SIZE * MATRIX_COL_SIZE];

    for (int i = 0; i < MATRIX_ROW_SIZE; ++i) {
        for (int j = 0; j < MATRIX_COL_SIZE; ++j) {
            matrix_T[j * MATRIX_ROW_SIZE + i] = matrix[i * MATRIX_COL_SIZE + j];
        }
    }
    auto start_mm_T = std::chrono::high_resolution_clock::now();
    multiply_mm_transposed_b(matrix, MATRIX_ROW_SIZE, MATRIX_COL_SIZE, matrix_T, MATRIX_ROW_SIZE, MATRIX_COL_SIZE, result2);
    auto end_mm_T = std::chrono::high_resolution_clock::now();
    auto duration_mm_T = std::chrono::duration_cast<std::chrono::milliseconds>(end_mm_T - start_mm_T);

    std::cout << "Transposed Matrix * Matrix: " << std::endl;
    std::cout << "Basic Time: " << duration_mm_T.count() << " milliseconds" << std::endl;


    delete[] matrix;
    delete[] matrix_T;
    delete[] vector;
    delete[] result;

    return 0;
    */
}