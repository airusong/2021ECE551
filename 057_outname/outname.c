#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * suffix = ".counts";
  int inputLen = strlen(inputName);
  int suffixLen = strlen(suffix);
  char * outputFile = malloc((inputLen + suffixLen + 1) * sizeof(*outputFile));
  strcpy(outputFile, inputName);
  strcat(outputFile, suffix);
  return outputFile;
  //WRITE ME
}
