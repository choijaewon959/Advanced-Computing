//
// Created by Jae Won Choi on 30/3/2026.
//

#include "calculation.h"

#include <stdexcept>

void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    if (!matrix || !result || !vector) {
        throw std::invalid_argument("Null pointer passed to multiply_mv_row_major");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("matrix dimensions must be positive");
    }

    for (int i=0; i<rows; i++) {
        double sum=0.0;
        for (int j=0; j<cols; j++) {
            sum += matrix[i*cols + j] * vector[j];
        }
        result[i]=sum;
    }
}

void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    if (!matrix || !result || !vector) {
        throw std::invalid_argument("Null pointer passed to multiply_mv_col_major");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("matrix dimensions must be positive");
    }
    for (int i=0; i<rows; i++) {
        result[i] = 0.0;
    }
    for (int j=0; j<cols; j++) {
        for (int i=0; i<rows; i++) {
            result[i] += matrix[i + j*rows] * vector[j];
        }
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
            double sum=0.0;
            for (int k = 0; k < colsA; ++k) {
                sum += matrixA[i * colsA + k] * matrixB[j * colsB + k];
            }
            result[i * rowsB + j]=sum;
        }
    }
}
void multiply_mm_blocked(const double* matrixA, const double* matrixB, double* matrixC, int N, int BS) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            matrixC[i*N+j] = 0.0;
        }
    }
    for (int ii=0; ii<N; ii+=BS) {
        for (int kk=0; kk<N; kk+=BS) {
            for (int jj=0; jj<N; jj+=BS) {

                int imax = std::min(ii+BS, N);
                int kmax = std::min(kk+BS, N);
                int jmax = std::min(jj+BS, N);

                for (int i=ii; i<imax; ++i) {
                    for (int k=kk; k<kmax; ++k) {
                        double aik = matrixA[i*N+k];
                        for (int j=jj; j<jmax; ++j) {
                            matrixC[i*N+j] += aik * matrixB[j*N+k];
                        }
                    }
                }
            }
        }
    }

}