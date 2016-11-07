#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>
#include <stdio.h>

bool get_int(int *number);
bool get_double(double *number);
bool get_char(char *letter);
bool get_string(size_t size, char *str);

bool get_char_range(char *letter, char min, char max);
bool get_int_range(int *number, int min, int max);

bool is_char_range(char letter, char min, char max);
bool is_int_range(int number, int min, int max);

#endif /* end of include guard: __INPUT_H__ */
