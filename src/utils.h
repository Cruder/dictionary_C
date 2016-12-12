#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define COUNTOF(x) (sizeof(x) / sizeof((x)[0]))

char *toLowerCase(char *str);
char **strSortedMakeUniq(char **strings, int *size);
void swapChar(char **a, char **b);
void quickSort(char **array, int start, int end);
int minInt(int a, int b);
char *chomp(char *str);
void cleanWord(char *word);

#endif /* end of include guard:  */
