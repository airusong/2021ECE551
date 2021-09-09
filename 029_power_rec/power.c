#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y) {
  if (x == 0) {
    return 0;
  }
  if (y == 0) {
    return 1;
  }
  return x * power(x, y - 1);
}
