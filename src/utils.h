#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *toLowerCase(char *str);
char **strSortedMakeUniq(char **strings, int *size);
void swapChar(char **a, char **b);
void quickSort(char **array, int start, int end);
int minInt(int a, int b);
char *chump(char *str);

#endif /* end of include guard:  */
