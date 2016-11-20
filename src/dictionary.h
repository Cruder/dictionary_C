#ifndef __DICTIONARY_H__
#define  __DICTIONARY_H__

#ifdef __WIN32__
  #define clear() system("cls")
#else
  #define clear() system("clear")
#endif

#include "metadata.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool createDictionary(const char *filename);
FILE* openDictionaryFile(const char *filename, const char *rights);

#endif //__DICTIONARY_H__
