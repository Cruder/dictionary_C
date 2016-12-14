#include "gestorth.h"

/**
 * \param dictionary The dictionary who contains words
 * \param filename  The name of the file who contain the text
 *
 * \brief List all not existing words
 */
void listUnexistsWords(Dictionary *dictionary, const char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "The file you want to access don't exist");
        return;
    }

    char *str = malloc(sizeof(char) * 255);

    size_t counter = 0;
    size_t line = 1;
    while(!feof(file)) {
        fscanf(file, "%s", str);
        cleanWord(str);
        // strlen(str) > 0 because of punctuation removal
        size_t wordlen = strlen(str);
        if(wordlen > 0 && wordPresent(dictionary, str) == false) {
            printf("\t%zu > %s\n", line, str);
            ++counter;
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

    printf("Line %zu\n", line);

    free(str);
    fclose(file);
}
