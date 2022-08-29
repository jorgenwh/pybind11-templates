#ifndef FOO_MATRIX_H_
#define FOO_MATRIX_H_

#include <string>
#include <assert.h>

#include "host_kernels.h"
#include "device_kernels.h"

class FooMatrix {
public:
  FooMatrix() = default;
  FooMatrix(int rows, int cols); 
  ~FooMatrix();

  std::string to_string() const;
  void to_host();
  void to_device();

  FooMatrix operator+(const int value) const;
  FooMatrix &operator+=(const int value);
  FooMatrix transpose() const;

private:
  int rows, cols;
  int *data;
  bool on_device;
};

#endif // FOO_MATRIX_H_
