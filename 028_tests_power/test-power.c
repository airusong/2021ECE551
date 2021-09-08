#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned, unsigned);

void check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  check(0, 0, 1);
  check(0, 1, 0);
  check(1, 0, 1);
  check(4, 3, 64);
  check(12345678, 1, 12345678);
  return EXIT_SUCCESS;
}
