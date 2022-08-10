#ifndef FOO_FUNCTIONS_H_
#define FOO_FUNCTIONS_H_

#include "kernels.h"

#include <cuda.h>
#include <cuda_runtime.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array_t<float> &cpu_increment(py::array_t<float> &array, float value);
py::array_t<float> &gpu_increment(py::array_t<float> &array, float value);
py::array_t<float> &cpu_sigmoid(py::array_t<float> &array);
py::array_t<float> &gpu_sigmoid(py::array_t<float> &array);
py::array_t<float> &cpu_relu(py::array_t<float> &array);
py::array_t<float> &gpu_relu(py::array_t<float> &array);

#endif // FOO_FUNCTIONS_H_
