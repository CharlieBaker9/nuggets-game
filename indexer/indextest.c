/*
 * indextest.c - a C program which tests the index module 
 *      sees if it outputs the exact same file that it is given
 * 
 * Charlie Baker, Apr 2023
 */

#include <stdio.h>
#include "../common/index.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

int 
main(const int argc, char* argv[]) 
{
  if (argc != 3){
    fprintf(stderr, "invalid number of arguments -- must have two arguments (oldIndexFilename newIndexFilename)\n");
    return 1;
  }

  index_t* index = index_from_file(argv[1]);
  
  FILE* fp = fopen(argv[2], "w");
  if (fp == NULL){
    fprintf(stderr, "newIndexFilename cannot be written to\n");
    return 1;
  }

  index_save(index, fp);
  index_delete(index);
  fclose(fp);
  
  return 0;
}