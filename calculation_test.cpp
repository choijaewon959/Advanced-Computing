//
// Created by Jae Won Choi on 30/3/2026.
//

#include <iostream>
#include <cassert>
#include "calculation.h"

void test_multiply_mv_row_major() {
    int rowsA = 2;
    int colsA = 3;

    double* A = new double[rowsA * colsA];
    double* vec = new double[colsA];
    double* result = new double[rowsA];

    double A_vals[] = {1,2,3,4,5,6};
    double V_vals[] = {1,2,3};

    std::copy(A_vals, A_vals + rowsA*colsA, A);
    std::copy(V_vals, V_vals + colsA, vec);

    multiply_mv_row_major(A, rowsA, colsA, vec, result);
    double expected[] = {14,32};
    for (int i = 0; i<rowsA; ++i) {
        assert(std::abs(result[i] - expected[i]) < 1e-9);
    }

    delete[] A;
    delete[] vec;
    delete[] result;

    std::cout << "test_multiply_mv_row_major_passed ...\n";
}

void test_multiply_mv_col_major() {
    int rowsA = 2;
    int colsA = 3;

    double* A = new double[rowsA * colsA];
    double* vec = new double[colsA];
    double* result = new double[rowsA];

    double A_vals[] = {1,2,3,4,5,6};
    double vec_vals[] = {1,2,3};

    std::copy(A_vals, A_vals + rowsA*colsA, A);
    std::copy(vec_vals, vec_vals+colsA, vec);
    multiply_mv_col_major(A, rowsA, colsA, vec, result);

    double expected[] = {22, 28};

    for (int i=0; i<rowsA; ++i) {
        assert(abs(result[i] - expected[i]) < 1e-9);
    }

    delete[] A;
    delete[] vec;
    delete[] result;

    std::cout << "test_multiply_mv_col_major passed ... \n";
}

void test_multiply_mm_naive() {
    int rowsA = 2, colsA = 3;
    int rowsB = 3, colsB = 2;

    double* A = new double[rowsA * colsA];
    double* B = new double[rowsB * colsB];
    double* result = new double[rowsA * colsB];

    // initialize
    double A_vals[] = {
        1, 2, 3,
        4, 5, 6
    };
    double B_vals[] = {
        7, 8,
        9, 10,
        11, 12
    };

    for (int i = 0; i < rowsA * colsA; ++i) {
        A[i] = A_vals[i];
    }
    for (int i = 0; i < rowsB * colsB; ++i) {
        B[i] = B_vals[i];
    }
    for (int i = 0; i < rowsA * colsB; ++i) {
        result[i] = 0.0;
    }

    multiply_mm_naive(A, rowsA, colsA, B, rowsB, colsB, result);

    double expected[] = {
        58, 64,
        139, 154
    };

    for (int i = 0; i < rowsA * colsB; ++i) {
        assert(result[i] == expected[i]);
    }

    delete[] A;
    delete[] B;
    delete[] result;

    std::cout << "test_multiply_mm_naive passed...\n";
}

void test_multiply_mm_transposed_b_basic() {
    double* A = new double[6];
    double* B = new double[6];
    double* result = new double[4];

    // initialize
    double A_vals[] = {1,2,3, 4,5,6};
    double B_vals[] = {7,8,9, 10,11,12};

    for (int i = 0; i < 6; ++i) {
        A[i] = A_vals[i];
        B[i] = B_vals[i];
    }

    for (int i = 0; i < 4; ++i) {
        result[i] = 0.0;
    }

    multiply_mm_transposed_b(A, 2, 3, B, 2, 3, result);

    double expected[] = {50, 68, 122, 167};

    for (int i = 0; i < 4; ++i) {
        assert(result[i] == expected[i]);
    }

    // cleanup
    delete[] A;
    delete[] B;
    delete[] result;

    std::cout << "test_multiply_mm_transposed_b_basic passed...\n";
}


int main() {
    test_multiply_mv_row_major();
    test_multiply_mv_col_major();
    test_multiply_mm_naive();
    test_multiply_mm_transposed_b_basic();

    std::cout << "All tests passed...!" << std::endl;
    return 0;
}