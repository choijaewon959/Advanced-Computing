## Task1.1
### 1. What happens if you use delete on the array?
error message: *Process finished with exit code 133 (interrupted by signal 5:SIGTRAP)*
Using delete on array directly leads to undefined behavior.

### 2. What happens if you forget to call delete at all?
Memory Leak. Allocated memory stays in the heap.

### Can you call delete twice on the same pointer? Try it. What did you observe?
error message: *Process finished with exit code 133 (interrupted by signal 5:SIGTRAP)*
This leads to unidentified behavior as well.



## Task 3.1
### 1. Why do we delete the copy constructor?
We delete the copy constructor because TradeHandle has exclusive ownership of a raw pointer.

If copying were allowed:

```cpp
TradeHandle a(new Trade("AAPL", 175));
TradeHandle b = a;   // copy
```
then both a and b would store the same Trade*. This may lead to double deletion.

### 2. Why is move semantics allowed?
Move semantics is allowed because ownership can be safely transferred.

Example:
```cpp
TradeHandle a(new Trade("AAPL", 175));
TradeHandle b = std::move(a);
```
After the move:
b becomes the new owner
a.ptr is set to nullptr
only b will delete the memory

This is safe because there is still only one owner of the resource.

### 3. What happens if you don't define a destructor?
If you do not define a destructor, the raw pointer inside TradeHandle will not be deleted automatically.
Result:
- memory leak 
- the Trade object stays allocated on the heap

## Part 5
1. The biggest risks of memory management:
- memory leaks: forgetting to delete allocated memory (memory grows)
- dangling pointers: accessing memory after it has been freed, leads to undefined behaviour
- double delete: deleting the same pointer twice, leads to runtime errors 

2. The problems that could occur in HFT systems due to memory leaks or fragmentation:
- latency spikes: fragmentation leads to poor cache locality and slow allocations 
- system crashes during trading: memory leaks lead to memory exhaustion (processes killed or crashes)
- missed trading opportunities / incorrect decisions: delays can lead to missed fills or incorrect pricing

3. RAII reduces the risk of bugs:
- RAII ties resource lifetime to object lifetime: resources are acquired in constructors and destroyed in destructors.
So no need to call delete manually, this also prevents leaks and double deletes.

4. Tradeoffs between manual and automatic memory management in performance critical code:
- Manual:
- Pros: More control over allocations, can optimize cache locality & alignment, lower overhead
- Cons: Error prone, hard to maintain, bugs


- Automatic:
- Pros: Safer, easier to maintain, clear ownership (unique_ptr)
- Cons: Slight overhead, less control over memory layout, hidden performance costs
