#include <math.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "device_kernels.h"

#define BLOCK_SIZE 252

__global__ void add_int_kernel(const int *in, const int value, int *out, const int size) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= size) { return; }
  out[i] = in[i] + value;
}

void device_add_int(const int *in, const int value, int *out, const int size) {
  int num_blocks = size / BLOCK_SIZE + (size % BLOCK_SIZE > 0);
  add_int_kernel<<<num_blocks, BLOCK_SIZE>>>(in, value, out, size);
  cudaDeviceSynchronize();
}

__global__ void transpose_kernel(const int *in, int *out, const int in_rows, const int in_cols) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= in_rows*in_cols) { return; }

  int in_row = floor((float)i / in_cols);
  int in_col = i % in_cols;
  int out_row = in_col;
  int out_col = in_row;

  out[out_row*in_rows + out_col] = in[in_row*in_cols + in_col];
}

void device_transpose(const int *in, int *out, const int in_rows, const int in_cols) {
  int size = in_rows*in_cols;
  int num_blocks = size / BLOCK_SIZE + (size % BLOCK_SIZE > 0);
  transpose_kernel<<<num_blocks, BLOCK_SIZE>>>(in, out, in_rows, in_cols);
  cudaDeviceSynchronize();
}
