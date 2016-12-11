#ifndef __GESTRECH_H__
#define  __GESTRECH_H__

#include "dictionary.h"
#include "utils.h"
#include <stdlib.h>

int levenshtein(char *str1, char *str2);

void main2Menu(void);
void menu2OpenDictionary(void);
void menu2(const Dictionary *dico);
void menuSearchSimilarWord(const Dictionary *dico);
void menuChangeThreshold(Metadata *metadata, const char *filename);

#endif //__GESTRECH_H__
