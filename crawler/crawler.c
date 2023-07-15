/*
 * crawler.c - a C program which...
 * Charlie Baker, Apr 2023
 */

#include <string.h>
#include <stdbool.h>
#include "../common/pagedir.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"


static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

int 
main(const int argc, char* argv[]) 
{
  if (argc != 4){
    fprintf(stderr, "invalid number of arguments -- must have three arguments (seedURL pageDirectory maxDepth)\n");
    return 1;
  }
  int maxDepth = atoi(argv[3]);
  if (maxDepth < 0 || maxDepth > 10){
    fprintf(stderr, "max depth is not within the range [0,10]");
    return 1;
  }
  parseArgs(argc, argv, &argv[1], &argv[2], &maxDepth);
  crawl(argv[1], argv[2], maxDepth);

  return 0;
}

static void 
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){
  //seed url -- normalize URL and validate it is an internal URL
  char* normURL = normalizeURL(*seedURL); // losing memory here
  if (!isInternalURL(normURL)){
    free(normURL);
    fprintf(stderr, "The normalized URL is not an internal URL\n");
    exit(1);
  }
  free(normURL);
  
  //calling pagedir_init with pagedirectory
  bool success = pagedir_init(*pageDirectory);
  if (!success){
    exit(1);
  }

  //validating maxDepth 
  if(maxDepth == NULL || *maxDepth < 0 || *maxDepth > 10){
    fprintf(stderr, "max depth is not within the specified range [0,10]\n");
    exit(1);
  }
}

static void 
crawl(char* seedURL, char* pageDirectory, const int maxDepth){
  hashtable_t* pages_seen = hashtable_new(200);    //keeps track of the URL's that we've seen
  if (pages_seen == NULL){
   fprintf(stderr, "error creating hashtable\n");
  }

  bag_t* pages_to_crawl = bag_new();    //keeps track of pages that we need to crawl
  if (pages_to_crawl == NULL){
    fprintf(stderr, "error creating bag\n");
  }

  char* normalizedSeed = normalizeURL(seedURL);
  hashtable_insert(pages_seen, normalizedSeed, "");
  bag_insert(pages_to_crawl, webpage_new(normalizedSeed, 0, NULL));

  webpage_t* currPage;
  int docID = 1;
  while ((currPage = bag_extract(pages_to_crawl)) != NULL){
    if (webpage_fetch(currPage) == 1){
      pagedir_save(currPage, pageDirectory, docID);
      docID++;
      if (webpage_getDepth(currPage) != maxDepth){
        pageScan(currPage, pages_to_crawl, pages_seen);
      }
    }
    webpage_delete(currPage);
  }
  bag_delete(pages_to_crawl, NULL);
  hashtable_delete(pages_seen, NULL);
}

static void 
pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
  int pos = 0;
  char* currURL;
  while ((currURL = webpage_getNextURL(page, &pos)) != NULL){
    char* normalizedURL = normalizeURL(currURL);
    if (isInternalURL(normalizedURL)){
      bool success = hashtable_insert(pagesSeen, normalizedURL, "");
      if (success){
        webpage_t* currPage = webpage_new(normalizedURL, webpage_getDepth(page) + 1, NULL);
        bag_insert(pagesToCrawl, currPage);
      } else {
        free(normalizedURL);
      }
    } else {
      free(normalizedURL);
    }
    free(currURL);
  }
}