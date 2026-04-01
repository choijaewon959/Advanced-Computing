# Matrix operations optimization report 

## 1.Introduction 
The project introduces the performance of fundamental linear algebra operations in C++:

- matrix-vector multiplications (MV)
- matrix-matrix multiplications (MM)

The project studies the impact of:

- cache locality (row-major vs column-major access)
- memory alignment
- algorithmic optimzations (transpose B and blocking)

## 2. Methodology
### 2.1 Implementations

The following implementations were developed:

**matrix-vector implementation**:
- row-major access
- column-major access

**matrix-matrix implementation**:
- naive matmul
- transpose B optimization
- blocking multiplication

### 2.2 Benchmarking 

- execution time measured using 'std::chrono'
- multiple runs per execution
- reported mean and standard deviation

### 2.3 Test sizes

squares matrices are of size: 64, 128, 256, 512, 1024, 2048

## 3. Results

### 3.1 Matrix-vector multiplication 



    



