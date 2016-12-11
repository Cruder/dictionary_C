#include "gestrech.h"
#include <string.h>

/**
 * \brief Function for guide user into the main menu
 */
void main2Menu(void) {
    int choice;
    do {
        printf("\n\n*** Dictionaries management ***\n\n"
               "\t1. Open an existing dictionary\n"
               "\t0. Quit\n\n");
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 1));
        switch (choice) {
            case 1:
                menu2OpenDictionary();
                break;
            case 0:
                printf("Good bye!\n");
                break;
        }
    } while(choice != 0);
}
/**
 * \brief Help the user to open a Dictionary
 */
void menu2OpenDictionary(void) {
    char *dico = menuSelectDictionary();
    if(dico != NULL) {
        menu2(selectDictionary(dico));
        free(dico);
        dico = NULL;
    }
}

/**
 * \brief Function for guide user into the second menu
 */
void menu2(const Dictionary *dico) {
    int choice;
    do {
        printf("\n\n--- Dictionary ---\n\n"
               "\t2. Search a similar word\n"
               "\t0. Return to Dictionaries management\n\n");
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 1));
        switch (choice) {
            case 1:
                menuSearchSimilarWord(dico);
                break;
            case 0:
                freeDictionary(dico);
                clear();
                break;
        }
    } while(choice != 0);
}

/**
 * \brief Menu for search similar words in dictionary
 * \param dico : Dictionary for search
 *
 */
void menuSearchSimilarWord(const Dictionary *dico) {
    char word[255] = {'\0'};
    printf("Enter a word : ");
    if(getString(255, word)) {
        if(strlen(word) > 0) {
            char **simWords;
            const unsigned int nb /*= searchSimilarWords(dico, word, simWords)*/;
            if(nb > 0) {
                unsigned int i;
                printf("Similar words :\n");
                for(i=0 ; i < nb ; i++)
                    printf("\t> %s\n", simWords[i]);
            } else
                printf("No similar word to %s was found ...\n");
        } else
            printf("Your word is void ...\n");
    } else
    fprintf(stderr, "Error while getting user input.\n");
}
