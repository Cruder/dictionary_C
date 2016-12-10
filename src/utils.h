#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *toLowerCase(char *str);
char **strSortedMakeUniq(char **strings, unsigned int *size);
void swapChar(char **a, char **b);
void quickSort(char **array, const unsigned int start, const unsigned int end);

#endif /* end of include guard:  */
