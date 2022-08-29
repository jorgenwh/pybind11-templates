cmake_minimum_required(VERSION 3.16)
project(foo LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_FLAGS "-O3")

add_subdirectory(extern/pybind11)

set(SOURCES ${SOURCES}
  src/foo_matrix.cu
  src/host_kernels.cpp
  src/device_kernels.cu
)

set(BINDINGS
  src/module.cpp
)

add_library(foo MODULE "${SOURCES}" "${BINDINGS}")

target_link_libraries(foo PRIVATE pybind11::module)

set_target_properties(foo PROPERTIES 
  PREFIX "${PYTHON_MODULE_PREFIX}"
  SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
