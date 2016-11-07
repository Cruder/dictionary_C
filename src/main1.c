#include "gestbib.h"
#include "input.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Hello Word\n");
  char *letter = (char *)malloc(sizeof(char) * 15);
  do {
    printf("Type a str: ");
  } while (!get_string(15, letter));

  printf("string is %s\n", letter);
  return 0;
}
