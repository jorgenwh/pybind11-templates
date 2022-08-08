#ifndef FOO_ARRAY_H_
#define FOO_ARRAY_H_

#include <iostream>

#include <cuda.h>
#include <cuda_runtime.h>

#include "foo_functions.h"

class FooArray {
public:
  FooArray(int size);
  ~FooArray();

  void print();
  void increment();

  void to_device();
  void to_host();

private:
  int size_m;

  float *h_data_m;
  float *d_data_m;

  bool on_device_m;
};

#endif // FOO_ARRAY_H_
