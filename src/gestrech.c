#include "gestrech.h"
<<<<<<< c47e201e18a5ab1d1fa72a1ebaf626bdf811d06b
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

/**
* \fn int levenshtein(char *str1, char *str2)
* \brief Calculate the distance between the two given strings
* \param str1 Char *
* \param str2 Char *
* \return Integer the distance between the two given strings
*/
int levenshtein(char *str1, char *str2) {
    if (strcmp(str1, str2) == 0) {
        return 0;
    }

    if(strlen(str2) > strlen(str1)) {
        swapChar(&str1, &str2);
    }

    size_t size1 = strlen(str1);
    size_t size2 = strlen(str2);

    int *val = malloc(sizeof(int) * size2 + 1);
    for (size_t i = 0; i <= size2; i++) {
        val[i] = i;
    }

    for (size_t i = 0; i < size1; i++) {
        int last_cost = i + 1;
        for (size_t j = 0; j < size2; j++) {
            int sub_cost = (str1[i] == str2[j]) ? 0 : 1;
            int cost = min(min(last_cost + 1, val[j + 1] + 1), val[j] + sub_cost);
            val[j] = last_cost;
            last_cost = cost;
        }
        val[size2] = last_cost;
    }
    int distance = val[size2];
    free(val);
    return distance;
}
