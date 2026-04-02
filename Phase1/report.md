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
N | RowMean(ms) | RowStd(ms) | ColMean(ms) | ColStd(ms)|
|---|-----------|------------|------------|------------|
64	|0.000608136	|0.000643924|	0.000631152|	0.000903281
128|	0.00246602	|0.00149498|	0.00271624|	0.00272288
256|	0.0108048|	0.0036111|	0.0103689	|0.000264127
512|	0.042917|	0.000458|	0.042354|	6.2e-05
1024	|0.17775|	0.00275|	0.175292|	0.001667
2048	|0.70275	|0.002209	|0.710834|	0.0113755

**Observations**
- Row major and Col major implementations show similar performance
- Differences fall within standard deviation
- Both use contiguous access in the inner loop

### 3.2 Memory alignment
N	| MV default mean   | 	MV default std| MV aligned mean |	MV aligned std|	MM default mean	|MM default std	|MM aligned mean|	MM aligned std
|---|-------------------|----------------|-----------------|------------|----------------|-------------------|-----------------|----------------
64	|0.000585946	|0.000889592	|0.000594921|	0.00048974	|0.0950998|	0.00436226|	0.0976879	|0.0183741
128|	0.0022218	|0.000223635	|0.00222645|	0.000309705	|1.06406	|0.027482	|1.06604	|0.0212727
256	|0.0100541	|0.000633057	|0.00995186|	0.000294622|	8.96963|	0.40998	|8.93807	|0.0934296
512|	0.039815|	0.000995075|	0.0399275	|0.000632886	|98.4872|	0.34712|	98.4553|	0.257753
1024|	0.170571|	0.00192099|	0.174142	|0.00345871	|918.541|	22.462|	914.601	|7.73461
2048|	0.76225|	0.076266|	0.762873	|0.0508428|	7734.4|	20.755|	7742.11|	62.2399

**Observations**
- Alignment has negligeable impact
- Differences are mainly tied to noise

### 3.3 Matrix-Matrix multiplication
N	|MM Tb mean	|MM Tb std|	MM blocked 16 mean	|MM blocked 16 std	|MM blocked 32 mean|	MM blocked 32 std| 	MM blocked 64 mean	 |MM blocked 64 std
|---|-------------------|----------------|-----------------|------------|----------------|-------------------|----------------------|----------------
64	|0.0987418	|0.0167372	|0.118585	|0.00755998	|0.109944	|0.00397361	| 0.107453	            |0.00360319
128|	1.09816	|0.534418	|1.03234	|0.0259032	|0.877397	|0.0429677	| 0.858754	            |0.0176653
256	|9.08295	|0.077764|	8.95824	|0.07714|	6.98827	|0.0433229	|7.0634	|0.0506996
512	|100.712	|1.52596	|79.4821	|1.54251	|62.5421	|0.161768	|88.1926	|0.378324
1024	|931.066	|14.8301	|955.838	|39.9152	|802.729	|8.72366	|880.401	|9.80342
2048	|7841.97	|1.30271	|7931.09	|3.32985|	6866.47|	1.50279|	7746.68	|11.939

## 4. Analysis
### 4.1 Cache locality
Performance depends on access patterns not just storage format.

- Row-major is efficient when accessed row-wise
- Column-major can also be efficient if loop order matches layout
- Poor performance occurs with strided access

### 4.2 Memory alignment

- Alignment produces negligible improvements.
- Modern CPUs handle unaligned accesses efficiently
- Performance is primarily memory bandwidth bound

### 4.3 Blocking optimization
Blocking divides matrices into smaller sub-blocks so that each block fits into cache. Instead of operating on the entire matrix, we perform computations on these blocks, which allows us to reuse data multiple times before it is evicted from cache.

Blocking significantly improved performance by:
- increasing cache reuse
- reducing memory traffic

A block of size **32** provided the best results:
- best balance of cache utilization and overhead
- consistently outperformed baseline methods

## 5. Conclusion
Key findings:
- Loop order and access patterns are critical for performance
- Memory alignment has limited impact in this context
- Blocking provides the largest gains in performance
- Optimal block size is hardware dependent and should fit the cache best (32 in this case)

## 6. Other optimizations
Possible extensions are:
- SIMD/vectorization
- Multithreading
- Cache aware research based on hardware