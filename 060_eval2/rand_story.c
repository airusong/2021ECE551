#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int check(char * cat) {
  char * ptr = cat;
  while (*ptr != '\0') {
    if (*ptr >= 48 && *ptr <= 57) {
      ptr++;
    }
    else {
      return -1;
    }
  }
  return 1;
}
void freeCategory(category_t * cats) {
  for (size_t i = 0; i < cats->n_words; i++) {
    free(cats->words[i]);
  }
  free(cats->name);
  free(cats->words);
  free(cats);
}
int checkduplicateName(char * name, catarray_t * cats) {
  for (int i = 0; i < cats->n; i++) {
    //if already have the category name
    if (!strcmp(name, cats->arr[i].name)) {
      return i;  //return the duplicate position
    }
  }
  return -1;  //no duplicate name,return -1
}
void removeWords(const char * word, catarray_t * cats, size_t index) {
  //make sure the word index in the category
  //   first find the category struct,
  //   compare each word with the used word
  size_t pos = 0;
  for (size_t i = 0; i < (cats->arr[index]).n_words; i++) {
    if (strcmp((cats->arr[index]).words[i], word) == 0) {
      pos = i;
    }
  }
  category_t
      ans;  //create a new category struct to save the unused word under the category
  ans.name = cats->arr[index].name;
  ans.n_words = 0;
  ans.words = NULL;

  size_t i = 0;
  for (size_t j = 0; j < (cats->arr[index]).n_words; j++) {
    if (j == pos) {
      continue;  //skip the used word
    }
    ans.words = realloc(
        ans.words,
        (i + 1) * sizeof(*(ans.words)));  //reallocate new position for the next word
    ans.words[i] = cats->arr[index].words[j];
    cats->arr[index].words[j] = NULL;
    i++;
  }
  ans.n_words = i;  //the number of the word after deletion
  cats->arr[index].n_words--;
  //free the initial word array under that category and allocate a new array to save the unused words array
  free(cats->arr[index].words);
  cats->arr[index].words =
      malloc(cats->arr[index].n_words * sizeof(*cats->arr[index].words));
  //use a for loop to to save the new word array
  for (size_t i = 0; i < cats->arr[index].n_words; i++) {
    cats->arr[index].words[i] = ans.words[i];
    ans.words[i] = NULL;
  }
  ans.name = NULL;
}
const char * findWord(char * cat, catarray_t * cats, category_t * used, int reuse) {
  if (cats == NULL) {
    return chooseWord(cat, cats);
  }
  //the category name is a category in the catarray_t
  //call chooseWord, return a random choice from that category and reuse is permitted
  if (checkduplicateName(cat, cats) != -1 && reuse == 1) {
    const char * word = chooseWord(cat, cats);
    return word;
  }
  //category name is a category in the catarray_t ,and no reuse is permitted
  else if (checkduplicateName(cat, cats) != -1 && reuse == 0) {
    const char * nword = chooseWord(cat, cats);
    //remove the previously used word in the same category
    removeWords(nword, cats, (unsigned int)(checkduplicateName(cat, cats)));
    return nword;
  }
  //category name is a valid integer of at least one,replace
  //the blank with a previously used word
  size_t number = (unsigned int)(atoi(cat));
  if (number <= used->n_words && number >= 1) {
    const char * usedword = used->words[used->n_words - number];
    return usedword;
  }  // If a category name is neither a
     //valid integer nor a valid category name, exit with a
     //failure status.
  else {
    fprintf(stderr, "invalid content between underscore");
    exit(EXIT_FAILURE);
  }
}
char * getName(char * curr) {
  char * ptr = strchr(curr, ':');
  if (ptr == NULL) {  //situation without semicolon
    fprintf(stderr, "invalid name and words input");
    exit(EXIT_FAILURE);
  }
  *ptr = '\0';  //seperate name and words
  char * name = strdup(curr);
  return name;
}

char * getWord(char * curr) {
  char * ptr1 = strchr(curr, ':');
  if (ptr1 == NULL) {  //situation without semicolon
    fprintf(stderr, "invalid words input");
    exit(EXIT_FAILURE);
  }
  char * ptr2 = strchr(curr, '\n');
  if (ptr2 != NULL) {
    *ptr2 = '\0';  //strip newline at the end of one line
  }
  ptr1++;
  char * word = strdup(ptr1);
  return word;
}
void addName(catarray_t * cat, char * name, char * word) {
  cat->arr = realloc(cat->arr, (cat->n + 1) * sizeof(*cat->arr));
  cat->arr[cat->n].name = name;
  cat->arr[(cat->n)].n_words = 0;
  cat->arr[(cat->n)].words = NULL;
  cat->arr[(cat->n)].words =
      realloc(cat->arr[(cat->n)].words,
              (++cat->arr[cat->n].n_words) * sizeof(*(cat->arr[(cat->n)].words)));
  cat->arr[(cat->n)].words[0] = word;
  cat->n++;
}
void addWord(catarray_t * cat, char * word, size_t i) {
  cat->arr[i].words = realloc(cat->arr[i].words,
                              (cat->arr[i].n_words + 1) * sizeof(*(cat->arr[i].words)));
  cat->arr[i].words[cat->arr[i].n_words] = word;
  cat->arr[i].n_words++;
}
catarray_t * readfromwords(
    FILE * f) {  //read from the word.txt file and classify the category name and word
  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;  //initialize the struct for category name and words
  char * curr = NULL;
  size_t sz = 0;
  while ((getline(&curr, &sz, f)) >= 0) {
    char * word = getWord(curr);
    char * name = getName(curr);
    int index = checkduplicateName(name, ans);
    if (index == -1) {
      //no duplicate, add a new category name
      addName(ans, name, word);
    }
    else {
      free(name);  //duplicate name, just add a new word
      addWord(ans, word, index);
    }
    //    curr = NULL;
  }
  free(curr);
  return ans;
}
void freeCatArray(catarray_t * arr) {
  for (size_t i = 0; i < arr->n; i++) {
    for (size_t j = 0; j < arr->arr[i].n_words; j++) {
      free(arr->arr[i].words[j]);
    }
    free(arr->arr[i].words);
    free(arr->arr[i].name);
  }
  free(arr->arr);
  free(arr);
}
void updateUsed(const char * word, category_t * used) {
  used->n_words++;
  used->words = realloc(used->words, (used->n_words) * sizeof(*used->words));
  used->words[used->n_words - 1] = strdup(word);
}
char * substitute(char * line, catarray_t * cats, int reuse, category_t * used) {
  //find the undersocre and subsititute with corresponding word
  char * ptr = line;
  char * result = NULL;  //initialize the result after filling in the word
  char * cat = NULL;     //initialize the category name
  size_t len = 0;        //initialize the length of  category name
  int count = 0;         //length of the result after subsititution
  int flag = 0;  //use a flag to show if the ptr is between the right underscore interval
  while (*ptr != '\0') {
    if (*ptr != '_') {  //before a underscore
      if (flag == 0) {
        result = realloc(result, (count + 2) * sizeof(*result));
        result[count] = *ptr;  //copy the char out of the undersocre area
        result[count + 1] = '\0';
        count++;
        ptr++;
      }
      else {                                           //between a underscore
        cat = realloc(cat, (len + 1) * sizeof(*cat));  //record the category name
        cat[len] = *ptr;
        len++;
        ptr++;
      }
    }
    else if (*ptr == '_') {
      if (flag == 0) {  //the first underscore,go pass
        ptr++;
        flag = 1;
      }
      else {  //end of a underscore
        cat = realloc(cat, (len + 1) * sizeof(*cat));
        cat[len] = '\0';
        len = 0;
        const char * word = findWord(cat, cats, used, reuse);
        result = realloc(result, (count + strlen(word) + 1) * sizeof(*result));
        result = strcat(
            result,
            word);  //recored the substitution result after finding the word under category
        flag = 0;
        ptr++;
        count = count + strlen(word);
        result[count] = '\0';
        updateUsed(word, used);  //update the used array
        cat = NULL;
      }
    }
  }
  free(cat);
  if (flag == 1) {
    exit(EXIT_FAILURE);
  }
  return result;
}

category_t * createUsed(void) {  //creat a struct for the used words
  category_t * used = malloc(sizeof(*used));
  used->n_words = 0;
  used->words = NULL;
  used->name = strdup("usedWord");
  return used;
}
text_t * parseStory(FILE * f,
                    catarray_t * cats,
                    int reuse) {  //store the file in char array
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  category_t * used = createUsed();
  text_t * ans = malloc(sizeof(*ans));
  while (getline(&curr, &sz, f) >= 0) {
    ans->input = realloc(ans->input, (i + 1) * sizeof(*ans->input));
    curr = substitute(curr, cats, reuse, used);
    ans->input[i] = strdup(curr);
    curr = NULL;
    i++;
  }
  ans->n = i;
  free(curr);
  freeCategory(used);
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
