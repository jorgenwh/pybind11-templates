cmake_minimum_required(VERSION 3.16)
project(foo LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)

file(GLOB SOURCES
  foo_matrix.cu
  host_kernels.cpp
  device_kernels.cu
)

add_executable(foo main.cpp ${SOURCES})
