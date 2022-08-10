#ifndef KERNELS_H_
#define KERNELS_H_

#include <cuda.h>
#include <cuda_runtime.h>

#include <cmath>

#define BLOCK_SIZE 512

void increment_array(float *data, size_t size, float value);
void sigmoid_array(float *data, size_t size);
void relu_array(float *data, size_t size);

#endif // KERNELS_H_
