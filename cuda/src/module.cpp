#include "cpp_functions.h"
#include "foo_array.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("print_hello_world", &print_hello_world);
  
  py::class_<FooArray>(
      handle, "FooArray"
    )
    .def(py::init<int>())
    .def("print", &FooArray::print)
    ;
}
