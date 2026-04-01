# High-Performance Linear Algebra Kernel

## Overview 

This project is to implement and optimize linear algebra operations(matrix-vector multiplication) considering cache locality, memory alignment, and the impact of compiler optimizations.

## Team Member

1. Mohammed Rhazi 12506615
2. Jae Won (Jay) Choi 12506596

## Build Instructions


## Part3. Discussion Questions

### 1. Key differences between Reference and Pointers
- Reference is the alias of the variable whereas pointer is address that can be handled manually.
- Reference cannot be NULL, and does not require dereferencing, whereas pointer can be NULL and requires dereferencing.
- Memory access control can be only done via pointers (layout, traversal, arithmetic). 
- Pointer is preferred to traverse matrix or flexibly "striding" between elements within the containers whereas reference is preferred when passing the operands into mathematical functions or operating in single element.

### 2. Row-major vs Column-major and Cache Locality on matrix-vector and matrix-matrix

### 3. CPU Caches(L1, L2, L3) and temporal/spatial locality
- | Cache   | Size       | Speed        | Scope               |
  | ------- | ---------- | ------------ | ------------------- |
  | **L1**  | ~32KB      | 🔥 fastest   | per core            |
  | **L2**  | ~256KB–1MB | fast         | per core            |
  | **L3**  | ~10–30MB   | slower       | shared across cores |
  | **RAM** | GBs        | 🐢 very slow | global              |

  - Cache Lines
  Memory is not fetched one at a time. CPU loads cache lines (~64 bytes)
  - **Temporal locality**
  
    If the data is accessed once, the data is likely to be accessed again soon.

    - **Spatial locality** 
  
      If the data is accessed in one memory location, nearby locations will be used soon.
      - **How we exploited locality of memory**
   
        - Temporal Locality
        ```cpp
              
        ```
        - Spatial Locality
        ```cpp
            
        ```
### 4. Memory Alignment
### 5. Compiler Optimization
- Compiler Optimization transforms my code to run faster without changing any behaviour.
- Inlining

  - Removes function call overhead 
  - Enables further optimization (vectorization)
- Loop optimizations

  - Unrolling, Reordering
- Auto-vectorization
- Impact on our performance optimization

  - The optimized implementation, especially via -O3, benefited more from higher optimization levels because it was written in a compiler-friendly way—contiguous memory access, simple loops, and no aliasing ambiguity.

- Potential Drawback of Aggressive Optimization 

  - It might hurt instruction cache (higher instruction cache pressure), chage floating-pointer behavior.


### 6. Profiling
tba

### 7. Teamwork Assessment
- Mo implemented Matrix-Vector Multiplication and Jay implemented Matrix-Matrix Multiplication.
- We then explained his own logic on the implementation to each other, and then discussed about the potential points to be improved after running benchmarking tools and profiling.
- Challenges were that explaining the logic of each other's code and understanding the potential optimization area for the code (as our initial version of the codes were already pretty optimized).
- Benefit was that I need to be 100 percent sure about the logic of the code to explain about it and had a good opportunity to talk about the potential improvements in each other's code.
    
    
    