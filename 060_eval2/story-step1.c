#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong input\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "%s does not exist\n", argv[1]);
    return EXIT_FAILURE;
  }
  parseStory(f);
  if (fclose(f) == -1) {
    fprintf(stderr, "can't close file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
