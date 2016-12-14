#include "gestorth.h"
#include "linked_words.h"

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

    bool is_first_word = false;
    LinkedWords *first_linked_word = NULL;
    LinkedWords *next_linked_word = NULL;
    size_t counter = 0;
    size_t line = 0;
    while(!feof(file)) {
        fscanf(file, "%s", str);
        int newline = fgetc(file);
        if(newline == '\n') {
            ++line;
        }
        if(!feof(file)) {
            fseek(file, -1, SEEK_CUR);
        }
        cleanWord(str);
        // strlen(str) > 0 because of punctuation removal
        size_t wordlen = strlen(str);
        if(wordlen > 0 && wordPresent(dictionary, str) == false) {
            printf("\t%zu > %s\n", line, str);
            if(is_first_word == false) {
                is_first_word = true;
                first_linked_word = newWord(str);
                next_linked_word = first_linked_word;
            } else {
                next_linked_word->next = newWord(str);
                next_linked_word = next_linked_word->next;
            }
            ++counter;
            for(size_t i = 0; i < wordlen; ++i) {
                str[i] = '\0';
            }
        }
    }

    printf("Line %zu\n", line);
    // displayLinkedWord(first_linked_word);

    free(str);
    fclose(file);
}
