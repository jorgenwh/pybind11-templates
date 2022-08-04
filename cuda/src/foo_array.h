#ifndef FOO_ARRAY_H_
#define FOO_ARRAY_H_

#include <iostream>

#include "mat_add_one.h"

class FooArray {
public:
  FooArray(int size);
  ~FooArray();

  void print();
  void add_one();

private:
  int size_m;
  float *data_m;
};

#endif // FOO_ARRAY_H_
