import numpy as np
import cupy as cp

import temp.cupyext as cupyext

def multiply_f32(cp_arr1, cp_arr2):
    assert cp_arr1.shape == cp_arr2.shape
    assert cp_arr1.dtype == np.float32
    assert cp_arr2.dtype == np.float32

    out_arr = cp.zeros_like(cp_arr1, dtype=np.float32)

    cupyext.elementwise_multiply(
            cp_arr1.data.ptr, cp_arr2.data.ptr, out_arr.data.ptr, out_arr.size)

    return out_arr
