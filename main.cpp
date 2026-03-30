//
// Created by Mohammed RHAZI on 30/03/2026.
//
#include <iostream>
#include <ostream>

#include "calculation.h"
int main() {



    //tests
    double matrix[6] = {1,2,3,4,5,6};
    double vec[3] = {1,2,3};
    double res[2];

    multiply_mv_row_major(matrix, 2,3,vec, res);
    std::cout << res[0] << " " << res[1] << std::endl;

    multiply_mv_col_major(matrix, 2,3,vec, res);
    std::cout << res[0] << " " << res[1] << std::endl;
}