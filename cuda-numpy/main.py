import build.foo as foo
print(dir(foo))

import numpy as np
import time

arr_shape = (1024, 2048)
dtype = np.float32
arr_size = 1
for x in arr_shape:
    arr_size *= x

print(f"Array shape={arr_shape}, Array size={arr_size}")

print("----- INCREMENT ARRAY -----")
print("CPU:")
cpu_arr = np.ones(arr_shape, dtype=dtype)
print(f"Original arr sum: {np.sum(cpu_arr)}")
t1 = time.time_ns()
cpu_arr = foo.cpu_increment(cpu_arr, 100)
t2 = time.time_ns()
elapsed_cpu = t2 - t1
print(f"Mutated arr sum: {np.sum(cpu_arr)}")
print(f"Elapsed time: {t2 - t1} ns")

print("\nGPU:")
gpu_arr = np.ones(arr_shape, dtype=dtype)
print(f"Original arr sum: {np.sum(gpu_arr)}")
t1 = time.time_ns()
gpu_arr = foo.gpu_increment(gpu_arr, 100)
t2 = time.time_ns()
elapsed_gpu = t2 - t1
print(f"Mutated arr sum: {np.sum(gpu_arr)}")
print(f"Elapsed time: {t2 - t1} ns")

print("\nNUMPY:")
np_arr = np.ones(arr_shape, dtype=dtype)
print(f"Original arr sum: {np.sum(np_arr)}")
t1 = time.time_ns()
np_arr += 100
t2 = time.time_ns()
print(f"Mutated arr sum: {np.sum(np_arr)}")
print(f"Elapsed time: {t2 - t1} ns\n")

if elapsed_cpu < elapsed_gpu:
    pf = elapsed_gpu / elapsed_cpu
    print(f"CPU was {round(pf*100, 3)}% faster than GPU")
else:
    pf = elapsed_cpu / elapsed_gpu
    print(f"GPU was {round(pf*100, 3)}% faster than CPU")

assert np.array_equal(cpu_arr, gpu_arr)
assert np.array_equal(cpu_arr, np_arr)
print("Array equal assert passed\n")

print("----- SIGMOID ARRAY -----")
start_arr = np.random.randn(*arr_shape).astype(dtype)
print("CPU:")
cpu_arr = start_arr * 1
t1 = time.time_ns()
cpu_arr = foo.cpu_sigmoid(cpu_arr)
t2 = time.time_ns()
elapsed_cpu = t2 - t1
print(f"Elapsed time: {t2 - t1} ns")

print("\nGPU:")
gpu_arr = start_arr * 1
t1 = time.time_ns()
gpu_arr = foo.gpu_sigmoid(gpu_arr)
t2 = time.time_ns()
elapsed_gpu = t2 - t1
print(f"Elapsed time: {t2 - t1} ns")

print("\nNUMPY:")
np_arr = start_arr * 1
t1 = time.time_ns()
np_arr = 1 / (1 + np.exp(-np_arr))
t2 = time.time_ns()
print(f"Elapsed time: {t2 - t1} ns\n")

if elapsed_cpu < elapsed_gpu:
    pf = elapsed_gpu / elapsed_cpu
    print(f"CPU was {round(pf*100, 3)}% faster than GPU")
else:
    pf = elapsed_cpu / elapsed_gpu
    print(f"GPU was {round(pf*100, 3)}% faster than CPU")

np.testing.assert_array_almost_equal(cpu_arr, gpu_arr, decimal=5)
np.testing.assert_array_almost_equal(cpu_arr, np_arr, decimal=5)
print("Array almost equal assert passed (decimal=5)\n")

print("----- RELU ARRAY -----")
print("CPU:")
cpu_arr = start_arr * 1
t1 = time.time_ns()
cpu_arr = foo.cpu_relu(cpu_arr)
t2 = time.time_ns()
elapsed_cpu = t2 - t1
print(f"Elapsed time: {t2 - t1} ns")

print("\nGPU:")
gpu_arr = start_arr * 1
t1 = time.time_ns()
gpu_arr = foo.gpu_relu(gpu_arr)
t2 = time.time_ns()
elapsed_gpu = t2 - t1
print(f"Elapsed time: {t2 - t1} ns")

print("\nNUMPY:")
np_arr = start_arr * 1
t1 = time.time_ns()
np_arr = np.maximum(0, np_arr)
t2 = time.time_ns()
print(f"Elapsed time: {t2 - t1} ns\n")

if elapsed_cpu < elapsed_gpu:
    pf = elapsed_gpu / elapsed_cpu
    print(f"CPU was {round(pf*100, 3)}% faster than GPU")
else:
    pf = elapsed_cpu / elapsed_gpu
    print(f"GPU was {round(pf*100, 3)}% faster than CPU")

np.testing.assert_array_almost_equal(cpu_arr, gpu_arr, decimal=8)
np.testing.assert_array_almost_equal(cpu_arr, np_arr, decimal=8)
print("Array almost equal assert passed (decimal=8)\n")
