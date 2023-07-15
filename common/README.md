# CS50 Lab 4
## CS50 Spring 2023

### COMMON

The common repo hosts pagedir.c, word.c, and index.c.
They host functions related to pagedirectories, indices, and normalizing words.

### Usage

The pagedir module, implemented in `pagedir.c`, exports the following functions:

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(char* pageDirectory);
webpage_t* pagedir_load(const char* pageDirectory, int docID);
```

The index module, implemented in `index.c`, exports the following functions:

```c
index_t* index_new(const int slotSize);
void index_insert(index_t* index, void* word, void* docID);
void index_save(index_t* index, FILE* fp);
void index_print(void *arg, const char *key, void *item);
void idx_counters_print(void *arg, const char *key, void *item);
index_t* index_from_file(char* filename);
void counter_delete(void *arg, const char *key, void *item);
void index_delete(index_t* index);
```

The word module, implemented in `word.c`, exports the following functions:

```c
char* normalizeWord(char* currWord);
```