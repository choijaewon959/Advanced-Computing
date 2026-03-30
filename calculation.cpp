//
// Created by Jae Won Choi on 30/3/2026.
//

#include "calculation.h"

#include <stdexcept>

void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        double sum=0.0;
        for (int j=0; j<cols; j++) {
            sum += matrix[i*cols + j] * vector[j];
        }
        result[i]=sum;
    }
}


void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result) {
    if (!matrixA || !matrixB || !result) {
        throw std::invalid_argument("Null pointer passed to multiply_mm_naive");
    }

    if (colsA != rowsB) {
        throw std::runtime_error("Dimensions incompatible");
    }

    for (int i=0; i < rowsA; ++i) {
        for (int j=0; j < colsB; ++j) {
            for (int k=0; k < colsA; ++k) {
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
}


void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result) {
    if (!matrixA || !matrixB || !result) {
        throw std::invalid_argument("Null pointer passed to multiply_mm_transposed_b");
    }

    if (colsA != colsB) {
        throw std::runtime_error("Dimensions incompatible");
    }

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < rowsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i * rowsB + j] += matrixA[i * colsA + k] * matrixB[j * colsB + k];
            }
        }
    }

}
