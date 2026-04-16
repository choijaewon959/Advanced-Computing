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

