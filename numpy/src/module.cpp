#include "foo_functions.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("foo_message", &foo_message);

  handle.def("foo_print_arr", &foo_print_arr);
  handle.def("foo_increment_arr", &foo_increment_arr);
}
