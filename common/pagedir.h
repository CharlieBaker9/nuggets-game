/*
 * pagedir.h - header file for 'pagedir.c'
 *
 * 'pagedir.c' is a re-usable module which handles the pagesaver element of the crawler lab
 * it writes pages to the pageDirectory, and marks them as a Crawler-produced pageDirectory
 * 
 * Charlie Baker, Apr 2023
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include "../libcs50/webpage.h"

/**************** pagedir_init ****************/
/* We initialize a page directory.
 *
 * We construct the pathname for the .crawler file in the directory
 * We open the file for writing; on error, return false.
 * And we close the file and return true.
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* This allows us to save pages inside of the page directory
 *
 * We construct the pathname for the page file in pageDirectory and open that file for writing
 * We then print the URL, Depth, and contents of the file
 * After we close the file
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/**************** pagedir_validate ****************/
/* This allows us to validate that page directories are valid, crawler directories
 *
 * We construct the pathname for .crawler file in the page directory
 * We then check if we can open this file
 * If not we return false, otherwise close the file and return true
 */
bool pagedir_validate(char* pageDirectory);

/**************** pagedir_load ****************/
/* This allows us to load pages from page directory and return then
 *
 * We return null if a file doesn't exist within the pageDirectory under the given docID
 * If it does exist we fetch the url, depth, and html
 * We then create a new webpage and return it
 */
webpage_t* pagedir_load(const char* pageDirectory, int docID);

#endif // __PAGEDIR_H