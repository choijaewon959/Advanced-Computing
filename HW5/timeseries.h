#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

#if defined(__aarch64__) || defined(__ARM_NEON)
#include <arm_neon.h>
#define USE_NEON
#endif

inline long long timeNowTS() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

inline void runTimeSeriesValidation() {
    const int N = 20000;
    const int window = 20;

    std::vector<double> prices;
    prices.reserve(N);

    for (int i = 0; i < N; i++) {
        prices.push_back(100.0 + (i % 50));
    }

    std::vector<double> naive;
    std::vector<double> neon;

    naive.reserve(N - window + 1);
    neon.reserve(N - window + 1);

    long long start, end;

    // ---------------------------
    // Naive moving average
    // ---------------------------
    start = timeNowTS();

    for (int i = 0; i <= N - window; i++) {
        double sum = 0.0;

        for (int j = 0; j < window; j++) {
            sum += prices[i + j];
        }

        naive.push_back(sum / window);
    }

    end = timeNowTS();
    std::cout << "Naive moving average: " << end - start << " us\n";

    // ---------------------------
    // NEON moving average
    // ---------------------------
    start = timeNowTS();

    for (int i = 0; i <= N - window; i++) {
        double sum = 0.0;
        int j = 0;

#ifdef USE_NEON
        float64x2_t vecSum = vdupq_n_f64(0.0);

        // Process 2 doubles at once
        for (; j + 1 < window; j += 2) {
            float64x2_t values = vld1q_f64(&prices[i + j]);
            vecSum = vaddq_f64(vecSum, values);
        }

        double temp[2];
        vst1q_f64(temp, vecSum);

        sum = temp[0] + temp[1];
#endif

        // Leftover values
        for (; j < window; j++) {
            sum += prices[i + j];
        }

        neon.push_back(sum / window);
    }

    end = timeNowTS();

#ifdef USE_NEON
    std::cout << "NEON moving average:  " << end - start << " us\n";
#else
    std::cout << "NEON not available on this architecture\n";
#endif

    // ---------------------------
    // Validation
    // ---------------------------
    bool ok = true;

    for (int i = 0; i < static_cast<int>(naive.size()); i++) {
        if (std::fabs(naive[i] - neon[i]) > 1e-9) {
            ok = false;
            break;
        }
    }

    if (ok) {
        std::cout << "Validation passed\n";
    } else {
        std::cout << "Validation failed\n";
    }
}

#endif