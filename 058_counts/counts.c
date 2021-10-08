#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    return NULL;
  }
  ans->array = NULL;
  ans->unknown = 0;
  ans->size = 0;
  return ans;  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown++;
  }
  else {
    int check = 1;
    for (int i = 0; i < c->size; i++) {
      if (!strcmp(c->array[i]->string, name)) {  //WRITE ME
        c->array[i]->time++;
        check = 0;
      }
    }
    if (check == 1) {
      c->size++;
      c->array = realloc(c->array, (c->size) * sizeof(*(c->array)));
      one_count_t * onecount = malloc(sizeof(*onecount));
      c->array[c->size - 1] = onecount;
      c->array[c->size - 1]->string = strdup(name);
      c->array[c->size - 1]->time = 1;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s:%d\n", c->array[i]->string, c->array[i]->time);
  }
  if (c->unknown > 0) {
    fprintf(outFile, "<unknown>:%d\n", c->unknown);
  }

  //WRITE ME
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->size; i++) {
    free(c->array[i]->string);
    free(c->array[i]);
  }
  free(c->array);
  free(c);  //WRITE ME
}
