#include <iostream>

#include <cuda.h>
#include <cuda_runtime.h>

#include "foo_functions.h"

void foo_message() {
  std::cout << "foo message" << std::endl;
}

__global__ void increment_kernel(float *arr, int size) {
  int i = threadIdx.x;
  arr[i] = arr[i] + 1;
}

void increment_array(float *arr, int size) {
  increment_kernel<<<1, size>>>(arr, size);
  cudaDeviceSynchronize();
}
