#ifndef __GESTORTH_H__
#define  __GESTORTH_H__

#include "dictionary.h"
#include "linked_words.h"
#include <ctype.h>

void main3Menu(void);
void menu3(Dictionary *dico);
void menu3OpenDictionary(void);

void searchMissingWords(Dictionary *dico, const char *filename, int code);
void listMissingWords(Dictionary *dico, const char *filename);
void suggestSimilarWords(Dictionary *dico, const char *filename);
void autoCorrectFile(Dictionary *dico, const char *filename);
void autoCorrectFileWrite(Dictionary *dico, char *str, FILE *out);

#endif //__GESTORTH_H__
