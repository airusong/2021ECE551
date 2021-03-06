#include <stdio.h>
#include <stdlib.h>
void printarray(int array[], size_t n) {
  int i;

  putchar('{');
  for (i = 0; i < n; i++) {
    printf((i == 0) ? "%d" : ", %d", array[i]);
  }
  putchar('}');
}
size_t maxSeq(int *, size_t);

void test_maxSeq(int array[], size_t n, size_t ans) {
  size_t ret;

  ret = maxSeq(array, n);
  printf("expect %zu, got %zu\n", ans, ret);
  if (ret != ans) {
    printf("found a bug !!\narray = ");
    printarray(array, n);
    printf(", n = %zu\n", n);
    exit(EXIT_FAILURE);
  }
}

int main() {
  test_maxSeq(NULL, 0, 0);
  test_maxSeq((int[]){1}, 1, 1);
  test_maxSeq((int[]){2, 2}, 2, 1);
  test_maxSeq((int[]){1, 2, 3, 4, 5}, 5, 5);
  test_maxSeq((int[]){1, 8, 1, 3, 5, 7, 2, 4, 7, 9, 11}, 10, 4);
  test_maxSeq((int[]){-2147483648, 2147483647}, 2, 2);
  return 0;
}
