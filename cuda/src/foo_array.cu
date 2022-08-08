#include <iostream>
#include <cstring>

#include <cuda.h>
#include <cuda_runtime.h>

#include "foo_array.h"
#include "foo_functions.h"

FooArray::FooArray(int size) {
  size_m = size;
  on_device_m = false;

  h_data_m = new float[size_m];
  memset(h_data_m, 0, sizeof(float)*size_m);
}

FooArray::~FooArray() {
  if (on_device_m) {
    cudaFree(d_data_m);
  }
  else {
    delete[] h_data_m;
  }
}

void FooArray::to_host() {
  if (!on_device_m) { return; }

  h_data_m = new float[size_m];
  cudaMemcpy(h_data_m, d_data_m, sizeof(float)*size_m, cudaMemcpyDeviceToHost);
  cudaFree(d_data_m);

  on_device_m = false;
}

void FooArray::to_device() {
  if (on_device_m) { return; }

  cudaMalloc(&d_data_m, sizeof(float)*size_m);
  cudaMemcpy(d_data_m, h_data_m, sizeof(float)*size_m, cudaMemcpyHostToDevice);
  delete[] h_data_m;

  on_device_m = true;
}

void FooArray::print() {
  std::cout << "FooArray([";
  for (int i = 0; i < size_m; i++) {
    std::cout << h_data_m[i];
    if (i < size_m-1) { std::cout << ", "; }
  }
  std::cout << "], " << (on_device_m ? "device" : "host") << ")" << std::endl;
}

void FooArray::increment() {
  if (!on_device_m) { return; }

  increment_array(d_data_m, size_m);
}
