## Task1.1
### 1. What happens if you use delete on the array?
error message: *Process finished with exit code 133 (interrupted by signal 5:SIGTRAP)*
Using delete on array directly leads to undefined behavior.

### 2. What happens if you forget to call delete at all?
Memory Leak. Allocated memory stays in the heap.

### Can you call delete twice on the same pointer? Try it. What did you observe?
error message: *Process finished with exit code 133 (interrupted by signal 5:SIGTRAP)*
This leads to unidentified behavior as well.


