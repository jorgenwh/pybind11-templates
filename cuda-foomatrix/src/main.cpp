#include <iostream>
#include <chrono>
#include <vector>
#include <tuple>

#include "foo_matrix.h"

void time_host_transpose(int rows, int cols) {
  FooMatrix mat(rows, cols);
  
  auto t1 = std::chrono::high_resolution_clock::now();
  FooMatrix matT = mat.transpose();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

  std::cout << "Host elapsed time: " << elapsed << " nanoseconds\n";
}

void time_device_transpose(int rows, int cols) {
  FooMatrix mat(rows, cols);
  mat.to_device();
  
  auto t1 = std::chrono::high_resolution_clock::now();
  FooMatrix matT = mat.transpose();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

  std::cout << "Device elapsed time: " << elapsed << " nanoseconds\n\n";
}

int main(int argc, char **argv) {
  //std::cout << "ROWS=" << ROWS << ", COLS=" << COLS << "\n\n";
  
  std::vector<std::tuple<int,int>> shapes{
    {5, 10}, {10, 10}, {50, 100}, {100, 100}, {500, 1000}, {1000, 1000}, {5000, 10000}, {10000, 10000}
  };
  
  for (auto &shape : shapes) {
    int rows = std::get<0>(shape);
    int cols = std::get<1>(shape);
    std::cout << "\nROWS=" << rows << ", COLS=" << cols << "\n";
    time_host_transpose(rows, cols);
    time_device_transpose(rows, cols);
  }
}
