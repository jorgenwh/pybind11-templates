cmake_minimum_required(VERSION 3.16)
project(foo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pthread")

add_subdirectory(extern/pybind11)

set(SOURCES ${SOURCES}
  src/collatz.cpp
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
