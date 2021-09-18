#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t result = 0;
  size_t temp = 1;
  if (n > 0) {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        temp++;
      }
      else {
        if (temp > result) {
          result = temp;
        }
        temp = 1;
      }
    }
    if (result < temp) {
      result = temp;
    }
  }
  return result;
}
