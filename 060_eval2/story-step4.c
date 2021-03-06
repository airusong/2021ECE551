#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc == 3 && strcmp(argv[1], "-n") != 0) {
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
  else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    FILE * fwords = fopen(argv[2], "r");
    if (fwords == NULL) {
      fprintf(stderr, "%s does not exist\n", argv[2]);
      return EXIT_FAILURE;
    }
    FILE * fstory = fopen(argv[3], "r");
    if (fstory == NULL) {
      fprintf(stderr, "%s does not exist\n", argv[3]);
      return EXIT_FAILURE;
    }
    catarray_t * ans = readfromwords(fwords);
    text_t * t = parseStory(fstory, ans, 0);
    printOut(t);
    freeCatArray(ans);
    freeText(t);
    if (fclose(fwords) == -1) {
      fprintf(stderr, "can't close %s file", argv[2]);
      return EXIT_FAILURE;
    }
    if (fclose(fstory) == -1) {
      fprintf(stderr, "can't close %s file", argv[3]);
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}
