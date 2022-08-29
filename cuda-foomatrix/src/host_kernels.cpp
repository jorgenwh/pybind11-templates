#include "host_kernels.h"

void host_add_int(const int *in, const int value, int *out, const int size) {
  for (int i = 0; i < size; i++) {
    out[i] = in[i] + value;
  }
}

void host_transpose(const int *in, int *out, const int in_rows, const int in_cols) {
  for (int i = 0; i < in_rows; i++) {
    for (int j = 0; j < in_cols; j++) {
      out[j*in_rows + i] = in[i*in_cols + j];
    }
  }
}
