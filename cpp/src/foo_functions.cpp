#include <algorithm>
#include <string>

#include "foo_functions.h"

std::string foo_message() {
  return "Foo message";
}

int get_collatz_length(int n) {
  int length = 0;

  uint64_t x = uint64_t(n);

  while (x != 1) {
    if (x%2 == 0) {
      x = x/2;
    }
    else {
      x = x*3+1;
    }
    length++;
  }

  return length;
}

int foo_collatz(int n) {
  int longest = 0;

  for (int i = 1; i < n+1; i++) {
    int length = get_collatz_length(i);
    longest = std::max(longest, length);
  }

  return longest;
}
