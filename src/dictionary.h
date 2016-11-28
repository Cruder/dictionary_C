#ifndef __DICTIONARY_H__
#define  __DICTIONARY_H__

#ifdef __WIN32__
  #define clear() system("cls")
#else
  #define clear() system("clear")
#endif

/*!
 * \def Longueur maximum d'un mot (sans '\0')
 */
#define WORD_MAXLENGTH 450

#include <stdio.h>
#include <stdlib.h> //system()
#include <stdbool.h>
#include "metadata.h"

typedef struct Dictionary {
  Metadata *metadata;
  FILE *file;
  char *filename;
} Dictionary;

Dictionary* emptyDictionary();
bool createDictionary(const char *filename);
FILE* openDictionaryFile(const char *filename, const char *rights);
void freeDictionary(Dictionary *dico);
Dictionary* selectDictionary(const char *filename);
bool checkDictionaryPath();
char** listDictionaries(char *dirname, size_t *count);
ssize_t countDictionaries(char *dirname);
void displayDictionaries(char *dirname);
bool addWord(const Dictionary *dic, const char *word);

#endif //__DICTIONARY_H__
