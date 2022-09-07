cmake_minimum_required(VERSION 3.16)
project(cupyext LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_FLAGS "-arch=sm_75 -O3")

add_subdirectory(extern/pybind11)

set(SOURCES ${SOURCES}
  src/extension_functions.cu
  src/kernels.cu
)

set(BINDINGS
  src/module.cu
)

add_library(cupyext MODULE "${SOURCES}" "${BINDINGS}")

target_link_libraries(cupyext PRIVATE pybind11::module)

set_target_properties(cupyext PROPERTIES 
  PREFIX "${PYTHON_MODULE_PREFIX}"
  SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
