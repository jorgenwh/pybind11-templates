#include <iostream>
#include <string.h>

#include "foo_class.h"

FooClass::FooClass(int size) {
  size_m = size;
  h_data_m = new float[size_m];
  memset(h_data_m, 0, sizeof(float)*size_m);
}

FooClass::~FooClass() {
  delete[] h_data_m;
}

void FooClass::print() {
  std::cout << "[";
  for (int i = 0; i < size_m; i++) {
    std::cout << h_data_m[i];
    if (i < size_m-1) { std::cout << ", "; }
  }
  std::cout << "]" << std::endl;
}

void FooClass::add_one() {
  for (int i = 0; i < size_m; i++) {
    h_data_m[i] = h_data_m[i] + 1;
  }
}
