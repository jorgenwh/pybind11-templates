import time

import build.foo as foo
print(dir(foo))

import numpy as np

arr = np.arange(10, dtype=np.float32)

print(arr.dtype)
print(arr)
t1 = time.time_ns()
arr += 1
t2 = time.time_ns()
elapsed = t2 - t1
print(arr.dtype)
print(arr)
print(f"Elapsed: {elapsed} ns")

arr = np.arange(10, dtype=np.float32)

print(arr.dtype)
print(arr)
t1 = time.time_ns()
arr = foo.foo_increment_arr(arr)
t2 = time.time_ns()
elapsed = t2 - t1
print(arr.dtype)
print(arr)
print(f"Elapsed: {elapsed} ns")
