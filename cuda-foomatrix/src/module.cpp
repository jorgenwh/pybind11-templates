#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

#include "foo_matrix.h"

namespace py = pybind11;

PYBIND11_MODULE(foo, m) {
  m.doc() = "Documentation for the foo module";

  py::class_<FooMatrix>(m, "FooMatrix")
    .def(py::init<int,int>())
    .def("__repr__", &FooMatrix::to_string)
    .def("to_host", &FooMatrix::to_host)
    .def("to_device", &FooMatrix::to_device)
    .def("__add__", [](FooMatrix &self, int other) { 
        return self + other; 
    }, py::is_operator())
    .def(py::self += int())
    ;
}
