/*
 * word.h - header file for 'word.c'
 *
 * 'word.c' is a re-usable module which handles normalization of words
 *          it takes in char* and returns the same string with all letters lowercase
 * 
 * Charlie Baker, Apr 2023
 */

#ifndef __WORD_H
#define __WORD_H

/**************** normalizeWord ****************/
/* We normalize words by iterating through each character and calling tolower()
 * returns the normalized word
 */
char* normalizeWord(char* currWord);

#endif // __WORD_H