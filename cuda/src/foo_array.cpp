#include <string.h>

#include "foo_array.h"
#include "mat_add_one.h"

FooArray::FooArray(int size) {
  size_m = size;
  data_m = new float[size_m];
  memset(data_m, 0, sizeof(float)*size_m);
}

FooArray::~FooArray() {
  delete[] data_m;
}

void FooArray::print() {
  std::cout << "[";
  for (int i = 0; i < size_m; i++) {
    std::cout << data_m[i];
    if (i < size_m-1) { std::cout << ", "; }
  }
  std::cout << "]" << std::endl;
}

void FooArray::add_one() {
  mat_add_one(data_m, size_m);
}
