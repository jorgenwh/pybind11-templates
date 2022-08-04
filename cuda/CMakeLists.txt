cmake_minimum_required(VERSION 3.16)
project(foo LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_CUDA_STANDARD 14)
#set(CMAKE_CUDA_FLAGS "-O3")

add_subdirectory(extern/pybind11)

set(SOURCES ${SOURCES}
  src/cpp_functions.cpp
  src/foo_array.cpp
)

set(CUDA_SOURCES
  src/mat_add_one.cu
)

set(BINDINGS
  src/module.cpp
)

add_library(gpu STATIC "${CUDA_SOURCES}")
set_target_properties(gpu PROPERTIES CUDA_SEPERABLE_COMPILATION ON
  POSITION_INDEPENDENT_CODE TRUE)

add_library(foo MODULE "${SOURCES}" "${BINDINGS}")
target_link_libraries(foo PRIVATE pybind11::module)
set_target_properties(foo PROPERTIES 
  PREFIX "${PYTHON_MODULE_PREFIX}"
  SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
