#ifndef FOO_FUNCTIONS_H_
#define FOO_FUNCTIONS_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

std::string foo_message();

void foo_print_arr(py::array_t<float> arr);
py::array_t<float> &foo_increment_arr(py::array_t<float> &arr);

#endif // FOO_FUNCTIONS_H_
