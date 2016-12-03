#ifndef __GESTBIB_H__
#define  __GESTBIB_H__

#include "dictionary.h"

void printMainMenu(void);
void printMenu(void);
void mainMenu(void);
void menuCreateDictionary(void);
void menuOpenDictionary(void);

void menu(Dictionary *dico);
char *menuSelectDictionary(void);
void menuAddDictionaryWord(Dictionary *dico);

#endif //__GESTBIB_H__
