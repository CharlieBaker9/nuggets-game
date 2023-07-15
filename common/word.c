/*
 * word.c - a C program which normalizes words -- converts to all lower case
 *
 * Charlie Baker, Apr 2023
 */



//implements normalize word -- convert to all lower case
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char*
normalizeWord(char* currWord){
  for (int i = 0; i < strlen(currWord); i++){
    currWord[i] = tolower(currWord[i]);
  }

  return currWord;
}