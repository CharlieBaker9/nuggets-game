# DESIGN of querier

## Input

The querier takes in inputs from the command line in the format

```bash
$ ./querier pageDirectory indexFilename
```

- `pageDirectory` is the pathname of a page directory produced by crawler (has a .crawler file)
- `indexFilename`  is the pathname of a file written by indexer

It then takes in words ("queries") in a specific format to see if they appear in the files in the pagedirectory. This will hinge off of the use of the index.

Querier outputs either a list of scores and corresponding documents in a specific format, no documents if there are no matches, or an error if the input query is invalid

## Pseudocode

1. Querier will start by running from the command line
2.  It will accept the pageDirectory and IndexFileName and check if they are valid
3. It will then load in the index
4. It will then begins to prompt the user for a query
5. It will then take in the input and go through certain checks
6. It will check if the input is all spaces and if there is a character that is not a letter or a space
7. It will then tokenize the words into an array and clean them by removing excess space and normalizing them
8. It then will print the cleaned query
9. It will check to make sure that the literals are not adjacent or at the beginning or end of the sequence
10. It will then iterater through printing out the scores of each of the doc's and their url in descending order
11. It will continue to prompt for input unless EOF is reached
12. To close it will delete the index and return


## Data structures

Two data structures we will rely on heavily:

 1. ***Index*** where the words will be keys to their values which will be counters
 2. ***counters*** the counters will have docID as their keys and their corresponding counts as their values
