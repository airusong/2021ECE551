#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
size_t getEqualPos(const char * str) {
  size_t returnIndex = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (*(str + i) == '=') {
      returnIndex = i;
      break;
    }
  }
  return returnIndex;
}
void stripNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
kvarray_t * read_kv_from_file(FILE * f) {
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->kvpairs = NULL;
  ans->length = 0;  // the count of kv pairs
  char * str = NULL;
  size_t sz = 0;
  size_t i = 0;
  size_t firstEqual = 0;
  while ((getline(&str, &sz, f)) >= 0) {
    ans->kvpairs = realloc(ans->kvpairs, (i + 1) * sizeof(*(ans->kvpairs)));
    ans->length++;
    ans->kvpairs[i] = NULL;
    ans->kvpairs[i] = malloc(sizeof(*ans->kvpairs[i]));
    stripNewLine(str);
    firstEqual = getEqualPos(str);
    ans->kvpairs[i]->key = strndup(str, firstEqual);
    ans->kvpairs[i]->value = strdup(str + firstEqual + 1);
    i++;
  }
  free(str);
  return ans;
}
kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("could not open file");
    return NULL;
  }
  kvarray_t * answer = read_kv_from_file(f);

  if (fclose(f)) {
    fprintf(stderr, "Can not close file.\n");
    exit(EXIT_FAILURE);
  }

  return answer;  //WRITE ME
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->kvpairs[i]->key);
    free(pairs->kvpairs[i]->value);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i]->key, pairs->kvpairs[i]->value);
  }
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->length; i++) {
    if (!strcmp(key, pairs->kvpairs[i]->key)) {
      return pairs->kvpairs[i]->value;
    }
  }
  return NULL;  //WRITE ME
}
