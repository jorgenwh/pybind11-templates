#include <cuda.h>
#include <cuda_runtime.h>

#include "mat_add_one.h"

__global__ void add_one_kernel(float *arr, int size) {
  int i = threadIdx.x;

  if (i < size) {
    arr[i] = arr[i] + 1;
  }
}

void mat_add_one(float *arr, int size) {
  float *d_arr;

  cudaMalloc(&d_arr, sizeof(float)*size);
  cudaMemcpy(d_arr, arr, sizeof(float)*size, cudaMemcpyHostToDevice);

  <<<1, size>>>add_one_kernel(d_arr, size);
  cudaDeviceSynchronize();

  cudaMemcpy(arr, d_arr, sizeof(float)*size, cudaMemcpyDeviceToHost);
  cudaFree(d_arr);
}
