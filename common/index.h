/*
 * index.h - header file for 'index.c'
 *
 * 'index.c' is a re-usable module creates a hashtable of hashtables
 *        The key for the first hashtable is a word and the item is another hashtable
 *        The key for the second hashtable is a docID and the item is the # of ocurrences
 *        We employ index_new(), index_save(), and index_delete() in index.c
 *        
 * 
 * Charlie Baker, Apr 2023
 */

#ifndef __INDEX_H
#define __INDEX_H

/**************** global types ****************/
typedef struct index index_t;  // opaque to users of the module

/**************** functions ****************/

/**************** bag_new ****************/
/* Create a new (empty) index.
 *
 * We return:
 *   pointer to a new index, or NULL if error.
 * We guarantee:
 *   The index is initialized empty.
 * Caller is responsible for:
 *   later calling index_delete.
 */
index_t* index_new(const int slotSize);

/**************** index_insert ****************/
/* Add new item to the index.
 *
 * Caller provides:
 *   a valid index pointer, a valid word pointer, and a valid docID pointer.
 * We guarantee:
 *   that NULL indexes, word pointers, and docIDs are ignored.
 *   an occurrence is added to the index.
 * Caller is responsible for:
 *   not free-ing the item as long as it remains in the index.
 */
void index_insert(index_t* index, void* word, void* docID);

/**************** index_save ****************/
/* Save index to a file in a specific format
 *
 * Uses helper function index_print 
 */
void index_save(index_t* index, FILE* fp);

/**************** index_print ****************/
/* Prints the index to the given file in a specific format
 *
 * Called by index_save and uses helper function idx_counters_print 
 */
void index_print(void *arg, const char *key, void *item);

/**************** idx_counters_print ****************/
/* Prints the docID and then the count
 *
 * Called by index_print and calls fprintf() with the filename, docID, and count
 */
void idx_counters_print(void *arg, const char *key, void *item);

/**************** index_from_file ****************/
/* Creates a new index from a file and returns it
 *
 * Takes a filename as input and attempts to open it to read from
 * Parses through file and slowly adds words and corresponding counters to the index
 * Returns the index once complete.
 */
index_t* index_from_file(char* filename);

/**************** counter_delete ****************/
/* Deletes the given counter
 *
 * Calls counters delete on the given counter
 */
void counter_delete(void *arg, const char *key, void *item);

/**************** index_find ****************/
/* Find an element of the index given a key.
 *
 * Caller provides:
 *   a valid index pointer and a char* key.
 * We guarantee:
 *   we ignore NULL index.
 * Notes:
 *   we call hashtable_find on the index->ht using the key
 */
void* index_find(index_t* index, char* key);

/**************** index_delete ****************/
/* Delete the whole index.
 *
 * Caller provides:
 *   a valid index pointer.
 * We guarantee:
 *   we ignore NULL index.
 * Notes:
 *   the order in which items are deleted is undefined.
 */
void index_delete(index_t* index);

#endif // __INDEX_H