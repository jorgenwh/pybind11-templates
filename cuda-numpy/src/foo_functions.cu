#include "foo_functions.h"
#include "kernels.h"

#include <cmath>

#include <cuda.h>
#include <cuda_runtime.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

py::array_t<float> &cpu_increment(py::array_t<float> &array, float value) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  for (py::ssize_t i = 0; i < data_size; i++) {
    data_ptr[i] = data_ptr[i] + value;
  }

  return array;
}

py::array_t<float> &gpu_increment(py::array_t<float> &array, float value) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  float *d_data_ptr;
  cudaMalloc(&d_data_ptr, sizeof(float)*data_size);
  cudaMemcpy(d_data_ptr, data_ptr, sizeof(float)*data_size, cudaMemcpyHostToDevice);

  increment_array(d_data_ptr, data_size, value);

  cudaMemcpy(data_ptr, d_data_ptr, sizeof(float)*data_size, cudaMemcpyDeviceToHost);
  cudaFree(d_data_ptr);

  return array;
}

py::array_t<float> &cpu_sigmoid(py::array_t<float> &array) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  for (py::ssize_t i = 0; i < data_size; i++) {
    data_ptr[i] = 1.0f / (1.0f + exp(-data_ptr[i]));
  }

  return array;
}

py::array_t<float> &gpu_sigmoid(py::array_t<float> &array) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  float *d_data_ptr;
  cudaMalloc(&d_data_ptr, sizeof(float)*data_size);
  cudaMemcpy(d_data_ptr, data_ptr, sizeof(float)*data_size, cudaMemcpyHostToDevice);

  sigmoid_array(d_data_ptr, data_size);

  cudaMemcpy(data_ptr, d_data_ptr, sizeof(float)*data_size, cudaMemcpyDeviceToHost);
  cudaFree(d_data_ptr);

  return array;
}

py::array_t<float> &cpu_relu(py::array_t<float> &array) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  for (py::ssize_t i = 0; i < data_size; i++) {
    data_ptr[i] = (data_ptr[i] > 0) ? data_ptr[i] : 0;
  }

  return array;
}

py::array_t<float> &gpu_relu(py::array_t<float> &array) {
  size_t data_size = array.size();
  float *data_ptr = array.mutable_data();

  float *d_data_ptr;
  cudaMalloc(&d_data_ptr, sizeof(float)*data_size);
  cudaMemcpy(d_data_ptr, data_ptr, sizeof(float)*data_size, cudaMemcpyHostToDevice);

  relu_array(d_data_ptr, data_size);

  cudaMemcpy(data_ptr, d_data_ptr, sizeof(float)*data_size, cudaMemcpyDeviceToHost);
  cudaFree(d_data_ptr);

  return array;
}
