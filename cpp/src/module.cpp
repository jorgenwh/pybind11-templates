#include "foo_functions.h"
#include "foo_class.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("foo_message", &foo_message);
  handle.def("foo_collatz", &foo_collatz);

  py::class_<FooClass>(
      handle, "FooClass"
  )
    .def(py::init<int>())
    .def("print", &FooClass::print)
    .def("add_one", &FooClass::add_one)
    ;
}
