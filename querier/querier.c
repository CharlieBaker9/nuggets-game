/*
 * indexer.c - a C program which...
 * Charlie Baker, Apr 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/pagedir.h"
#include "../common/word.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/mem.h"
#include "../libcs50/webpage.h"

static void prompt(void);
static bool validate(char* line);
static bool tokenize(char* input, char* words[], const int wordCount);
static int countWords(char* line);
static char** cleanWords(char** words, int wordCount);
static counters_t* satisfy(index_t* index, char** cleanedWords, int wordCount);
static bool firstLastCheck(char** words, int wordCount);
static bool literalValidation(char** words, int wordCount);
static counters_t* countersUnion(counters_t* first, counters_t* second);
static void countersUnionHelper(void* counter, const int key, const int count);
static counters_t* countersIntersect(counters_t* first, counters_t* second);
static void countersIntersectHelper(void* counter, const int key, const int count);
static void countersIntersectCleaner(void* counter, const int key, const int count);
static void printScores(counters_t* docs, char* pageDirectory);
static void  printScoresHelper(void* arg, const int key, const int count);
static void docCount(void *arg, const int key, int count);
static int min(int a, int b);

int 
main(const int argc, char* argv[]) 
{
  if (argc != 3){
    fprintf(stderr, "invalid number of arguments -- must have two arguments (pageDirectory indexFilename)\n");
    return 1;
  }

  //validate parameters
  bool valid = pagedir_validate(argv[1]);
  if (!valid){
    fprintf(stderr, "Invalid page directory crawler path\n");
    return 1;
  }
  if (access(argv[1], R_OK) != 0) { //check if pagedirectory can be read
    fprintf(stderr, "Invalid pageDirectory -- .crawler cannot be read\n");
    return 1;
  }
  if (access(argv[2], F_OK) != 0) {   //check if the file does not exist
    fprintf(stderr, "Invalid indexFilename -- file does not exist\n");
    return 1;
  }
  if (access(argv[2], R_OK) != 0) {   //check if the filename can be read
    fprintf(stderr, "Invalid indexFilename -- cannot be read\n");
    return 1;
  }

  index_t* index = index_from_file(argv[2]);    //loading index in

  char* input;
  prompt();
  while ((input = file_readLine(stdin)) != NULL){   //reading in queries line by line
    bool allSpaces = true;
    for (int i = 0; input[i] != '\0'; i++){   //for loop to see if input is all spaces
      if (!isspace(input[i])){ 
        allSpaces = false;
      }
    }
    if (allSpaces || strlen(input) == 0){ //prompts new query if all spaces or len=0
      free(input);
      prompt();
      continue;
    }

    if (!validate(input)){    //calls method to check that all characters are either spaces or letters
      fprintf(stderr, "Invalid input contains a character that is not a letter or space\n");
      free(input);
      prompt();
      continue;
    }

    int wordCount = countWords(input);
    char* words[wordCount];
    if (!tokenize(input, words, wordCount)) {   //tokenizes the words into an array of chars
      fprintf(stderr, "error tokenizing input '%s'\n", input);
      return 1;
    }
    char** cleanedWords = cleanWords(words, wordCount); //lowercase words using helper function

    printf("%s", "Query: ");  //prints the cleaned query if all previous checks pass
    for (int i = 0; i < wordCount; i++) { 
      printf("%s%s", cleanedWords[i], " "); 
    } 
    printf("\n");

    if (!literalValidation(words, wordCount)){    //validates literals are not beginning, end, or adjacent
      free(input);
      prompt();
      continue;
    }

    counters_t* docs = satisfy(index, cleanedWords, wordCount);   //sees which docID's satisfy the query

    int size = 0;
    counters_iterate(docs, &size, docCount);    //finds number of docs that satisfy

    if (size == 0){
      printf("%s\n", "No Documents match.");
    } else {
      printf("%s%d%s\n", "Matches ", size, " documents (ranked):");   //prints header before scores
      printScores(docs, argv[1]);   //prints scores of docIDs
    }

    counters_delete(docs); 
    free(input);
    prompt();
  }

  printf("\n");
  index_delete(index);
  return 0;
}

static void
prompt(void){
  int fileno(FILE *stream);
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
}

static bool
validate(char* line){     //validates all characters are spaces or letters
  if ((line[0] == '\0') | (line == NULL)){
    return false;
  }
  for (int i = 0; line[i] != '\0'; i++){
    if (!isalpha(line[i]) && !isspace(line[i])){
      return false;
    }
  }
  return true;
}

static int
countWords(char* line){   //count number of words in the line
  int count = 0;
  bool spaceLast = true;
  int i = 0;
  while (i < strlen(line)){
    while(isalpha(line[i])){
      i++;
      spaceLast = false;
    }
    if (!spaceLast){
      count++;
    }
    spaceLast = true;
    i++;
  }
  return count;
}

static bool 
tokenize(char* input, char* words[], const int wordCount){      //tokenizes the input into an array
  if (input == NULL || words == NULL || wordCount < 1) {
    return false;
  }
  char* l = input;
  while (*l != '\0') { // iterate until end of string
    if (!isspace(*l)) { // check if current character is not a space
      break;
    }
    l++; // move to next character
  }

  for (int w = 0; w < wordCount; w++){
    words[w] = l;            // field begins here
    char* p = strchr(l, ' '); // find the next space
    if (p == NULL) {          // space not found
      if (w < wordCount - 1) {  // error if not the last word
        return false;
      }
    } else {                  // space found 
      int count = 1;
      *p = '\0';              // terminate at the space
      l = p+count;                // move l past the space
      while (l[0] == 32){
        count++;
        l = p+count;
      }
    }
  }
  return true;
}

static char**
cleanWords(char** words, int wordCount){ //makes all letters lowercase with normalize function
  for (int i = 0; i < wordCount; i++) { 
    words[i] = normalizeWord(words[i]);
  } 
  return words;
}

static bool
literalValidation(char** words, int wordCount){ //validates literals are not adjacent or at beginning or end
  if (!firstLastCheck(words, wordCount)){
    return false;
  }
  char* currLiteral;
  bool literal;
  for (int i = 0; i < wordCount; i++){
    if (((strcmp(words[i], "and") == 0) || (strcmp(words[i], "or") == 0)) && literal ) {
      fprintf(stderr, "%s%s%s%s%s\n", "Error: '", currLiteral, "' and '", words[i], "' cannot be adjacent");
      return false;
    } else if (strcmp(words[i], "and") == 0){
      currLiteral = words[i];
      literal = true;
    } else if (strcmp(words[i], "or") == 0){
      currLiteral = words[i];
      literal = true;
    } else {
      literal = false;
    }
  }
  return true;
}

static counters_t* 
satisfy(index_t* index, char** words, int wordCount){   //checks to see which docs satisfy the query
  counters_t* base = counters_new();
  counters_t* temp;
  int i = 0;
  while (i < wordCount){
    if (strcmp(words[i], "and") == 0){  //continue on and
      i++;
      continue;
    } else if (strcmp(words[i], "or") == 0){  //if or we create a new temporary counter which builds until end of query or another or statement
      i++;
      temp = counters_new();
      countersUnion((counters_t*) index_find(index, words[i]), temp);
      while ((strcmp(words[i], "or") != 0) && (i != wordCount-1)){
        if (strcmp(words[i], "and") != 0){
          counters_t* nextWord = (counters_t*) index_find(index, words[i]);
          counters_t* intersectTemp = countersIntersect(nextWord, temp);
          counters_delete(temp);
          temp = counters_new();
          countersUnion(intersectTemp, temp); //we join new intersect temp with overall temp counters to bring down 
          counters_delete(intersectTemp);
        }
        i++;  //iterate to next word to bring into "and sequence" before next or
      }
      countersUnion(temp, base);
      counters_delete(temp);
    } else {    //if it is a word we use temp to combine with main
      if (i == 0){    //first word is base as it is the only thing to satisfy
        temp = (counters_t*) index_find(index, words[i]);
        countersUnion(temp, base);
      } else {    //else the base depends off of an intersection with temp
        temp = (counters_t*) index_find(index, words[i]);
        counters_t* final = countersIntersect(temp, base);
        counters_delete(base);
        base = counters_new();
        countersUnion(final, base);
        counters_delete(final);
      }
    }
    i++;
  }
  counters_print(base, stdout);
  printf("\n");
  return base;
}

static bool firstLastCheck(char** words, int wordCount){    //helper function to check if literals are first or last in query
  if ((strcmp(words[0], "and") == 0) || (strcmp(words[0], "or") == 0)){
    fprintf(stderr, "%s%s%s\n", "Error: '", words[0], "' cannot be first");
    return false;
  } else if ((strcmp(words[wordCount-1], "and") == 0) || (strcmp(words[wordCount-1], "or") == 0)){
    fprintf(stderr, "%s%s%s\n", "Error: '", words[wordCount-1], "' cannot be last");
    return false;
  }
  return true;
}

static counters_t*
countersUnion(counters_t* first, counters_t* second){   //union of two counters
  counters_iterate(first, second, countersUnionHelper);
  return second;
}

static void
countersUnionHelper(void* counter, const int key, const int count){ //union of two counters helper
  int prevCount = counters_get((counters_t*) counter, key);
  counters_set((counters_t*) counter, key, prevCount + count);
}

static counters_t*
countersIntersect(counters_t* first, counters_t* second){   //intersect of two counters
  counters_t* temp1 = counters_new();
  countersUnion(first, temp1);
  counters_iterate(first, second, countersIntersectHelper);
  counters_iterate(second, temp1, countersIntersectHelper);
  counters_t* cleanedCounter = counters_new();
  counters_iterate(temp1, cleanedCounter, countersIntersectCleaner);
  counters_delete(temp1);
  return cleanedCounter;
}

static void
countersIntersectHelper(void* counter, const int key, const int count){  //intersect of two counters helper
  int prevCount = counters_get((counters_t*) counter, key);
  counters_set((counters_t*) counter, key, min(prevCount, count));
}

static void
countersIntersectCleaner(void* counter, const int key, const int count){  //removes docID's whose counts have been set to 0
  if (count > 0){
    counters_set(counter, key, count);
  }
}

static void 
printScores(counters_t* docs, char* pageDirectory){   //prints the scores in descending order for docID's which satisfy
  int max[2] = {0,1};

  while (max[1] > 0){
    max[0] = 0;     // DocID of max
    max[1] = 0;     // score of max
    counters_iterate(docs, &max, printScoresHelper);
    webpage_t* page = pagedir_load(pageDirectory, max[0]);
    printf("%3s%5d%3s%3d%s%3s\n", "score", max[1], "  doc", max[0], ": ", webpage_getURL(page));
    webpage_delete(page);
    counters_set(docs, max[0], 0);
  }
}

static void 
printScoresHelper(void* arg, const int key, const int count){   //prints next highest in counter
  int* max = (int*) arg;
  if (max[1] < count){
    max[0] = key;
    max[1] = count;
  }
}

static void 
docCount(void *arg, const int key, int count){    //finds count of docID's
    if (count != 0) {
        int *runCount = arg;
        (*runCount)++;
    }
}

static int 
min(int a, int b){    //min of two ints
  if (a < b) {
    return a;
  }
  return b;
}