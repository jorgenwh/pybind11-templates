import time

import build.foo as foo
print(dir(foo))

import numpy as np

x = foo.get_np_array((2, 32))
print(x.shape)
print(x)
