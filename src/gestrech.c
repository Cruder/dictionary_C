#include "gestrech.h"
#include <AccelLib/terminal.h>

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
void menu2(Dictionary *dico) {
    int choice;
    do {
        printf("\n\n--- Dictionary %s ---\n\n"
               "\t1. Change threshold\n"
               "\t2. Search a similar word\n"
               "\t0. Return to Dictionaries management\n\n", dico->filename);
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 2));
        switch (choice) {
            case 1:
                menuChangeThreshold(dico->metadata, dico->filename);
                break;
            case 2:
                menuSearchSimilarWord(dico);
                break;
            case 0:
                freeDictionary(dico);
                clear_terminal();
                break;
        }
    } while(choice != 0);
}

/**
 * \brief Menu for search similar words in dictionary
 * \param dico : Dictionary for search
 *
 */
void menuSearchSimilarWord(Dictionary *dico) {
    char *word = malloc(sizeof(char) * 255);
    do {
        printf("Enter a word: ");
    } while (!getString(255, word));
    if(strlen(chomp(word)) > 0) {
        LinkedWords *first_linked_word;
        first_linked_word = getLinkedWordThresold(dico,
                                                  dico->metadata->threshold,
                                                  word);
        if (first_linked_word != NULL) {
            printf("Similar words:\n");
            displayLinkedWord(first_linked_word);
            freeLinkedWords(first_linked_word);
        } else {
            printf("An error occured when reading the dictionary %s.\n",
                    dico->filename);
        }
    }
    free(word);
}

/**
 * \fn int levenshtein(char *str1, char *str2)
 * \brief Calculate the distance between the two given strings
 * \param str1 Char * string to compare
 * \param str2 Char * string model must be in lowercase
 * \return Integer the distance between the two given strings
 */
int levenshtein(char *str1, char *str2) {
    toLowerCase(str1);
    if (strcasecmp(str1, str2) == 0) {
        return 0;
    }
    if (strlen(str2) > strlen(str1)) {
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
            int cost = minInt(last_cost + 1, val[j + 1] + 1);
            cost = minInt(cost, val[j] + sub_cost);
            val[j] = last_cost;
            last_cost = cost;
        }
        val[size2] = last_cost;
    }
    int distance = val[size2];
    free(val);
    return distance;
}

/**
 * \param metadata Metadata to change
 * \param filename The name of the metadata file
 */
void menuChangeThreshold(Metadata *metadata, const char *filename) {
    int value;
    printf("Set a positive number (>= 0)\n");
    do {
        do {
            printf("Your value: ");
        } while(!getInt(&value));
    } while(value < 0);

    metadata->threshold = (size_t)value;
    setMetadata(metadata, filename);
}
