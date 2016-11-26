#include "gestmemory.h"
#include <stdio.h>

/**
 * \fn char **mallocBiChar(size_t x, size_t y)
 * \param x The 1st dimentional size
 * \param y The 2nd dimentional size
 *
 * \brief Allocate a new bi-dimentional array
 * \return NULL if error or a bi-dimentional array
 */
char **mallocBiChar(size_t x, size_t y) {
  char **value = (char **)malloc(sizeof(char *) * x);
  if(value == NULL) {
    return NULL;
  }
  for(size_t i = 0; i < x; ++i) {
    value[i] = (char *)malloc(sizeof(char) * y);
    if(value[i] == NULL) {
      freeBiChar(value, i - 1);
      return NULL;
    }
  }
  return value;
}

/**
 * \fn void freeBiChar(char **value, size_t x)
 * \param value The bi-dimentional array
 * \param x The size of the bi-dimentional array
 *
 * \brief Free a bi-dimentional char
 */
void freeBiChar(char **value, size_t x) {
  for(size_t i = 0; i < x; ++i) {
    free(value[i]);
    value[i] = NULL;
  }
  free(value);
  value = NULL;
}
