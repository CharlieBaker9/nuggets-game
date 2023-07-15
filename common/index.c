/*
 * index.c - a C program which defines a a module providing the data structure 
      to represent the in-memory index, and functions to read and write index files
 *
 * Charlie Baker, Apr 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/mem.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"

/**************** global types ****************/
typedef struct index {      //hashtable where key is 'word' and item is counters for word
  struct hashtable *ht;  
} index_t;

/**************** index_new() ****************/
/* see index.h for description */
index_t*
index_new(const int slotSize)
{
  index_t* index = mem_malloc(sizeof(index_t));

  if (index == NULL) {
    return NULL;        //error allocating index
  } else {
    hashtable_t* wordHashtable = hashtable_new(slotSize);
    index->ht = wordHashtable;
    return index;
  }
}

/**************** index_insert() ****************/
/* see index.h for description */
void
index_insert(index_t* index, void* word, void* docID)
{
  if (index != NULL && word != NULL && docID != NULL) {
    counters_t* counter;
    int docIDInt = atoi(docID);
    if((counter = hashtable_find(index->ht, word)) == NULL){
      counters_t* newCounter = counters_new();
      counters_add(newCounter, docIDInt);
      hashtable_insert(index->ht, word, newCounter);
    } else {
      counters_add(counter, docIDInt);
    }
  }

#ifdef MEMTEST
  mem_report(stdout, "After index_insert");
#endif
}

/**************** counters_print() ****************/
/* see index.h for description */
void
idx_counters_print(void *arg, const int key, const int count){
  fprintf(arg, " %d %d", key, count);
}

/**************** index_print() ****************/
/* see index.h for description */
void
index_print(void *arg, const char *key, void *item){
  fprintf(arg, "%s", key);
  counters_iterate(item, arg, idx_counters_print);
  fprintf(arg, "\n");
}

/**************** index_save() ****************/
/* see index.h for description */
void
index_save(index_t* index, FILE* fp)
{
  hashtable_iterate(index->ht, fp, index_print);
}

/**************** index_from_file() ****************/
/* see index.h for description */
index_t*
index_from_file(char* filename){
  FILE* fp = fopen(filename, "r");
  if (fp == NULL){
    fprintf(stderr, "Error opening filename to read from");
    return NULL;
  }
  int wordCount = file_numLines(fp);
  index_t* index = index_new(wordCount);

  char* currWord;
  for (int i = 0; i < wordCount; i++){
    currWord = file_readWord(fp);

    counters_t* counters = counters_new();
    int docID;
    int count;

    while(fscanf(fp, "%d %d", &docID, &count) == 2){
      counters_set(counters, docID, count);
    }

    hashtable_insert(index->ht, currWord, counters);
    free(currWord);
  }

  fclose(fp);
  return index;
}

/**************** counter_delete() ****************/
/* see index.h for description */
void
counter_delete(void *arg, const char *key, void *item)
{
  counters_delete(item);

#ifdef MEMTEST
  mem_report(stdout, "After index_insert");
#endif
}

/**************** index_find() ****************/
/* see index.h for description */
void*
index_find(index_t* index, char* key)
{
  void* result = NULL;
  if (index != NULL) {
    result = hashtable_find(index->ht, key);
  }
  return result;
}

/**************** index_delete() ****************/
/* see index.h for description */
void
index_delete(index_t* index)
{
  if (index != NULL) {
    hashtable_t* ht = index->ht;
    hashtable_iterate(ht, NULL, counter_delete);
    hashtable_delete(ht, NULL);
    free(index);
  }

#ifdef MEMTEST
  mem_report(stdout, "After index_insert");
#endif
}


