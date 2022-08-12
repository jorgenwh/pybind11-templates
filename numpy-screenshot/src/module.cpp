#include "screenshot.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("screenshot", &screenshot, py::arg("scale_factor") = 1.0f, py::return_value_policy::take_ownership);
}
