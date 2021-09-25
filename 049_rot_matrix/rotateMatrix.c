#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void rotate(FILE * f) {
  int row = 0;
  int col = 0;
  int c;
  char matrix[10][10] = {"0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000"};
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (col > 9 || row > 9) {
        fprintf(stderr, "Invalid matrix");
        exit(EXIT_FAILURE);
      }
      else {
        if (c < 0 || c > 255) {
          fprintf(stderr, "Invalid character");
        }
        else {
          matrix[row][col] = c;
          col++;
        }
      }
    }
    else {
      if (col != 10) {
        fprintf(stderr, "Invalid matrix\n");
        exit(EXIT_FAILURE);
      }
      else {
        col = 0;
        row++;
      }
    }
  }
  if (row != 10 || col != 0) {
    fprintf(stderr, "Invalid matrix\n");
    exit(EXIT_FAILURE);
  }
  for (int j = 0; j < 10; j++) {
    for (int i = 9; i >= 0; i--) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage:rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
