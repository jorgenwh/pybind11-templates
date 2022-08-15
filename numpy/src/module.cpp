#include "foo_functions.h"
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("foo_message", &foo_message);

  handle.def("foo_print_arr", &foo_print_arr);
  handle.def("foo_increment_arr", &foo_increment_arr);

  handle.def("get_np_array", [](const py::tuple &t) {
      std::vector<size_t> arr_shape(t.size());

      for (size_t i = 0; i < t.size(); i++) {
        arr_shape[i] = t[i].cast<size_t>(); 
      } 

      py::array_t<float> arr = py::array_t<float>(arr_shape);
      return arr;
  });

  handle.def("transpose_np_array", [](py::array_t<float> &arr) {
      py::module_ np = py::module_::import("numpy");
      py::array_t<float> arrT = np.attr("transpose")(arr);
      return arrT;
  });
}
