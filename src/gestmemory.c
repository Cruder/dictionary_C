#include "gestmemory.h"
#include <stdio.h>

char **mallocBiChar(size_t x, size_t y) {
  char **value = (char **)malloc(sizeof(char *) * x);
  for(size_t i = 0; i < x; ++i) {
    value[i] = (char *)malloc(sizeof(char) * y);
  }
  return value;
}

void freeBiChar(char **value, size_t x) {
  for(size_t i = 0; i < x; ++i) {
    free(value[i]);
    value[i] = NULL;
  }
  free(value);
  value = NULL;
}
