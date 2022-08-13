#include "collatz.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, handle) {
  handle.doc() = "Documentation for the foo module";

  handle.def("get_longest_sequence", &get_longest_sequence);
  handle.def("get_longest_sequence_threaded", &get_longest_sequence_threaded);
}
