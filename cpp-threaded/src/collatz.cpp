#include <vector>
#include <thread>
#include <mutex>

#include "collatz.h"

__inline__ static int step(int n) {
  if (n%2 == 0) {
    return n/2;
  }
  else {
    return n*3 + 1;
  }
}

static std::vector<int> get_collatz_sequence(int n) {
  std::vector<int> seq{n};

  while (n != 1) {
    n = step(n);
    seq.push_back(n);
  }

  return seq;
}

std::vector<int> get_longest_sequence(int n) {
  std::vector<int> longest_seq;

  for (int i = 1; i <= n; i++) {
    std::vector<int> cur_seq = get_collatz_sequence(i);
    if (cur_seq.size() > longest_seq.size()) {
      longest_seq = cur_seq;
    }
  }

  return longest_seq;
}

static std::mutex fetch_mu;
static std::mutex dump_mu;

static int end;
static int counter = 1;
static std::vector<int> longest_seq;

static int fetch_next_n() {
  std::lock_guard<std::mutex> lock(fetch_mu);
  if (counter > end) {
    return -1;
  }
  counter++;
  return counter - 1;
}

static void dump_seq(std::vector<int> &seq) {
  std::lock_guard<std::mutex> lock(dump_mu);
  if (seq.size() > longest_seq.size()) {
    longest_seq = seq;
  }
}

static void thread_worker() {
  while (true) {
    int n = fetch_next_n();
    if (n == -1) { break; }

    std::vector<int> seq = get_collatz_sequence(n);
    dump_seq(seq);
  }
}

std::vector<int> get_longest_sequence_threaded(int n, const int num_threads) {
  end = n;

  std::vector<std::thread> threads(num_threads);
  for (int i = 0; i < num_threads; i++) {
    threads[i] = std::thread(&thread_worker);
  }

  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  return longest_seq;
}
