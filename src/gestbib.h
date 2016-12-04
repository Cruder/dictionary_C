#ifndef __GESTBIB_H__
#define  __GESTBIB_H__

#include "dictionary.h"
#include <ctype.h>

void printMainMenu(void);
void printMenu(void);
void mainMenu(void);
void menuCreateDictionary(void);
void menuOpenDictionary(void);

void menu(Dictionary *dico);
char *menuSelectDictionary(void);
void menuAddDictionaryWord(Dictionary *dico);

void menuCreateDictionaryFromFile(void);
char **readTxtFile(const char *filename, int *count);
int dictionaryFromFile(const char *filename, const char *dico);
int dictionaryFromFileEx(Dictionary *dic, char **words, int count, int status);
int countFileWord(const char *filename);
char **strSortedMakeUniq(char **strings, int *size);

#endif //__GESTBIB_H__
