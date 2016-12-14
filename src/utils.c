#include "utils.h"

/**
* \fn char **strSortedMakeUniq(char **strings, int *size)
* \param strings The array of strings to make uniq
* \param size Size of th array
*
* \brief Check for duplicate strings into a sorted array and make them uniq
* \return Array of strings without duplicate
*/
char **strSortedMakeUniq(char **strings, int *size) {
    for (size_t i = 0; i < *size - 1; ++i) {
        if(strcmp(strings[i], strings[i + 1]) == 0) {
            free(strings[i + 1]);
            for (size_t j = i + 1; j < *size - 1; ++j) {
                strings[j] = strings[j + 1];
            }
            i--;
            strings[--(*size)] = NULL;
        }
    }
    return strings;
}

/**
* \fn void swapChar(char **a, char **b)
* \param a Pointer to a string
* \param b Pointer to a string
*
* \brief Invert two strings
*/
void swapChar(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
* \fn void quickSort(char **array, int start, int end)
* \param array The array of strings to sort
* \param start Index of the array where to start the sort
* \param end Index of the array where to finish the sort
*
* \brief Sort an array of strings with quick sort algorithm
*/
void quickSort(char **array, int start, int end) {
    int left = start - 1;
    int right = end + 1;
    char *pivot = malloc(sizeof(char) * 255);
    strcpy(pivot, array[start]);

    if(start >= end) {
        return;
    }

    while(1) {
        do {
            right--;
        } while(strcmp(array[right], pivot) > 0);
        do {
            left++;
        } while(strcmp(array[left], pivot) < 0);

        if(left < right) {
            swapChar(&array[left], &array[right]);
        } else {
            break;
        }
    }

    quickSort(array, start, right);
    quickSort(array, right + 1, end);
    free(pivot);
}

/**
* \fn char *toLowerCase(char *str)
* \brief Set a string to lower case
*
* \param str String to set in lower case
* \return Char* The formated string in lower case
*/
char *toLowerCase(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

/**
* \fn int min(int a, int b)
* \brief Get the lower value between the two given Integers
* \param a Integer
* \param b Integer
* \return Integer the lower value between the two given Integers
*/
int minInt(int a, int b) {
    if(a < b) {
        return a;
    }
    return b;
}

/**
* \fn char *chomp(char *str)
* \brief Remove the '\n' last caracter before the '\0' if exists
* \param str The string to treat
* \return Char* The string without the final '\n'
*/
char *chomp(char *str) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

/**
 * \param word The word to clean
 *
 * \brief Remove punctuations ".!?,;:/_"
 */
void cleanWord(char *word) {
    char clean[] = ".!?,;:/_&\"()[]{}=+*\\#|";
    size_t wordlen = strlen(word);

    for(size_t i = 0; i < wordlen; ++i) {
        if (strchr(clean, word[i]) != NULL) {
            for(size_t j = i; j < wordlen; ++j) {
                word[j] = word[j + 1];
            }
        }
    }
}
