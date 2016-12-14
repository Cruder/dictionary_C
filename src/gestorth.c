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
                listMissingWords(dico, "yolo.txt");
                break;
            case '0':
                continu = false;
                break;
        }
    } while(continu);
}

/**
 * \param dictionary The dictionary who contains words
 * \param filename  The name of the file who contain the text
 *
 * \brief List all not existing words
 */
void listMissingWords(Dictionary *dictionary, const char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "The file you want to access don't exist");
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
        if(wordlen > 0 && wordPresent(dictionary, str) == false) {
            if (missing == false) {
                printf("These words are missing :\n");
                missing = true;
            }
            printf("\t%zu > %s\n", line, str);
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
