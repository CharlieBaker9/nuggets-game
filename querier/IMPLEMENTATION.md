# IMPLEMENTATION of querier

## Overview
The querier module parses queries and creates a list of most relevant documents based on appearances of words in the query in those documents

## Querier.c static methods that are all accessed either directly or indirectly by the main function

***prompt*** -- prompts the user for their query
```c
static void prompt(void);
```
***validate*** -- prompts the user for their query
```c
static bool validate(char* line);
```
***countWords*** -- counting the words in the query to be used in later functions
```c
static int countWords(char* line);
```
***tokenize*** -- tokenizes the query into an array of words
```c
static bool tokenize(char* input, char* words[], const int wordCount);
```
***cleanWords*** -- changes all letters to lowercase by callign normalizeWord()
```c
static char** cleanWords(char** words, int wordCount);
```
***satisfy*** -- iterates through the cleaned query and returns a counter of all the docID's that satisfy the query and their scores
```c
static counters_t* satisfy(index_t* index, char** cleanedWords, int wordCount);
```
***firstLastCheck*** -- checks to make sure that literals do not exist at the beginning or end of the query line
```c
static bool firstLastCheck(char** words, int wordCount);
```
***literalValidation*** -- checks to make sure that no literals are adjacent to each other
```c
static bool literalValidation(char** words, int wordCount);
```
***countersUnion*** -- function which returns the union of two counters by iterating through them both and calling a helper function to add counts
```c
static counters_t* countersUnion(counters_t* first, counters_t* second);
```
***countersUnionHelper*** -- helper function for countersUnion and adds counts together from two counters for a certain DocID
```c
static void countersUnionHelper(void* counter, const int key, const int count);
```
***countersIntersect*** -- function which returns the intersection of two counters by iterating through them both and calling helper functions
```c
static counters_t* countersIntersect(counters_t* first, counters_t* second);
```
***countersIntersectHelper*** -- helper function for countersIntersect, called by counters_iterate and sets count to min of two values for a certain docID
```c
static void countersIntersectHelper(void* counter, const int key, const int count);
```
***countersIntersectCleaner*** -- helper function for countersIntersect, called by counters_iterate and gets rid of docID's with counts of 0
```c
static void countersIntersectCleaner(void* counter, const int key, const int count);
```
***printScores*** -- prints the scores and URL's of documents in descending order in a certain format
```c
static void printScores(counters_t* docs, char* pageDirectory);
```
***printScoresHelper*** -- helper function to printScores called by counters_iterate and pulls out max docID and count 
```c
static void  printScoresHelper(void* arg, const int key, const int count);
```
***docCount*** -- returns the number of documents whose counts are greater than 0
```c
static void docCount(void *arg, const int key, int count);
```
***min*** -- returns the min of two integers
```c
static int min(int a, int b);
```

## Testing Plan
I plan to test my querier in three ways with the same pageDirectory and indexFilename
1. Through a file filled with inputs that all have different syntax errors to stress test it and make the most obvious errors do not slip through the cracks
2. Through a file filled with inputs that come from a file created by fuzzquery
3. Through a file filled with valid inputs.
