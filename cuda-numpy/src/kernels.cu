#include "kernels.h"

#include <cuda.h>
#include <cuda_runtime.h>

#include <cmath>

__global__ void increment_kernel(float *data, size_t size, float value) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= size) { return; }

  data[i] += value;
}

void increment_array(float *data, size_t size, float value) {
  int num_blocks = size / BLOCK_SIZE + (size % BLOCK_SIZE > 0);
  increment_kernel<<<num_blocks, BLOCK_SIZE>>>(data, size, value);
  cudaDeviceSynchronize();
}

__global__ void sigmoid_kernel(float *data, size_t size) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= size) { return; }

  data[i] = 1.0f / (1.0f + exp(-data[i]));
}

void sigmoid_array(float *data, size_t size) {
  int num_blocks = size / BLOCK_SIZE + (size % BLOCK_SIZE > 0);
  sigmoid_kernel<<<num_blocks, BLOCK_SIZE>>>(data, size);
  cudaDeviceSynchronize();
}

__global__ void relu_kernel(float *data, size_t size) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= size) { return; }

  data[i] = (data[i] > 0) ? data[i] : 0;
}

void relu_array(float *data, size_t size) {
  int num_blocks = size / BLOCK_SIZE + (size % BLOCK_SIZE > 0);
  relu_kernel<<<num_blocks, BLOCK_SIZE>>>(data, size);
  cudaDeviceSynchronize();
}
