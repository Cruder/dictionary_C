#include "gestorth.h"

/**
 * \brief Function for guide user into the third main menu
 */
void main3Menu(void) {
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
                menu3OpenDictionary();
                break;
            case 0:
                printf("Good bye!\n");
                break;
        }
    } while(choice != 0);
}

/**
 * \brief Function for guide user into the third menu
 */
void menu3(Dictionary *dico) {
    int choice;
    do {
        printf("\n\n--- Dictionary %s ---\n\n"
               "\t1. Find unknown words\n"
               "\t2. Suggest a correction for unknown words\n"
               "\t3. Auto correct a text file\n"
               "\t0. Return to Dictionaries management\n\n", dico->filename);
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 3));
        char *filename = malloc(sizeof(char) * 255);
        printf("Please tape the path to your txt file: ");
        getString(255, filename);
        switch (choice) {
            case 1:
                listMissingWords(dico, filename);
                break;
            case 2:
                suggestSimilarWords(dico, filename);
                break;
            case 3:
                autoCorrectFile(dico, filename);
                break;
            case 0:
                freeDictionary(dico);
                clear();
                break;
        }
        free(filename);
    } while(choice != 0);
}

/**
 * \brief Help the user to open a Dictionary
 */
void menu3OpenDictionary(void) {
    char *dico = menuSelectDictionary();
    if(dico != NULL) {
        menu3(selectDictionary(dico));
        free(dico);
        dico = NULL;
    }
}

/**
 * \param dico The dictionary who contains words
 * \param filename  The name of the file who contain the text
 * \param code  A code to switch between features
 * \brief List all not existing words and may suggest a correction if code is equal to 1
 */
void searchMissingWords(Dictionary *dico, const char *filename, int code) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "The file you want to access does not exist");
        return;
    }
    char *str = malloc(sizeof(char) * 255);
    bool missing = false;
    size_t line = 1;
    while(!feof(file)) {
        fscanf(file, "%s", str);
        cleanWord(str);
        // strlen(str) > 0 because of punctuation removal
        size_t wordlen = strlen(str);
        if(wordlen > 0 && wordPresent(dico, str) == false) {
            if (missing == false) {
                printf("These words are missing :\n");
                printf("(line > word)\n");
                missing = true;
            }
            printf("  %zu > %s\n", line, str);
            if (code == 1) {
                displaySimilarWords(dico, 2, str);
            }
            for(size_t i = 0; i < wordlen; ++i) {
                str[i] = '\0';
            }
        }

        while (fgetc(file) == '\n') {
            ++line;
        }
        if(!feof(file)) {
            fseek(file, -1, SEEK_CUR);
        }
    }

    if (missing == false) {
        printf("The file is correct.\n");
    }

    free(str);
    fclose(file);
}

/**
 * \param dico The dictionary who contains words
 * \param filename  The name of the file who contain the text
 *
 * \brief List all not existing words and suggest a correction
 */
void suggestSimilarWords(Dictionary *dico, const char *filename) {
    searchMissingWords(dico, filename, 1);
}

/**
* \param dico The dictionary who contains words
* \param filename  The name of the file who contain the text
*
* \brief List all not existing words
*/
void listMissingWords(Dictionary *dico, const char *filename) {
    searchMissingWords(dico, filename, 0);
}

/**
* \param dico The dictionary who contains words
* \param filename  The name of the file who contain the text
*
* \brief Auto correct the given file with the words from the given dictionary
*/
void autoCorrectFile(Dictionary *dico, const char *filename) {
    FILE *file = fopen(filename, "r");
    char *file_out = malloc(sizeof(char) * 255);
    FILE *out = fopen(strcat(strcpy(file_out, filename), ".revised"), "w");
    if(file == NULL || out == NULL) {
        fprintf(stderr, "The file you want to access does not exist");
        free(file_out);
        fclose(file);
        fclose(out);
        return;
    }
    char *str = malloc(sizeof(char) * 255);
    int c;
    size_t index = 0;
    while (!feof(file)) {
        c = fgetc(file);
        if (isalpha(c)) {
            str[index++] = tolower(c);
            str[index] = '\0';
        } else {
            if (strlen(str) != 0) {
                autoCorrectFileWrite(dico, str, out);
            }
            index = 0;
            str[index] = '\0';

            if(!feof(file)) {
                char remain[] = { c, '\0' };
                fputs(remain, out);
            }
        }
    }
    free(str);
    fclose(file);
}

/**
* \param dico The dictionary who contains words
* \param str  The string to correct and write into the dictionary
* \param out  A pointer to the file to write
* \brief Write the correction into the given file with the words from the given dictionary
*/
void autoCorrectFileWrite(Dictionary *dico, char *str, FILE *out) {
    LinkedWords *first_word = getLinkedWordThresold(dico, 1, str);
    if (wordPresent(dico, str)) {
        fputs(str, out);
    } else if (first_word != NULL) {
        fputs(first_word->word, out);
    } else {
        fputs(str, out);
    }
    freeLinkedWords(first_word);
}
