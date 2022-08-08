#include "foo_functions.h"
#include "foo_array.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("foo_message", &foo_message);

  py::class_<FooArray>(
      handle, "FooArray"
  )
    .def(py::init<int>())
    .def("print", &FooArray::print)
    .def("to_host", &FooArray::to_host)
    .def("to_device", &FooArray::to_device)
    .def("increment", &FooArray::increment)
    ;
}
