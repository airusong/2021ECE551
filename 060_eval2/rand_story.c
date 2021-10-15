#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//char * findWord(char * cat, catarray_t * cats, category_t * track) {
//}
char * getName(char * curr) {
}
char * getWord(char * curr) {
}
int checkduplicateName(char * name, catarray_t * cats) {
}
catarray_t * readfromwords(FILE * f) {
  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while ((getline(&curr, &sz, f)) >= 0) {
    char * name = getName(curr);
    char * word = getWord(curr);
    if (!(checkduplicateName(name, ans))) {
    }
    else {
    }
  }
  return ans;
}
char * substitute(char * line, catarray_t * cats, int reuse, category_t * track) {
  char * ptr = line;
  char * result = NULL;
  char * cat = NULL;
  size_t len = 0;
  int count = 0;
  int flag = 0;
  while (*ptr != '\0') {
    if (*ptr != '_') {  //before a underscore
      if (flag == 0) {
        result = realloc(result, (count + 1) * sizeof(*result));
        result[count] = *ptr;
        count++;
        ptr++;
      }
      else {  //between a underscore
        cat = realloc(cat, (len + 1) * sizeof(*cat));
        cat[len] = *ptr;
        len++;
        ptr++;
      }
    }
    else if (*ptr == '_') {  //the first underscore
      if (flag == 0) {
        ptr++;
        flag = 1;
      }
      else {  //end of a underscore
        cat = realloc(cat, (len + 1) * sizeof(*cat));
        cat[len] = '\0';
        const char * word = chooseWord(cat, cats);
        result = realloc(result, (count + strlen(word) + 1) * sizeof(*result));
        result = strcat(result, word);
        flag = 0;
        ptr++;
        count = count + strlen(word);

        track->n_words++;
        track->words = realloc(track->words, (track->n_words) * sizeof(*track->words));
        track->words[track->n_words - 1] = strdup(word);
      }
    }
  }
  free(cat);
  if (flag == 1) {
    exit(EXIT_FAILURE);
  }
  return result;
}

category_t * creatTrack(void) {  //creat a
  category_t * track = malloc(sizeof(*track));
  track->n_words = 0;
  track->words = NULL;
  track->name = strdup("used");
  return track;
}
text_t * parseStory(FILE * f,
                    catarray_t * cats,
                    int reuse) {  //store the file in char array
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  category_t * track = creatTrack();
  text_t * ans = malloc(sizeof(*ans));
  while (getline(&curr, &sz, f) >= 0) {
    ans->input = realloc(ans->input, (i + 1) * sizeof(*ans->input));
    curr = substitute(curr, cats, reuse, track);
    ans->input[i] = curr;
    curr = NULL;
    i++;
  }
  ans->n = i;
  free(curr);
  free(track);
  return ans;
}
void printOut(text_t * t) {  //print out the updated version
  for (size_t i = 0; i < t->n; i++) {
    printf("%s", t->input[i]);
  }
}
void freeText(text_t * t) {
  for (size_t i = 0; i < t->n; i++) {
    free(t->input[i]);
  }
  free(t->input);
  free(t);
}
