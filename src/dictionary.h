#ifndef __DICTIONARY_H__
#define  __DICTIONARY_H__

#ifdef __WIN32__
  #define clear() system("cls")
#else
  #define clear() system("clear")
#endif

#include "input.h"
#include "metadata.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct {
  Metadata *metadata;
  FILE *file;
  char *filename;
} Dictionary;

Dictionary *emptyDictionary();
bool createDictionary(const char *filename);
FILE* openDictionaryFile(const char *filename, const char *rights);
void freeDictionary(Dictionary *dico);
Dictionary* selectDictionary();

#endif //__DICTIONARY_H__
