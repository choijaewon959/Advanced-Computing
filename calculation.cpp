//
// Created by Jae Won Choi on 30/3/2026.
//

#include "calculation.h"
void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            int idx = i*cols + j;
            result[idx] = matrix[idx] * vector[j];
        }
    }
}
