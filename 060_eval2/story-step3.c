#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "wrong input\n");
    return EXIT_FAILURE;
  }
  FILE * fwords = fopen(argv[1], "r");
  if (fwords == NULL) {
    fprintf(stderr, "%s does not exist\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * fstory = fopen(argv[2], "r");
  if (fstory == NULL) {
    fprintf(stderr, "%s does not exist\n", argv[2]);
    return EXIT_FAILURE;
  }
  catarray_t * ans = readfromwords(fwords);
  text_t * t = parseStory(fstory, ans, 1);
  printOut(t);
  freeCatArray(ans);
  freeText(t);
  if (fclose(fwords) == -1) {
    fprintf(stderr, "can't close %s file", argv[1]);
    return EXIT_FAILURE;
  }
  if (fclose(fstory) == -1) {
    fprintf(stderr, "can't close %s file", argv[2]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
