#ifndef FOO_FUNCTIONS_H_
#define FOO_FUNCTIONS_H_

#include <cuda.h>
#include <cuda_runtime.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

void elementwise_multiply(long in_data1, long in_data2, long out_data, size_t size);

#endif // FOO_FUNCTIONS_H_
