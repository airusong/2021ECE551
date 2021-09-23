#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int arrayMax(int * array, int n) {
  int * max;
  int maxIndex = 0;
  max = &array[0];
  for (int i = 1; i < n; i++) {
    if (array[i] > *max) {
      max = &array[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}
int getKey(FILE * f) {
  int c;
  int array[26] = {0};
  int maxIdx;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[tolower(c) - 'a']++;
    }
  }
  maxIdx = arrayMax(array, 26);
  return (maxIdx + 22) % 26;
}
int main(int argc, char ** argv) {
  int key;
  if (argc != 2) {
    fprintf(stderr, "Usage: filename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("fopen");
    fprintf(stderr, "%s does not exist\n", argv[1]);
    return EXIT_FAILURE;
  }
  key = getKey(f);
  printf("%d\n", key);
  fclose(f);
  return EXIT_FAILURE;
}
