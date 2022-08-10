#include "foo_functions.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("cpu_increment", &cpu_increment);
  handle.def("gpu_increment", &gpu_increment);

  handle.def("cpu_sigmoid", &cpu_sigmoid);
  handle.def("gpu_sigmoid", &gpu_sigmoid);

  handle.def("cpu_relu", &cpu_relu);
  handle.def("gpu_relu", &gpu_relu);
}
