#include "gestorth.h"
#include <AccelLib/terminal.h>
#include "menu.h"

/**
 * \brief Function for guide user into the main menu
 */
void main3Menu(void) {
    const ColorOut title = txtColor("Dictionaries management", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor("Welcome to Dictionary Manager !", COLOR_YELLOW, COLOR_BLACK);
    MenuEntry entries[] = {{'1', "Open an existing dictionary"}, {'0', "Quit"}};
    bool continu = true;
    do {
        switch (menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                menu3OpenDictionary();
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
void menu3OpenDictionary(void) {
    char *dico = menuSelectDictionary();
    if(dico != NULL) {
        color_puts(COLOR_YELLOW, COLOR_BLACK, "Opening dictionary ... ");
        Dictionary *dic = selectDictionary(dico);
        if(dic != NULL) {
            menu3(dic);
            color_printf(COLOR_YELLOW, COLOR_BLACK, "Closing dictionary ... ");
            freeDictionary(dic);
            color_printf(COLOR_GREEN, COLOR_BLACK, "Done\n");
        } else {
            color_printf(COLOR_LIGHT_RED, COLOR_BLACK, "Error while opening the dictionary %s ...\n", dico);
            pause_msg();
        }
        free(dico);
        dico = NULL;
    } else {
        color_puts(COLOR_LIGHT_RED, COLOR_BLACK, "No dictionary selected ...");
        pause_msg();
    }
}

/**
 * \brief Function for guide user into the second menu
 */
void menu3(const Dictionary *dico) {
    const ColorOut title = txtColor("Dictionary", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor(dico->filename, COLOR_BLACK, COLOR_LIGHT_GRAY);
    MenuEntry entries[] = {{'1', "List missing words from text"},
                           {'0', "Quit dictionary"}};
    bool continu = true;
    do {
        switch(menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                printf("Entre the path of text file : ");
                const char *path = getStringColor(COLOR_YELLOW, COLOR_BLACK);
                listMissingWords(dico, path);
                free(path);
                break;
            case '0':
                continu = false;
                break;
        }
    } while(continu);
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
        fprintf(stderr, "The file you want to access does not exist\n");
        pause_msg();
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
