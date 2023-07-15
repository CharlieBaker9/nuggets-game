# CS50 Lab 4
## CS50 Spring 2023

### CRAWLER

The crawler.c files runs a main functions which takes in arguments passed through the command line or a bash function. 
The main function checks to make sure that there exist only 3 arguments (seedURL, pageDirectory, and maxDepth)
It then calls the parseArgs function to make sure that the arguments are valid and initializes a corresponding page directory
The main function then calls crawl which crawls webpages with help from the pageScan function.
The crawl function implements the 'bag' and 'hashtable' modules and calls the function -- pagedir_save -- detailed in pagedir.h

### Usage

The crawler module, implemented in `crawler .c`, exports the following functions:

```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### Crawlertesting.sh

This is a bash script test file for the crawler.c implementation
Its outputs are formatted into a folder called data

To test, simply `make test`.

To test with valgrind, `make valgrind`.

Limitation -- you must run `make clean` and then `make` after running `make test` or `make valgrind`
running `make test` or `make valgrind` again will throw warnings as the data folder will have already been created and filled with other folders