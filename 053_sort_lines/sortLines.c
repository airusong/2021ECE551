#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void operation(FILE * stream) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, stream) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    operation(f);
    if (fclose(f) != 0) {
      perror("Failed to close the file");
      return EXIT_FAILURE;
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      operation(f);
      if (fclose(f) != 0) {
        perror("Failed to close the file");
        return EXIT_FAILURE;
      }
    }
  }
  //WRITE YOUR CODE HERE!

  return EXIT_SUCCESS;
}
