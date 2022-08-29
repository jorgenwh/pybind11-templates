#include "foo_functions.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>

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

  handle.def("print_some_np_stuff", [](py::array_t<float> &arr) {
      size_t ndims = arr.ndim();
      std::vector<size_t> shape(ndims);

      for (size_t i = 0; i < ndims; i++) {
        shape[i] = arr.shape()[i];
      }

      std::cout << arr.size() << std::endl;
      std::cout << ndims << std::endl;
      std::cout << "(";
      for (size_t i = 0; i < ndims; i++) {
        std::cout << shape[i];
        if (i < ndims-1) {
          std::cout << ", ";
        }
      }
      std::cout << ")" << std::endl;

      float *data = (float *)arr.mutable_data();
      for (int r = 0; r < shape[0]; r++) {
        for (int c = 0; c < shape[1]; c++) {
          printf("%.0f ", data[c + r*shape[1]]);
        }
        std::cout << std::endl;
      }
  });

  handle.def("matmul", [](py::array_t<float> &arr1, py::array_t<float> &arr2) {
      assert(arr1.ndim() == 2);
      assert(arr2.ndim() == 2);

      size_t arr1_rows = arr1.shape()[0];
      size_t arr1_cols = arr1.shape()[1];
      size_t arr2_rows = arr2.shape()[0];
      size_t arr2_cols = arr2.shape()[1];
      size_t out_rows = arr1_rows;
      size_t out_cols= arr2_cols;
    
      assert(arr1_cols == arr2_rows);

      py::array_t<float> out_arr = py::array_t<float>({arr1_rows, arr2_cols});

      float *out = (float *)out_arr.mutable_data();
      float *in1 = (float *)arr1.mutable_data();
      float *in2 = (float *)arr2.mutable_data();

      memset(out, 0, sizeof(float)*out_rows*out_cols);

      for (size_t i = 0; i < out_rows; i++) {
        for (size_t j = 0; j < out_cols; j++) {
          for (size_t k = 0; k < arr1_cols; k++) {
            out[i*out_cols + j] += in1[i*arr1_cols + k] * in2[k*arr2_cols + j];
          }
        }
      }

      return out_arr;
  });
}
