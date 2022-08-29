import numpy as np
import cupy as cp

from temp.foo import FooMatrix

mat = FooMatrix(3, 5)
print(mat)

mat += 10
print(mat)

mat2 = mat + 1
print(mat2)
