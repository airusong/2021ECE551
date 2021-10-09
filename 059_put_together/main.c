#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"
void removeNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can't open the file");
    exit(EXIT_FAILURE);
  }
  char * curr = NULL;
  size_t sz = 0;
  while (getline(&curr, &sz, f) >= 0) {
    removeNewLine(curr);
    addCount(counts, lookupValue(kvPairs, curr));
    //WRITE ME
  }
  free(curr);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close the file");
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "at least two files");
    exit(EXIT_FAILURE);
  }
  //WRITE ME (plus add appropriate error checking!)
  kvarray_t * kv = readKVs(argv[1]);
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  for (int i = 2; i < argc; i++) {
    //count from 2 to argc (call the number you count i)
    counts_t * c = countFile(argv[i], kv);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    char * outName = computeOutputFileName(argv[i]);
    //compute the output file name from argv[i] (call this outName)
    FILE * f = fopen(outName, "w");
    //open the file named by outName (call that f)
    printCounts(c, f);
    //print the counts from c into the FILE f
    if (fclose(f) != 0) {
      //close f
      fprintf(stderr, "can't close file %d", i);
      exit(EXIT_FAILURE);
      //free the memory for outName and c
    }
    //free the memory for kv
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
