#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
text_t * parseStory(FILE * f) {
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  text_t * ans = malloc(sizeof(*ans));
  while (getline(&curr, &sz, f) >= 0) {
    ans->input = realloc(ans->input, (i + 1) * sizeof(*ans->input));
    ans->input[i] = curr;
    curr = NULL;
    i++;
  }
  ans->n = i;
  free(curr);
  return ans;
}
void checkUnderscore(text_t * input) {
}
const char * blankWord(char * category, catarray_t * cats) {
  if (cats == NULL) {
    return chooseWord("verb", cats);
  }
}
