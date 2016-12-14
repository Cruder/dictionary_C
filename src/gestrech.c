#include "gestrech.h"
#include <AccelLib/terminal.h>
#include <stdbool.h>
#include "menu.h"
#include "utils.h"

/**
 * \brief Function for guide user into the main menu
 */
void main2Menu(void) {
    const ColorOut title = txtColor("Dictionaries management", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor("Welcome to Dictionary Manager !", COLOR_YELLOW, COLOR_BLACK);
    MenuEntry entries[] = {{'1', "Open an existing dictionary"}, {'0', "Quit"}};
    bool continu = true;
    do {
        switch (menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                menu2OpenDictionary();
                break;
            case '0':
                color_printf(COLOR_BLUE, COLOR_BLACK, "Good bye!\n");
                continu = false;
                break;
        }
    } while(continu);
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
    const ColorOut title = txtColor("Dictionary", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor(dico->filename, COLOR_BLACK, COLOR_LIGHT_GRAY);
    MenuEntry entries[] = {{'1', "Change the threshold"},
                           {'2', "Search a similar word"},
                           {'0', "Quit dictionary"}};
    bool continu = true;
    do {
        switch(menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                menuChangeThreshold(dico->metadata, dico->filename);
                break;
            case '2':
                menuSearchSimilarWord(dico);
                break;
            case '0':
                color_printf(COLOR_YELLOW, COLOR_BLACK, "Closing dictionary ... ");
                freeDictionary(dico);
                color_printf(COLOR_GREEN, COLOR_BLACK, "Done\n");
                continu = false;
                break;
        }
    } while(continu);
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
