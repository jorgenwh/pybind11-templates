import time

import numpy as np
import cupy as cp

from cupy_functions import multiply_f32

size = 100000000 
dtype = np.float32
print(f"array size  : {size}")
print(f"array dtype : {dtype}\n")

arr1 = cp.arange(size).astype(dtype)
arr2 = cp.zeros((size)).astype(dtype) + 2

t1 = time.time_ns()
cp_out = arr1 * arr2
t2 = time.time_ns()
print(f"elapsed ns (cp)  : {round(t2 - t1, 3)}")

t1 = time.time_ns()
ext_out = multiply_f32(arr1, arr2)
t2 = time.time_ns()
print(f"elapsed ns (ext) : {round(t2 - t1, 3)}\n")

cp.testing.assert_array_equal(cp_out, ext_out)
print("assert_array_equal passed")
