#ifndef __LINKED_WORDS_H__
#define __LINKED_WORDS_H__

#include "dictionary.h"
#include "gestrech.h"
#include <stdlib.h>
#include <string.h>

struct LinkedWords {
    struct LinkedWords *next;
    char *word;
};
typedef struct LinkedWords LinkedWords;


LinkedWords* newWord(char *str);
void freeLinkedWords(LinkedWords* lw);
LinkedWords *getLinkedWordFromFile(Dictionary *dico, size_t *size);
LinkedWords *getLinkedWordThresold(Dictionary *dico, int thres, char *word);
void displayLinkedWord(LinkedWords *lw);

#endif /* end of include guard: __LINKED_WORDS_H__ */
