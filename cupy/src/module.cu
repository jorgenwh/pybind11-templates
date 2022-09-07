#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "extension_functions.h"

namespace py = pybind11;

PYBIND11_MODULE(cupyext, m) {
  m.doc() = "Documentation for the cupy extension module";

  m.def("elementwise_multiply", &elementwise_multiply);
}
