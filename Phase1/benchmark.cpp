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
stats benchmark_mm_blocked(const double* matrixA, const double* matrixB, double* matrixC, int N, int BS, int runs) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<double> times;
    times.reserve(runs);

    multiply_mm_blocked(matrixA, matrixB, matrixC, N, BS);

    for (int r=0;r<runs;r++) {
        auto start = clock::now();
        multiply_mm_blocked(matrixA, matrixB, matrixC, N, BS);
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

double* allocate_aligned(std::size_t count, std::size_t alignment = 64) {
    void* ptr= nullptr;
    if (posix_memalign(&ptr, alignment, count * sizeof(double)) != 0) {
        throw std::bad_alloc();
    }
    return static_cast<double*>(ptr);
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
        for (int i=0; i<N*N; ++i) result_mm[i]=0.0;

        if (N<=128) runs = 10000;
        else if (N<=256) runs = 1000;
        else runs = 2;

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
void run_benchmarks_aligned() {
    int sizes[] = {64, 128, 256, 512, 1024, 2048};
    std::cout << "N\tMV default mean\tMV default std\tMV aligned mean\tMV aligned std\tMM default mean\tMM default std\tMM aligned mean\tMM aligned std\tMM optimized mean\tMM optimized std" << std::endl;

    for (int N : sizes) {
        double* A = allocate_aligned(N*N);
        double* B = allocate_aligned(N*N);
        double* result_mv = allocate_aligned(N);
        double* result_mm = allocate_aligned(N*N);
        double* vec = allocate_aligned(N);

        double* A_default = new double[N*N];
        double* B_default = new double[N*N];
        double* vec_default = new double[N];
        double* result_mv_default = new double[N];
        double* result_mm_default = new double[N*N];

        int runs;
        for (int i=0; i<N*N; ++i) {
            A[i] = 1.0;
            B[i] = 1.0;
            A_default[i] = 1.0;
            B_default[i] = 1.0;
            result_mm[i] = 0.0;
            result_mm_default[i] = 0.0;
        }
        for (int i=0; i<N; ++i) {
            vec[i] = 1.0;
            vec_default[i] = 1.0;
        }

        if (N<=128) runs = 10000;
        else if (N<=256) runs = 1000;
        else if (N<=512) runs = 100;
        else runs = 20;

        stats row = benchmark_mv_row_major(A, N, N, vec, result_mv, runs);
        stats mmTb = benchmark_mm_transposed_b(A,N,N,B,N,N,result_mm,runs);

        stats row_default = benchmark_mv_row_major(A_default, N, N, vec_default, result_mv_default, runs);
        stats mmTb_default = benchmark_mm_transposed_b(A_default,N,N,B_default,N,N,result_mm_default,runs);

        std::cout << N << "\t"
                  << row_default.mean * 1e3 << "\t"
                  << row_default.stddev * 1e3 << "\t"
                  << row.mean * 1e3 << "\t"
                  << row.stddev * 1e3 << "\t"
                  << mmTb_default.mean * 1e3 << "\t"
                  << mmTb_default.stddev * 1e3 << "\t"
                  << mmTb.mean * 1e3 << "\t"
                  << mmTb.stddev * 1e3 << "\n";

        free(A);
        free(B);
        free(result_mv);
        free(result_mm);
        free(vec);

        delete[] A_default;
        delete[] B_default;
        delete[] result_mv_default;
        delete[] result_mm_default;
        delete[] vec_default;
    }
}
void run_benchmarks_mm_tb_blocked() {
    int sizes[] = {64, 128, 256, 512, 1024, 2048};
    std::cout << "N\tMM Tb mean\tMM Tb std\tMM blocked 16 mean\tMM blocked 16 std\tMM blocked 32 mean\tMM blocked 32 std\tMM blocked 64 mean\tMM blocked 64 std" << std::endl;

    for (int N : sizes) {
        double* A = new double[N*N];
        double* B = new double[N*N];
        double* result_mm_tb = new double[N*N];
        double* result_mm_blocked = new double[N*N];

        int runs;
        for (int i=0; i<N*N; ++i) {
            A[i] = 1.0;
            B[i] = 1.0;
            result_mm_tb[i] = 0.0;
            result_mm_blocked[i] = 0.0;
        }

        if (N<=128) runs = 10000;
        else if (N<=256) runs = 1000;
        else if (N<=512) runs = 100;
        else runs = 20;

        stats mmTb = benchmark_mm_transposed_b(A,N,N,B,N,N,result_mm_tb, runs);

        stats mmBlock16 = benchmark_mm_blocked(A,B,result_mm_blocked,N,16,runs);
        stats mmBlock32 = benchmark_mm_blocked(A,B,result_mm_blocked,N,32,runs);
        stats mmBlock64 = benchmark_mm_blocked(A,B,result_mm_blocked,N,64,runs);

        std::cout << N << "\t"
                 << mmTb.mean * 1e3 << "\t"
                 << mmTb.stddev * 1e3 << "\t"
                 << mmBlock16.mean * 1e3 << "\t"
                 << mmBlock16.stddev * 1e3 << "\t"
                 << mmBlock32.mean * 1e3 << "\t"
                 << mmBlock32.stddev * 1e3 << "\t"
                 << mmBlock64.mean * 1e3 << "\t"
                 << mmBlock64.stddev * 1e3 << "\n" ;

        delete[] A;
        delete[] B;
        delete[] result_mm_tb;
        delete[] result_mm_blocked;
    }
}