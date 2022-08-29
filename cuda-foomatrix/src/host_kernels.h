#ifndef HOST_KERNELS_H_
#define HOST_KERNELS_H_

void host_add_int(const int *in, const int value, int *out, const int size);
void host_transpose(const int *in, int *out, const int in_rows, const int in_cols);

#endif // HOST_KERNELS_H_
