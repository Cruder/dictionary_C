#ifndef __DICTIONARY_H__
#define  __DICTIONARY_H__

#ifdef __WIN32__
  #define clear() system("cls")
#else
  #define clear() system("clear")
#endif

#include "input.h"
#include "metadata.h"
#include "gestmemory.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

typedef struct {
    Metadata *metadata;
    FILE *file;
    char *filename;
} Dictionary;

Dictionary *emptyDictionary();
bool createDictionary(const char *filename);
FILE* openDictionaryFile(const char *filename, const char *rights);
void freeDictionary(Dictionary *dico);
Dictionary* selectDictionary(const char *filename);
bool checkDictionaryPath();
char **listDictionaries(char *dirname, size_t *count);
ssize_t countDictionaries(char *dirname);
void displayDictionaries(char **dictionaries, size_t count);
long positionForWord(Dictionary* file, char *word);
int addWordFile(FILE *file, char *word, const long position);

#endif //__DICTIONARY_H__
