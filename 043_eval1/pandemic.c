#include "pandemic.h"

#include "ctype.h"
#include "errno.h"
#include "inttypes.h"
#include "stdio.h"
#include "string.h"
country_t parseLine(char * line) {
  //WRITE ME
  const char * point = line;
  country_t ans;
  if (line == NULL) {  //check if the line is null or not
    fprintf(stderr, "The line pointer is null\n");
    exit(EXIT_FAILURE);
  }
  if (strchr(line, ',') == NULL) {  //check if the line has a comma or not
    fprintf(stderr, "The line do not have a comma\n");
    exit(EXIT_FAILURE);
  }
  ans.name[0] = '\0';
  ans.population = 0;
  int i = 0;
  //read contry
  while ((*point) != ',' && i < MAX_NAME_LEN) {
    ans.name[i] = *point;
    i++;
    point++;
  }  //put char in the array
  if (i != MAX_NAME_LEN) {
    ans.name[i] = '\0';  //add a null terminator
  }
  if (i == MAX_NAME_LEN && *point != ',') {
    fprintf(stderr, "Country name larger than 64 bits");
    exit(EXIT_FAILURE);
  }  //country name out of bound
  //read digit
  if (*point == ',') {
    point++;
  }  //pass the comma
  if (*point == '-') {
    point++;
  }  //check the minus sign if it has
  while (*point >= '0' && *point <= '9') {
    ans.population = ans.population * 10 +
                     (uint64_t)(*point - '0');  ////transform the population value
    point++;
  }
  if (errno == ERANGE) {
    fprintf(stderr, "The population is out of range\n");
    exit(EXIT_FAILURE);
  }  //check if population is out of bound
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  const unsigned * dataP = data;
  double * avgPointer = avg;  //WRITE ME
  if (data == NULL) {
    exit(EXIT_FAILURE);  //check if data is null
  }
  if (n_days <= 6) {
    exit(EXIT_FAILURE);  //check if the date is right
  }
  for (size_t i = 0; i < n_days - 6; i++) {  //caculate the average
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
  }  //check the data pointer
  double * cumP = cum;
  *cumP = (double)(*dataP);
  for (size_t i = 1; i < n_days; i++) {
    *(cum + i) = *(cum + i - 1) +
                 (double)(*(data + i));  //caculate the accumulative cases in n_days
    if (*(cum + i) >
        (double)pop) {  //if the accumulative cases is larger than population,exit failure
      exit(EXIT_FAILURE);
    }
  }
  for (size_t j = 0; j < n_days; j++) {
    *(cum + j) =
        *(cum + j) * 100000 / pop;  //transform the result to cases per 100000 people
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
  //find the max index of the matrix
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
