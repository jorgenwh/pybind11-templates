#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "kernels.h"
#include "cu.h"

#define THREADS_PER_BLOCK 256 
#define NUM_STREAMS 10

__global__ void elem_mul_kernel(const float *in1, const float *in2, float *out, const size_t size) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= size) { return; }
  out[i] = in1[i] * in2[i];
}

void elemwise_mul(const float *in1, const float *in2, float *out, const size_t size) {
  int num_blocks = size / THREADS_PER_BLOCK + (size % THREADS_PER_BLOCK > 0);
  elem_mul_kernel<<<num_blocks, THREADS_PER_BLOCK>>>(in1, in2, out, size);
  cudaDeviceSynchronize();
}
