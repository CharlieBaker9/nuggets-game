/*
 * pagedir.c - a C program which handles writing pages to the pageDirectory, 
 *             and marking them as Crawler-produced pageDirectories
 * Charlie Baker, Apr 2023
 */

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../libcs50/file.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"

// pagedir_init -- initializes page directory 
bool
pagedir_init(const char* pageDirectory){
  char* crawlerPath = malloc(strlen(pageDirectory) + strlen("/.crawler") + 1);
  sprintf(crawlerPath, "%s%s%s", pageDirectory, "/", ".crawler");
  
  FILE* fptr = fopen(crawlerPath,"w");    //open file to write to
  free(crawlerPath);
  if (fptr == NULL){
    fprintf(stderr, "%s/n", "file could not be opened in pagedir_init");
    return false;
  }

  fclose(fptr);
  return true;
}

// pagedir_save -- saves pages to new files
void
pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
  char* filename = malloc(strlen(pageDirectory) + strlen("/") + sizeof(docID) + 1);
  sprintf(filename, "%s%s%d", pageDirectory, "/", docID);

  FILE* fptr = fopen((char*) filename,"w");     //open file to write to

  //printing webpage url, Depth, and HTML to file
  fprintf(fptr, "%s\n", webpage_getURL(page));
  fprintf(fptr, "%d\n", webpage_getDepth(page));
  fprintf(fptr, "%s\n", webpage_getHTML(page));

  free(filename);
  fclose(fptr);
}

bool
pagedir_validate(char* pageDirectory){
  char *crawlerFile = malloc(strlen(pageDirectory) + strlen("/.crawler") + 1);
  sprintf(crawlerFile, "%s%s", pageDirectory, "/.crawler");

  if (crawlerFile == NULL){
    free(crawlerFile);
    return false;
  }

  FILE* fp = fopen(crawlerFile, "r");
  free(crawlerFile);

  if (fp == NULL){
    return false;
  }
  
  fclose(fp);
  return true;
}

webpage_t*
pagedir_load(const char* pageDirectory, int docID){
  char* pageFile = malloc(strlen(pageDirectory) + strlen("/") + sizeof(docID) + 1);
  sprintf(pageFile, "%s%s%d", pageDirectory, "/", docID);
  FILE* fp = fopen(pageFile, "r");
  free(pageFile);

  if (fp == NULL){
    return NULL;
  }

  char* url = file_readLine(fp);
  char* charDepth = file_readLine(fp);
  char* html = file_readFile(fp);
  fclose(fp);

  const int depth = atoi(charDepth);
  webpage_t* page = webpage_new(url, depth, html);

  free(charDepth);

  return page;
}