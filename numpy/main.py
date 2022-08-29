import time

import temp.foo as foo
print(dir(foo))

import numpy as np

w1 = np.random.randn(728, 1024).astype(np.float32)
w2 = np.random.randn(1024, 512).astype(np.float32)
w3 = np.random.randn(512, 10).astype(np.float32)

inputs = np.random.randn(16, 728).astype(np.float32)

# Forward np
h_np = np.dot(inputs, w1)
h_np = np.dot(h_np, w2)
h_np = np.dot(h_np, w3)

# Forward foo 
h_foo = foo.matmul(inputs, w1)
h_foo = foo.matmul(h_foo, w2)
h_foo = foo.matmul(h_foo, w3)

np.testing.assert_almost_equal(h_np, h_foo, decimal=1)
