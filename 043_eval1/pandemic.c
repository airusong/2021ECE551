#include "pandemic.h"

#include "ctype.h"
#include "inttypes.h"
#include "stdio.h"

country_t parseLine(char * line) {
  //WRITE ME
  const char * point = line;
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  int i = 0;
  while ((*point) != ',' && i < MAX_NAME_LEN) {
    ans.name[i] = *point;
    i++;
    point++;
  }
  if (i != MAX_NAME_LEN) {
    ans.name[i] = '\0';
  }
  if (i == MAX_NAME_LEN && *point != ',') {
    fprintf(stderr, "Country name larger than 64 bits or invalid input without a comma");
    exit(EXIT_FAILURE);
  }
  //read digit
  if (*point == ',') {
    point++;
  }
  while (*point >= '0' && *point <= '9') {
    ans.population = ans.population * 10 + (uint64_t)(*point - '0');
    point++;
  }
  if (*point != '\n') {
    fprintf(stderr, "population is wrong");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  const unsigned * dataP = data;
  double * avgPointer = avg;  //WRITE ME
  if (data == NULL) {
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days - 6; i++) {
    *avgPointer = (double)(*dataP + *(dataP + 1) + *(dataP + 2) + *(dataP + 3) +
                           *(dataP + 4) + *(dataP + 5) + *(dataP + 6)) /
                  7;
    dataP++;
    avgPointer++;
  }
}
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  const unsigned * dataP = data;
  if (data == NULL) {
    exit(EXIT_FAILURE);
  }
  double * cumP = cum;
  *cumP = (double)(*dataP);
  for (size_t i = 1; i < n_days; i++) {
    *(cum + i) = *(cum + i - 1) + (double)(*(data + i));
    if (*(cum + i) > (double)pop) {
      exit(EXIT_FAILURE);
    }
  }
  for (size_t j = 0; j < n_days; j++) {
    *(cum + j) = *(cum + j) * 100000 / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  // check the country_t pointer
  if (countries == NULL) {
    fprintf(stderr, "The countries struct is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check data pointer
  if (data == NULL) {
    fprintf(stderr, "The data pointer is invalid!\n");
    exit(EXIT_FAILURE);
  }
  unsigned max = data[0][0];
  size_t maxRow = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        maxRow = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", (*(countries + maxRow)).name, max);
}
