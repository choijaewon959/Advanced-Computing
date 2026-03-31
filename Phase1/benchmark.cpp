//
// Created by Mohammed RHAZI on 30/03/2026.
//


#include <vector>
#include "benchmark.h"

stats benchmark_mv_row_major(const double*A, int rowsA, int colsA, const double* vec, double* result, int runs) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<double> times;
    times.reserve(runs);

    multiply_mv_col_major(A, rowsA, colsA, vec, result);

    for (int r=0; r<runs; r++) {
        auto start = clock::now();
        multiply_mv_col_major(A, rowsA, colsA, vec, result);

        auto end = clock::now();
        double time = std::chrono::duration<double>(end-start).count();
        times.push_back(time);
    }
    double s=0.0;
    for (double t:times) s+=t;
    double mean = s/runs;

    double var=0.0;
    for (double t:times) var+=(t-mean)*(t-mean);
    var/=runs;
    double stddev=std::sqrt(var);

    return {mean, stddev};
}
stats benchmark_mv_col_major(const double *A, int rowsA, int colsA, const double *vec, double *result, int runs) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<double> times;
    times.reserve(runs);

    multiply_mv_col_major(A, rowsA, colsA, vec, result);

    for (int r=0; r<runs; r++) {
        auto start = clock::now();
        multiply_mv_col_major(A, rowsA, colsA, vec, result);
        auto end = clock::now();

        double time = std::chrono::duration<double>(end-start).count();
        times.push_back(time);
    }
    double s=0.0;
    for (double t: times) s+=t;
    double mean=s/runs;

    double var=0.0;
    for (double t: times) var+=(t-mean)*(t-mean);
    var/=runs;
    double stddev=std::sqrt(var);

    return {mean, stddev};
}
stats benchmark_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result, int runs) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<double> times;
    times.reserve(runs);

    multiply_mm_naive(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);

    for (int r=0;r<runs;r++) {
        auto start = clock::now();
        multiply_mm_naive(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);
        auto end = clock::now();

        double time = std::chrono::duration<double>(end-start).count();
        times.push_back(time);
    }
    double s=0.0;
    for (double t: times) s+=t;
    double mean=s/runs;

    double var=0.0;
    for (double t: times) var+=(t-mean)*(t-mean);
    var/=runs;
    double stddev=std::sqrt(var);

    return {mean, stddev};
}
stats benchmark_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result, int runs) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<double> times;
    times.reserve(runs);

    multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);

    for (int r=0; r<runs; r++) {
        auto start = clock::now();
        multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);
        auto end = clock::now();

        double time = std::chrono::duration<double>(end-start).count();
        times.push_back(time);
    }
    double s=0.0;
    for (double t:times) s+=t;
    double mean=s/runs;

    double var=0.0;
    for (double t:times) var+=(t-mean)*(t-mean);
    var/=runs;
    double stddev=std::sqrt(var);

    return {mean, stddev};
}
void run_benchmarks() {
    int sizes[] = {64, 128, 256, 512, 1024, 2048};
    std::cout << "N\tRowMean(ms)\tRowStd(ms)\tColMean(ms)\tColStd(ms)\tmmNMean(ms)\tmmNStd(ms)\tmmTBMean(ms)\tmmTBStd(ms)\n" << std::endl;

    for (int N : sizes) {
        double* A = new double[N*N];
        double* B = new double[N*N];
        double* vec = new double[N];
        double* result_mv = new double[N];
        double* result_mm = new double[N*N];
        int runs;

        for (int i=0; i<N*N; ++i) A[i]=1.0;
        for (int i=0; i<N*N; ++i) B[i]=1.0;
        for (int i=0; i<N; ++i) vec[i]=1.0;

        if (N<=128) runs = 1000;
        else if (N<=256) runs = 100;
        else runs = 10;

        stats row = benchmark_mv_row_major(A, N, N, vec, result_mv, runs);
        stats col = benchmark_mv_col_major(A, N, N, vec, result_mv, runs);
        stats mmN = benchmark_mm_naive(A,N,N,B,N,N,result_mm,runs);
        stats mmTb = benchmark_mm_transposed_b(A,N,N,B,N,N,result_mm,runs);

        std::cout << N << "\t"
                  << row.mean * 1e3 << "\t"
                  << row.stddev * 1e3 << "\t"
                  << col.mean * 1e3 << "\t"
                  << col.stddev * 1e3 << "\t"
                  << mmN.mean * 1e3 << "\t"
                  << mmN.stddev * 1e3 << "\t"
                  << mmTb.mean * 1e3 << "\t"
                  << mmTb.stddev * 1e3 << "\n";
        delete[] A;
        delete[] B;
        delete[] vec;
        delete[] result_mv;
        delete[] result_mm;
    }
}