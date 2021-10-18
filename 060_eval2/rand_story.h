#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"
struct text_tag {
  char ** input;
  size_t n;
};
typedef struct text_tag text_t;
const char * chooseWord(char * category, catarray_t * cats);
void printWords(catarray_t * cats);
text_t * parseStory(FILE * f, catarray_t * cats, int reuse);
void printOut(text_t * t);
void freeText(text_t * t);
catarray_t * readfromwords(FILE * f);
void freeCatArray(catarray_t * arr);
//any functions you want your main to use

#endif
