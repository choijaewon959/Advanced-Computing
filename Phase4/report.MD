### For the default setup:

Tick-to-Trade Latency (nanoseconds) (10K ticks):
- Min: 541 
- Max: 365208
- Mean: 2148.59
- P99: 7458

Tick-to-Trade Latency (nanoseconds) (1K ticks):
- Min: 459 
- Max: 173500 
- Mean: 1700.17 
- P99: 4000

Tick-to-Trade Latency (nanoseconds) (100K ticks):
- Min: 458 
- Max: 2709250
- Mean: 1700.3
- P99: 2583
std dev & max have larger values. surprisingly P99 2583 means that very high values are outliers (in the 1%)

### Logging off:
with 10k ticks
- Tick-to-Trade Latency (nanoseconds)
- Min: 458
- Max: 338834
- Mean: 1168.02
- P99: 2833
- Here Mean latency halves when logging off. 


### map/multimap vs flater array
- map pros: map always sorted, easy best bid/ask (begin()), easy lookup with iterators
- cons: tree based, poor cache locality, pointer chasing, insert needs nodes
Complexity:
- insert O(logN)
- best bid/ask: O(1)
- cancel O(1)

array:
- pros: contiguous memory, cache-friendly, fast scans, few allocations with reserve
- cons: not sorted, erasing expensive, iterators are invalid after erase
-insert O(1)
- best bid/ask O(n)
- cancel O(n)

### std::unique<ptr> vs raw pointer
raw pointer setup:
```Bash
std::multimap<PriceType, OrderT*, std::greater<PriceType>> buys;
std::multimap<PriceType, OrderT*> sells;
```

```Bash
~OrderBook() {
for (auto& [price, order] : buys) {
delete order;
}
for (auto& [price, order] : sells) {
delete order;
}
}
```

```Bash
auto it = buys.emplace(price, new OrderT(std::move(o)));
auto it = sells.emplace(price, new OrderT(std::move(o)));
```

Tick-to-Trade Latency (nanoseconds)
- Min: 458
- Max: 334083
- Mean: 1785.11
- P99: 2625

Mean latency under a raw pointer setup only decreases marginally.
Both methods need heap allocation, we expected limited improvement. A better optimization is
using a memory pool to reduce allocation overhead 


### cache alignment:
- Tick-to-Trade Latency (nanoseconds)
- Min: 541
- Max: 341083
- Mean: 1891.55
- P99: 2791

Used alignas(64) on Order, even here because multimap stores nodes all over the heap,
impact is low.

### Conclusion
Logging off had the most impact on latency: dropping from 2149ns to 1168ns
after that replacing std::unique<ptr> vs raw pointer produced marginal improvement and so did cache alignement because multimap allocates non contiguously.