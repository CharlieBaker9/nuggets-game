# CS50 Lab 4
## CS50 Spring 2023

### INDEXER

The idnexer.c files runs a main functions which takes in arguments passed through the command line or a bash function. 
The main function checks to make sure that there exist only 2 arguments (pageDirectory indexFilename).
It then validates both the pageDirectory and the indexFilename.
The main function then calls index_build with the given page directory which constructs a new index.
After the index is created we then print it into the indexFilename with a certain format

### Usage

The indexer module, implemented in `indexer.c`, exports the following functions:

```c
int main(const int argc, char* argv[]);
static index_t* indexBuild(char** pageDirectory, const int slotSize);
static void indexPage(webpage_t* page, index_t* index, int docID, const int slotSize);
```

### indextest.c

This is a c file which tests the implementation of index.c in the common directory

It takes two arguments: oldIndexFilename newIndexFilename.
The oldIndexFilename points to the output of an old index which has been saved to that file in a specific format.
Indextest opens the file and loads it into a new index.
It then saves the new index to newIndexFilename.
This allows us to see if there are any differences between the two files (signaling that index has an incorrect implementation).

### testing.sh

This is a bash script test file for the indexer.c implementation

To test, simply `make test`.

To test with valgrind, `make valgrind`.

Limitation -- you must run `make clean` and then `make` after running `make test` or `make valgrind`
running `make test` or `make valgrind` again will throw warnings as the data folder will have already been created and filled with other folders