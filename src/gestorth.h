#ifndef __GESTORTH_H__
#define  __GESTORTH_H__

#include "dictionary.h"
#include "linked_words.h"

void searchMissingWords(Dictionary *dico, const char *filename, int code);
void listMissingWords(Dictionary *dico, const char *filename);
void suggestSimilarWords(Dictionary *dico, const char *filename);
void autoCorrectFile(Dictionary *dico, const char *filename);

#endif //__GESTORTH_H__
