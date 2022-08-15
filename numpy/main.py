import time

import temp.foo as foo
print(dir(foo))

import numpy as np

arr = np.arange(12).reshape(3, 4)

t1 = time.time_ns()
arrT1 = np.transpose(arr)
t2 = time.time_ns()
print(t2 - t1)

t1 = time.time_ns()
arrT2 = foo.transpose_np_array(arr)
t2 = time.time_ns()
print(t2 - t1)

