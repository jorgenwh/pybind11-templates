#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "foo_functions.h"

std::string foo_message() {
  return "Foo message";
}

void foo_print_arr(py::array_t<float> arr) {
  const float *data = arr.data();

  std::cout << "[";
  for (int i = 0; i < arr.size(); i++) {
    std::cout << data[i];
    if (i < arr.size()-1) { std::cout << ", "; }
  }
  std::cout << "]" << std::endl;
}

py::array_t<float> &foo_increment_arr(py::array_t<float> &arr) {
  float *ptr = (float *)arr.mutable_data(); 

  for (py::ssize_t i = 0; i < arr.size(); i++) {
    ptr[i]++;
  }

  return arr;
}
