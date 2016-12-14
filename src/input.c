#include "input.h"

/**
 * \fn bool getInt(int *number)
 * \brief Function for read an int from the stdin
 *
 * \param number Integer pointer to fill with stdin
 * \return Boolean of success or not
 */
bool getInt(int *number) {
    char line[256];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%d", number)) {
            return true;
        }
    }
    return false;
}

/**
 * \fn bool getDouble(double *number)
 * \brief Function for read a double from the stdin
 *
 * \param number Double pointer to fill with stdin
 * \return Boolean of success or not
 */
bool getDouble(double *number) {
    char line[256];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%lf", number)) {
            return true;
        }
    }
    return false;
}

/**
 * \fn bool getChar(char *letter)
 * \brief Function for read a char from the stdin
 *
 * \param letter Character pointer to fill with stdin
 * \return Boolean of success or not
 */
bool getChar(char *letter) {
    char line[2];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%c", letter)) {
            return true;
        }
    }
    return false;
}

/**
 * \fn bool getString(size_t size, char *str)
 * \brief Function for read a string from the stdin
 *
 * \param size The size of the string array
 * \param str Character array to fill with stdin
 * \return Boolean of success or not
 */
bool getString(size_t size, char *str) {
    char line[size + 1];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%[^\n]s", str)) {
            return true;
        }
    }
    return false;
}

/**
 * \fn bool getCharRange(char *letter, char min, char max)
 * \brief Function for read a char from the stdin in an interval
 *
 * \param letter Character pointer to fill with stdin
 * \param min Integer, must be lower than max
 * \param max Integer, must be higher than min
 * \return Boolean of success or not
 */
bool getCharRange(char *letter, char min, char max) {
    char line[2];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%c", letter)) {
            if (*letter < min || *letter > max) {
                return false;
            }
            return true;
        }
    }
    return false;
}

/**
 * \fn getIntRange(int *number, int min, int max)
 * \brief Function for read an integer from the stdin in an interval
 *
 * \param number Integer pointer to fill with stdin
 * \param min Integer, must be lower than max
 * \param max Integer, must be higher than min
 * \return Boolean of success or not
 */
bool getIntRange(int *number, int min, int max) {
    char line[256];
    fseek(stdin, 0, SEEK_END);
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%d", number)) {
            if (*number < min || *number > max) {
                return false;
            }
            return true;
        }
    }
    return false;
}

/**
 * \fn isCharRange(char letter, char min, char max)
 * \brief Function for test if a letter is between two values
 *
 * \param letter
 * \param min Integer, must be lower than max
 * \param max Integer, must be higher than min
 * \return Boolean of success or not
 */
bool isCharRange(char letter, char min, char max) {
    if (letter < min || letter > max) {
        return false;
    }
    return true;
}

/**
 * \fn bool isIntRange(int number, int min, int max)
 * \brief Function for test if a number is between two values
 *
 * \param number
 * \param min Integer, must be lower than max
 * \param max Integer, must be higher than min
 * \return Boolean of success or not
 */
bool isIntRange(int number, int min, int max) {
    if (number < min || number > max) {
        return false;
    }
    return true;
}

/**
 * \brief Function for read a string from the stdin (colored version)
 *
 * Remember to free the string returned !
 *
 * \param fg color foreground
 * \param bg color background
 * \return string input
 */
char* getStringColor(const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    char *buffer = NULL;
    if(color_scanf(fg, bg, "%m[^\n]", &buffer) == 1) { //version 2013
        return buffer;
        //free(buffer);
    } else
        return NULL;
}

/**
 * \brief Function for read a string from the stdin (colored version)
 *
 * Remember to free the string returned !
 *
 * \param fg color foreground
 * \param bg color background
 * \return string input
 */
char* getWordColor(const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    char *buffer = NULL;
    if(color_scanf(fg, bg, "%ms", &buffer) == 1) { //version 2013
        return buffer;
        //free(buffer);
    } else
        return NULL;
}
