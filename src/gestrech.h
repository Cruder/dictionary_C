#ifndef __GESTRECH_H__
#define  __GESTRECH_H__

#include "dictionary.h"

void mainMenu(void);
void menuOpenDictionary(void);
char *menuSelectDictionary(void);
void menu(const Dictionary *dico);
void menuSearchSimilarWord(const Dictionary *dico);

#endif //__GESTRECH_H__
