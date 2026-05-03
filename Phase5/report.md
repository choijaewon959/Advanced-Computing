## Report

### Bottleneck analysis:
1.Lookup performance \
Lookups are expected to be quick: orders are stored in an unordered map which allows O(1) average lookup.
But performance can worsen if IDs collide. \
Solution: hashmaps can be sized using reserve() and/or use custom hash function.

```text
orderLookup.reserve(ticks)
```
```text
latencies.reserve(ticks)
```

2.Memory usage \
Each order is stored twice. so average search speed goes up but memory usage as well. one idea would be to 
store Order once and use pointers to Order in the other container. In HFT systems, memory pools are used to reduce 
fragmentation and allocation overhead

3.Branching delays \
Operations such as Add, Modify and Delete contain checks like if an order exists. These are used for correctness, 
but frequent branches may hurt performance. In practice separating valid/invalid order handling can improve branch prediction

