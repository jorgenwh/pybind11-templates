#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "extension_functions.h"
#include "kernels.h"

void elementwise_multiply(long in_data1, long in_data2, long out_data, size_t size) {
  float *in1 = reinterpret_cast<float*>(in_data1);
  float *in2 = reinterpret_cast<float*>(in_data2);
  float *out = reinterpret_cast<float*>(out_data);

  elemwise_mul(in1, in2, out, size);
}
