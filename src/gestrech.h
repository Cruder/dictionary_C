#ifndef __GESTRECH_H__
#define  __GESTRECH_H__

#include "dictionary.h"
#include "utils.h"
#include "linked_words.h"
#include <stdlib.h>

void menu2(Dictionary *dico);
void main2Menu(void);
void menu2OpenDictionary(void);

void menuChangeThreshold(Metadata *metadata, const char *filename);
void menuSearchSimilarWord(Dictionary *dico);

int levenshtein(char *str1, char *str2);

#endif //__GESTRECH_H__
