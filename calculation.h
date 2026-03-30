//
// Created by Jae Won Choi on 30/3/2026.
//

#ifndef ADVANCED_COMPUTING_CALCULATION_H
#define ADVANCED_COMPUTING_CALCULATION_H

void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result);

void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result);

void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result);

void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result);



#endif //ADVANCED_COMPUTING_CALCULATION_H