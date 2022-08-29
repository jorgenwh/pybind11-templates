#ifndef DEVICE_KERNELS_H_
#define DEVICE_KERNELS_H_

#include <cuda.h>
#include <cuda_runtime.h>

void device_add_int(const int *in, const int value, int *out, const int size);
void device_transpose(const int *in, int *out, const int in_rows, const int in_cols);

#endif // DEVICE_KERNELS_H_
