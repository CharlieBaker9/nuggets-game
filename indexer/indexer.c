/*
 * indexer.c - a C program which...
 * Charlie Baker, Apr 2023
 */

#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"
#include "../libcs50/webpage.h"

static index_t* indexBuild(char** pageDirectory, const int slotSize);
static void indexPage(webpage_t* page, index_t* index, int docID, const int slotSize);

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
    fprintf(stderr, "Invalid page directory crawler path");
    return 1;
  }
  if (access(argv[1], W_OK) != 0) {
    fprintf(stderr, "Invalid page directory -- read-only directory");
    return 1;
  }
  
  const int slotSize = 900;
  index_t* index = indexBuild(&argv[1], slotSize);

  if (index == NULL){
    fprintf(stderr, "Error building index");
    return 1;
  }

  FILE* fp = fopen(argv[2], "w");
  if (fp == NULL){
    fprintf(stderr, "Error opening indexfilename for writing");
    return 1;
  }

  index_save(index, fp);
  index_delete(index);

  fclose(fp);

  return 0;
}

static index_t* 
indexBuild(char** pageDirectory, const int slotSize){
  index_t* index = index_new(slotSize);
  if (index == NULL){
    fprintf(stderr, "Index build failed");
    return NULL;
  }

  int docID = 1;
  webpage_t* page;
  while ((page = pagedir_load(*pageDirectory, docID)) != NULL){
    indexPage(page, index, docID, slotSize);
    docID++;
    webpage_delete(page);
  }

  return index;
}

static void 
indexPage(webpage_t* page, index_t* index, int docID, const int slotSize){
  int pos = 0;
  char* currWord;
  while ((currWord = webpage_getNextWord(page, &pos)) != NULL){
    if (strlen(currWord) >= 3){
      currWord = normalizeWord(currWord);
      index_insert(index, currWord, &docID);
    }
    free(currWord);
  }
}