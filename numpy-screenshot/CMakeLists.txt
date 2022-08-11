cmake_minimum_required(VERSION 3.16)
project(foo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lX11 -O3")

add_subdirectory(extern/pybind11)

find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")

include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

set(SOURCES ${SOURCES}
  src/screenshot.cpp
)

set(BINDINGS
  src/module.cpp
)

add_library(foo MODULE "${SOURCES}" "${BINDINGS}")

target_link_libraries(foo PRIVATE pybind11::module ${X11_LIBRARIES})

set_target_properties(foo PROPERTIES 
  PREFIX "${PYTHON_MODULE_PREFIX}"
  SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
