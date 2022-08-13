#pragma once

#include <vector>
#include <thread>
#include <mutex>

std::vector<int> get_longest_sequence(int n);
std::vector<int> get_longest_sequence_threaded(int n, int num_threads);
