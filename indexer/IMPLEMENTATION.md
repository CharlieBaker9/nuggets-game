# Implementation of Indexer

## Overview
The indexer module parses webpages and creates an index for them. The index (created in the index module) stores counters inside of a hashtable. The hashtable maps words to counters which store the docID's of the corresponding page that the word has appeared as well as the count of how many times.

## Pseudocode
### Indexer
Has a main function which takes in arguments that it feeds into indexBuild. It should pass the pageDirectory of the corresponding crawled webpages to parse as well as the size of the hashtable. IndexBuild should then build the website by iterating through the crawled files, recreating a webpage using the webpage module and then passing that into indexPage. The indexPage should go through each word in the webpage, normalize them, and then add them to the index accordingly

### Indextest
Indextest should have a main function that takes in names of an old index file as well as a new index file to be written to. Index test will allow us to check to see if our index module works correctly. IndexTest will call a function from index that loads the index file in and parses through it, creating a new index. It will then save this new index to the new file and delete the index itself. This allows us to then compare the contents of each index file to see if there are any differences.

## Datastructures
### Common
`word.c` - module for normalizing words <br>
`pagedir.c` - module to initialize, save, validate, and load page directories <br>
`index.c` - struct which points to a hashtable and has various methods to perform operations on that hashtable <br>
### Libcs50
`hashtable.c` - hashtable module from lab 3 <br>
`file.c` - module for processing files <br>
`counters.c` - module used in index.c for keeping track of docID's and word ocurrences <br>
`mem.c` - used for allocating and freeing memory <br>
`webpage.h` - used for loading and saving webpages <br>

## Testing Plan
`testing.sh` -- in testing.sh I will first test basic qualities of indexer and indextest by inputting the wrong amount of inputs and non-crawler directories. I will then test my index file by using indextest and feeding it a given index file from shared and then comparing it to the output file to see if the indices differ at all. I will then jump in and run indexer on various pagedirectories created in crawler to make sure its outputs are valid. I will test validity by comparing these output files to the given correct index files. I will then run make valgrind to check for heap allocation issues.

## Error Handling
Appropriate errors will be printed out through 'stderr'