#include <string>
#include <assert.h>
#include <iostream>

#include <cuda.h>
#include <cuda_runtime.h>
#include <sstream>

#include "foo_matrix.h"
#include "host_kernels.h"
#include "device_kernels.h"

FooMatrix::FooMatrix(int rows, int cols) {
  data = new int[rows*cols];
  this->rows = rows;
  this->cols = cols;

  int count = 10;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      data[r*cols + c] = count;
      count++;
    }
  }

  on_device = false;
}

FooMatrix::~FooMatrix() {
  if (on_device) {
    cudaFree(data);
  } else {
    delete[] data;
  }
}

std::string FooMatrix::to_string() const {
  std::stringstream ss;

  int *dptr;
  bool needs_free = false;
  if (on_device) {
    dptr = new int[rows*cols];
    cudaMemcpy(dptr, data, rows*cols*sizeof(int), cudaMemcpyDeviceToHost);
    needs_free = true;
  } else {
    dptr = data;
  }

  ss << "FooMatrix(";
  ss << "[";
  for (int r = 0; r < rows; r++) {
    if (r != 0) { ss << "           "; }
    ss << "[";
    for (int c = 0; c < cols; c++) {
      ss << dptr[r*cols + c];
      if (c < cols - 1) { ss << ", "; }
    }
    if (r == rows - 1) { ss << "]"; }
    ss << "]";
    if (r != rows - 1) { ss << "\n"; }
  }
  ss << ", device=" << (on_device ? "device" : "host") << ")";

  if (needs_free) {
    assert(on_device);
    delete[] dptr;
  }
  return ss.str();
}

void FooMatrix::to_host() {
  if (!on_device) { return; }

  int *h_ptr = new int[rows*cols];
  cudaMemcpy(h_ptr, data, rows*cols*sizeof(int), cudaMemcpyDeviceToHost);
  cudaFree(data);
  data = h_ptr;

  on_device = false;
}

void FooMatrix::to_device() {
  if (on_device) { return; }

  int *cu_ptr;
  cudaMalloc(&cu_ptr, rows*cols*sizeof(int));
  cudaMemcpy(cu_ptr, data, rows*cols*sizeof(int), cudaMemcpyHostToDevice);
  delete[] data;
  data = cu_ptr;

  on_device = true;
}

FooMatrix FooMatrix::operator+(const int value) const {
  FooMatrix ret;

  ret.rows = rows;
  ret.cols = cols;
  ret.on_device = on_device;

  if (on_device) {
    size_t size = rows*cols*sizeof(int);
    cudaMalloc(&ret.data, size);
    device_add_int(data, value, ret.data, rows*cols);
  } else {
    ret.data = new int[rows*cols];
    host_add_int(data, value, ret.data, rows*cols);
  }

  return ret;
}

FooMatrix &FooMatrix::operator+=(const int value) {
  int size = rows*cols;
  for (int i = 0; i < size; i++) { 
    data[i] += value;
  }
  return *this;
}

FooMatrix FooMatrix::transpose() const {
  FooMatrix ret;

  ret.rows = cols;
  ret.cols = rows;
  ret.on_device = on_device;

  if (on_device) {
    size_t size = rows*cols*sizeof(int);
    cudaMalloc(&ret.data, size);
    device_transpose(data, ret.data, rows, cols);
  } else {
    ret.data = new int[cols*rows];
    host_transpose(data, ret.data, rows, cols);
  }

  return ret;
}
