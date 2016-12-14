#include "gestbib.h"
#include <ctype.h>
#include <AccelLib/terminal.h>
#include "input.h"

/**
 * \fn void mainMenu()
 * \brief Function for guide user into the main menu
 *
 */
void mainMenu(void) {
    const ColorOut title = txtColor("Dictionaries management", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor("Welcome to Dictionary Manager !", COLOR_YELLOW, COLOR_BLACK);
    MenuEntry entries[] = {{'1', "Open an existing dictionary"},
                           {'2', "Create an empty dictionary"},
                           {'3', "Create a dictionary with a text file"},
                           {'4', "Remove a dictionary"},
                           {'0', "Quit"}};
    bool continu = true;
    do {
        switch (menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                menuOpenDictionary();
                break;
            case '2':
                menuCreateDictionary();
                break;
            case '3':
                menuCreateDictionaryFromFile();
                break;
            case '4':
                menuRemoveDictionary();
                break;
            case '0':
                color_printf(COLOR_BLUE, COLOR_BLACK, "Good bye!\n");
                continu = false;
                break;
        }
    } while(continu);
}

/**
 * \fn void menuOpenDictionary(void)
 * \brief Help the user to open a Dictionary
 */
void menuOpenDictionary(void) {
    char *dico = menuSelectDictionary();
    if(dico != NULL) {
        color_puts(COLOR_YELLOW, COLOR_BLACK, "Opening dictionary ... ");
        Dictionary *dic = selectDictionary(dico);
        if(dic != NULL) {
            menu(dic);
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
 * \fn void mainMenu()
 * \brief Function for guide user into the second menu
 *
 */
void menu(Dictionary *dico) {
    const ColorOut title = txtColor("Dictionary", COLOR_WHITE, COLOR_BLACK);
    const ColorOut msg = txtColor(dico->filename, COLOR_MAGENTA, COLOR_BLACK);
    MenuEntry entries[] = {{'1', "Add a word"},
                           {'2', "Search a word"},
                           {'0', "Return to Dictionaries management"}};
    bool continu = true;
    do {
        switch (menuChoice(title, msg, entries, COUNTOF(entries))) {
            case '1':
                menuAddDictionaryWord(dico);
                break;
            case '2':
                freeDictionary(dico);
                break;
            case '0':
                continu = false;
                break;
        }
    } while(continu);
}

/**
 * \fn void menuCreateDictionary()
 * \brief Function to help the user creating a dictionary
 *
 */
void menuCreateDictionary(void) {
    char *filename = getStringColor();
    printf("Dictionary filename: ");
    filename = malloc(sizeof(char) * 255);
    getString(255, filename);
    if(createDictionary(filename)) {
        printf("Dictionary %s has been created.\n", filename);
    } else {
        printf("An error as occured when creating dictionary %s.\n", filename);
    }
    free(filename);
}

/**
 * \fn void menuAddDictionaryWord(Dictionary *dico)
 * \param dico The dictionary where to put the new word
 *
 * \brief Function to display the menu `add a word`
 *
 */
void menuAddDictionaryWord(Dictionary *dico) {
    dico->file = openDictionaryFile(dico->filename, "r+");

    char *word = (char *) malloc(sizeof(char) * 255);
    do {
        printf("Enter a word: ");
    } while (!getString(255, word));

    long pos = positionForWord(dico, word);
    if (pos == -1) {
        return;
    }
    addWordFile(dico->file, word, pos);
    metadataWordAdded(dico->metadata, word);
    setMetadata(dico->metadata, dico->filename);

    free(word);
    fclose(dico->file);
    dico->file = NULL;
}

/**
 * \fn int countFileWord(const char *filename)
 * \param filename The path of the file on which to count words
 *
 * \brief Count the number of words into a given file
 * \return The number of words into the given file in Integer
 */
int countFileWord(const char *filename) {
    char c;
    int count = 0;
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        return -1;
    }
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(file);
    return count;
}

/**
 * \fn int dictionaryFromFile(const char *filename, const char *dico_name)
 * \param filename The path of the file to parse into a dictionary
 * \param dico_name Name of the dico to create
 *
 * \brief Create a new dictionary from a file conaining words separated by carriage return
 * \return Integer of the code error
 */
int dictionaryFromFile(const char *filename, const char *dico_name) {
    int count;
    char **words = readTxtFile(filename, &count);
    if (words == NULL) {
        return 1;
    }
    quickSort(words, 0, count - 1);
    words = strSortedMakeUniq(words, &count);
    if (createDictionary(dico_name) == false) {
        return dictionaryFromFileEx(NULL, words, count, 2);
    }
    Dictionary *dico = selectDictionary(dico_name);
    if (dico == NULL) {
        return dictionaryFromFileEx(NULL, words, count, 3);
    }
    dico->file = openDictionaryFile(dico->filename, "r+");
    if (dico->file == NULL) {
        return dictionaryFromFileEx(dico, words, count, 4);
    }
    fseek(dico->file, 0, SEEK_END);
    for (size_t i = 0; i < count; i++) {
        fputs(words[i], dico->file);
    }
    if(synchronizeMetadata(dico) == false) {
        return dictionaryFromFileEx(dico, words, count, 5);
    }
    return dictionaryFromFileEx(dico, words, count, 0);
}

/**
 * \fn int dictionaryFromFileEx(Dictionary *dic, char **words, int count, int status)
 * \param dic Dictionary to free
 * \param words Array is string to free
 * \param count Number of strings into the given array
 * \param status Code error to raise
 *
 * \brief Manage Exception for the function int dictionaryFromFile(const char *filename, const char *dico_name)
 * \return Status of the Excpetion
 */
int dictionaryFromFileEx(Dictionary *dic, char **words, int count, int status) {
    freeDictionary(dic);
    freeBiChar(words, count);
    return status;
}

/**
 * \fn char **readTxtFile(const char *filename, int* count)
 * \param filename The path of the file on which to collect the words
 * \param count A pointer of Integer on which the words wil be count
 *
 * \brief Read a txt file and collect words
 * \return Array with the strings from the given file
 */
char **readTxtFile(const char *filename, int* count) {
    *count = countFileWord(filename);
    FILE *file = fopen(filename, "r");
    if (*count == -1 || file == NULL) {
        return NULL;
    }
    char **words = mallocBiChar(*count, 255);
    if (words == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < *count; i++) {
        fgets(words[i], 255, file);
    }
    fclose(file);
    return words;
}



/**
 * \fn void menuCreateDictionaryFromFile(void)
 *
 * \brief Help the user to create a dictionary from a text file
 */
void menuCreateDictionaryFromFile(void) {
    char *filename = malloc(sizeof(char) * 255);
    char *diconame = malloc(sizeof(char) * 255);
    printf("Please tape the path to your txt file: ");
    getString(255, filename);
    printf("Now give a name to the new dictionary: ");
    getString(255, diconame);
    switch (dictionaryFromFile(filename, diconame)) {
        case 1:
            printf("An error occured when reading the file.\n");
            break;
        case 2:
            printf("An error occured when creating the dictionary.\n");
            break;
        case 3:
        case 4:
            printf("An error occured when opening the dictionary.\n");
            break;
        case 5:
            printf("An error occured when setting the metadata.\n");
            break;
        default:
            printf("Dictionary %s has been created\n", diconame);
    }
    free(filename);
    free(diconame);
}

/**
 * \fn void menuSearchWord(Dictionary *dico)
 * \param dico Dictionary on which to search a word
 *
 * \brief Help the user to search a word into a given dictionary
 */
void menuSearchWord(Dictionary *dico) {
    char *word = malloc(sizeof(char) * 255);
    printf("Enter a word: ");
    getString(255, word);
    if (wordPresent(dico, word) == true) {
        printf("The word %s exists in the dictionary %s.\n", word, dico->filename);
    } else {
        printf("The word %s does not exist in the dictionary %s.\n", word, dico->filename);
        printf("Do you want to add it ? [y/N]: ");
        char c;
        getChar(&c);
        if (c == 'y') {
            printf("ADD WORD\n");
        }
    }
    free(word);
}

/**
 * \fn void menuRemoveDictionary()
 * \brief Function to help the user removing a dictionary
 *
 */
void menuRemoveDictionary(void) {
    size_t count;
    int choice;
    char **dictionaries = listDictionaries("resources/dictionaries", &count);
    displayDictionaries(dictionaries, count);
    printf("\t0. CANCEL - Back to menu\n");
    do {
        printf("Dictionary number to remove: ");
    } while(!getIntRange(&choice, 0, count));
    if(choice != 0) {
        printf("Remove dictionary %s? [y/N] : ", dictionaries[choice - 1]);
        char c;
        if(getChar(&c) && (c == 'y' || c == 'Y')) {
            if(removeDictionary(dictionaries[choice - 1]) == 0) {
                printf("Dictionary %s has been removed.\n", dictionaries[choice - 1]);
            } else {
                printf("An error has occured when removing the dictionary %s\n",
                       dictionaries[choice - 1]);
            }
        }
    }
    freeBiChar(dictionaries, count);
}
