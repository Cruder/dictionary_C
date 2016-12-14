#include "gestorth.h"

/**
 * \param dictionary The dictionary who contains words
 * \param filename  The name of the file who contain the text
 * \param code  A code to switch between features
 * \brief List all not existing words and may suggest a correction if code is equal to 1
 */
void searchMissingWords(Dictionary *dico, const char *filename, int code) {
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
 * \param dictionary The dictionary who contains words
 * \param filename  The name of the file who contain the text
 *
 * \brief List all not existing words and suggest a correction
 */
void suggestSimilarWords(Dictionary *dico, const char *filename) {
    searchMissingWords(dico, filename, 1);
}

/**
* \param dictionary The dictionary who contains words
* \param filename  The name of the file who contain the text
*
* \brief List all not existing words
*/
void listMissingWords(Dictionary *dico, const char *filename) {
    searchMissingWords(dico, filename, 0);
}
