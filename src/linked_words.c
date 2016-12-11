#include "linked_words.h"

/**
 * \fn LinkedWords *newWord(char *str)
 * \param str the str in char * to add in the LinkedWords
 * \brief Add a new word to the LinkedWords
 * \return LinkedWords* the new word to LinkedWords
 */
LinkedWords *newWord(char *str) {
    if(str == NULL || strlen(str) == 0) {
        return NULL;
    }
    LinkedWords* lw = malloc(sizeof(LinkedWords));
    lw->word = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(lw->word, str);
    chump(lw->word);
    lw->next = NULL;
    return lw;
}

/**
 * \fn void freeLinkedWords(LinkedWords* lw)
 * \param lw The first linked word of the LinkedWords
 * \brief Free the LinkedWords
 */
void freeLinkedWords(LinkedWords* lw) {
    if (lw == NULL) {
        return;
    }
    if(lw->next) {
        freeLinkedWords(lw->next);
    }
    free(lw->word);
    free(lw);
}

/**
 * \fn LinkedWords *getLinkedWordFromFile(Dictionary *dico, size_t *size)
 * \param dico A pointer to the dictionary to parse in LinkedWords
 * \param size A pointer to the size of the dictionary
 * \brief Create a new LinkedWords and full it with a dictionary file
 * \return LinkedWords* The first element of the LinkedWords
 */
LinkedWords *getLinkedWordFromFile(Dictionary *dico, size_t *size) {
    if (dico->file == NULL) {
        dico->file = openDictionaryFile(dico->filename, "r");
    }
    if (dico->file == NULL) {
        return NULL;
    }

    fseek(dico->file, 24, SEEK_SET);
    char *line = malloc(sizeof(char) * 255);
    LinkedWords *first_linked_word = newWord(fgets(line, 255, dico->file));
    if (first_linked_word == NULL) {
        *size = 0;
        return NULL;
    }
    LinkedWords *next_linked_word = first_linked_word;
    *size = 1;
    while (fgets(line, 255, dico->file)) {
        next_linked_word->next = newWord(line);
        next_linked_word = next_linked_word->next;
        (*size)++;
    }
    fclose(dico->file);
    dico->file = NULL;
    return first_linked_word;
}

/**
 * \fn void displayLinkedWord(LinkedWords *lw)
 * \param lw The firts element of the LinkedWords to display
 * \brief Display the words into the LinkedWords with iterativ
 */
void displayLinkedWord(LinkedWords *lw) {
    while(lw) {
        printf("\t> %s\n", lw->word);
        lw = lw->next;
    }
}

/**
 * \fn LinkedWords *getLinkedWordThresold(Dictionary *dico, int thres, char *word)
 * \param dico A pointer to the dictionary to parse into a LinkedWords
 * \param thres The Threshold to select words with the levenshtein algorithm
 * \param word The string to compare with the levenshtein algorithm
 * \brief Create a new LinkedWords selecting close words from the given word into a dictionary
 * \return LinkedWords* the firts element of the LinkedWords
 */
LinkedWords *getLinkedWordThresold(Dictionary *dico, int thres, char *word) {
    if (dico->file == NULL) {
        dico->file = openDictionaryFile(dico->filename, "r");
    }
    if (dico->file == NULL) {
        return NULL;
    }
    fseek(dico->file, 24, SEEK_SET);

    toLowerCase(word);
    char *line = malloc(sizeof(char) * 255);
    LinkedWords *first_linked_word = NULL;
    do {
        if(fgets(line, 255, dico->file) == NULL) {
            return NULL;
        }
        if (levenshtein(line, word) <= thres) {
            first_linked_word = newWord(line);
        }
    } while(first_linked_word == NULL);


    LinkedWords *next_linked_word = first_linked_word;
    while (fgets(line, 255, dico->file)) {
        if (levenshtein(line, word) <= thres) {
            next_linked_word->next = newWord(line);
            next_linked_word = next_linked_word->next;
        }
    }
    fclose(dico->file);
    dico->file = NULL;
    return first_linked_word;
}
