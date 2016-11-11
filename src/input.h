#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>
#include <stdio.h>

bool getInt(int *number);
bool getDouble(double *number);
bool getChar(char *letter);
bool getString(size_t size, char *str);

bool getCharRange(char *letter, char min, char max);
bool getIntRange(int *number, int min, int max);

bool isCharRange(char letter, char min, char max);
bool isIntRange(int number, int min, int max);

#endif /* end of include guard: __INPUT_H__ */
