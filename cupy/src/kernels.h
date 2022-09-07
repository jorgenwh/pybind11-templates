#ifndef KERNELS_H_
#define KERNELS_H_

#include <cuda.h>
#include <cuda_runtime.h>

void elemwise_mul(const float *in1, const float *in2, float *out, const size_t size);

#endif // KERNELS_H_
