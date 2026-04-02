# High-Performance Linear Algebra Kernel

## Overview 

The project introduces implementations and optimizations of classic linear algebra operations on C++ (matrix-vector and matrix-matrix multiplications). The study also measures the impact of cache locality, memory alignment, and compiler optimizations over the kernels.

## Team Members

1. Mohammed Rhazi 12506615
2. Jae Won (Jay) Choi 12506596

## Build Instructions
- Requirements

  - C++ compiler with C++17 support
  - CMake 3.10 or newer
  - Xcode / Clang on macOS, or GCC/Clang on Linux

- Bash code
```Bash
mkdir -p build
cd build
cmake ..
make
```

## Part3. Discussion Questions

### 1. Key differences between References and Pointers
- A reference is the alias of a variable whereas pointer is an address that can be handled manually.
- A reference cannot be NULL, and does not require dereferencing, whereas a pointer can be NULL and requires dereferencing.
- Memory access control can only be done via pointers (layout, traversal, arithmetic). 
- Pointers are preferred in matrix traversal or in "striding" between elements within containers. References are preferred when passing operands into functions or operations involving a single element.

### 2. Row-major vs Column-major and Cache Locality on matrix-vector and matrix-matrix
- Matrix-Vector
  - As C++ usually stores the matrix in row-major, where the adjacent elements are contiguous in the heap memory, Row-major computation is expected to be faster. 
  - However, in this assignment's setting, we assume column-major matrix is accessing elements that are also contiguous in heap memory, and therefore there is no expected difference in overall running time.
- Matrix-Matrix
  
  - In the naive approach, matrix multiplication loops from left to right on the row of the left matrix and top to bottom on the column of the right matrix. Here, we need to "jump" from one index to another when we are looping from top to bottom on the second matrix.
  - To deal with this, we transpose the matrix before passing it into the function to maintain the data access contiguous which improves the runtime.
  
### 3. CPU Caches(L1, L2, L3) and temporal/spatial locality
- | Cache   | Size       | Speed       | Scope               |
  | ------- | ---------- | ----------- | ------------------- |
  | **L1**  | ~32KB      | fastest   | per core            |
  | **L2**  | ~256KB–1MB | fast        | per core            |
  | **L3**  | ~10–30MB   | slower      | shared across cores |
  | **RAM** | GBs        | very slow | global              |

  - Cache Lines
  Memory is not fetched one at a time. CPU loads cache lines (~64 bytes)
  - **Temporal locality**
  
    If the data is accessed once, the data is likely to be accessed again soon.

  - **Spatial locality** 
  
    If the data is accessed in one memory location, nearby locations will be used soon.
  
  **How we exploited locality of memory**

    - Spatial Locality is improved by structuring loops to access contiguous elements of data; this is exploited by transposing matrix B to allow cache friendly access in matmul 
    ```cpp
        for (int j=0; j<cols; j++){
            sum += matrix[i*cols + j];
        }
  ```
    - Temporal Locality is improved through blocking which allow submatrices to remain in cache and be reused many times, reducing memory traffic
    ```cpp
        double a=A[i][k]
        for (int j=0; j<N; j++){
           C[i][j] += a * B[k][j]
        }
  ```
  
  
### 4. Memory Alignment
Memory alignment refers to data storage at memory adresses that are multiples of a specific byte (eg 32, 64 bytes). 
Memory alignment can improve performance in theory by enabling efficient memory access and vectorization.
However we did not observe an improvement from aligned memory; this is because computations are memory band width bound,
and modern hardware is efficient in handling unaligned accesses.
### 5. Compiler Optimization
- Compiler Optimization transforms our code to run faster without changing any behavior.
- Inlining

  - Removes function call overhead 
  - Enables further optimization (vectorization)
- Loop optimizations

  - Unrolling, Reordering
- Auto-vectorization
- Impact on our performance optimization

  - The optimized implementation, especially via -O3, benefited more from higher optimization levels because it was written in a compiler-friendly way—contiguous memory access, simple loops, and no aliasing ambiguity.

- Potential Drawback of Aggressive Optimization 

  - It might hurt instruction cache (higher instruction cache pressure), change floating-pointer behavior.


### 6. Profiling
![Profiling Result](img/Profiling%20result.png)

- We have focused on optimizing Matrix * Matrix multiplication. We have provided the runtime of naive algorithm vs transposed algorithm vs block cached algorithm.
- We have tested for 3 different block sizes - 16, 32, and 64. 
- Due to updated cache locality in transposed version and blocked version, we could find significant improvement in the runtime of the algorithm from naive to optimized (110mins → 3mins 50s).
- As expected, the main bottleneck is the big stride between the index of memory for naive approach, whereas transposed version and block cached version leverages on cache locality and cache reuse which enables 30x faster result.
```cpp
  // bottleneck - naive approach
  result[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
```
```cpp
  // block-cached - improved with cache reuse by storing result of submatrix
  int imax = std::min(ii+BS, N);
  int kmax = std::min(kk+BS, N);
  int jmax = std::min(jj+BS, N);
  
  for (int i=ii; i<imax; ++i) {
      for (int k=kk; k<kmax; ++k) {
          double aik = matrixA[i*N+k];
          for (int j=jj; j<jmax; ++j) {
              matrixC[i*N+j] += aik * matrixB[j*N+k];
```
- See more details about the implementation logic and result in report.md

### 7. Teamwork Assessment
- Mo implemented Matrix-Vector Multiplication and Jay implemented Matrix-Matrix Multiplication.
- After explaining each other's logic and implementation, we discussed potential points of improvement amid running benchmarking tools and profiling.
- The main challenge was to find an angle of optimization using our limited knowledge of C++. We focused on the matrix-matrix operation since it is most time consuming and likely presented more room for improvement
- The first implementations served as a refresher of basic linear algebra operations and made us aware of the potential bottlenecks in data access. Our views then converged naturally when discussing improvements - cache locality, memory alignment and blocking were the obvious optimizations sources. We then separately studied each type and discussed tradeoffs, correctness and usability. Each question raised was discussed (ex how to fit the best number of blocks in submatrices for blocking) and a solution fitting the context was adopted
    
    
    