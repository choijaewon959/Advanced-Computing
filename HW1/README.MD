# Matrix Summation Optimization

## Overview

This project compares a basic matrix summation implementation with an optimized version to improve performance using low-level memory access techniques.

---

## Results

| Version      | Sum       | Time        |
|-------------|----------|------------|
| Basic       | -126820  | 70 ms      |
| Optimized   | -126820  | 11 ms      |

The optimized version achieves a **~6.3x speedup** while producing the same result.

---

## Key Optimizations

### 1. Removed Function Call Overhead
The basic implementation used helper functions (`getElement`, `add`) inside nested loops.  
These functions were called millions of times, adding significant overhead.

The optimized version directly accesses elements and performs addition inline.

---

### 2. Improved Cache Locality
The matrix is stored row-by-row (row-major order).  
The optimized version iterates sequentially through each row:

```cpp
const int* ptr = matrix[i].data();
```

---

### 3. Pointer-based Traversal
Instead of accessing element using indexing (`matrix[i][j]`), the optimized version uses pointer arithmetic:
```cpp
sum += *ptr++;
```
This reduces indexing overhead and allows the compiler to generate more efficient instructions.

___ 

### 4. Simplified Inner Loop
The inner loop is rewritten as:
```cpp
while (ptr < end)
```
This creates a tight loop with minimal operations, enabling better compiler optimizations such as loop unrolling and vectorization.