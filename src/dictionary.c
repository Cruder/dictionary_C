#include "dictionary.h"


#include <string.h>

bool createDictionary(const char *filename) {
  FILE *file = openDictionaryFile(filename, "w");
  if(!file) {
    return false;
  }
  fprintf(file, "=== DICTIONARY TYPE ===\n");
  fclose(file);
  return createMetadata(filename);
}

FILE* openDictionaryFile(const char *filename, const char *rights) {
  char *filename_ext = malloc(strlen(filename) + 32);
  sprintf(filename_ext, "resources/dictionaries/%s.dic", filename);
  FILE *file = fopen(filename_ext, rights);
  free(filename_ext);
  filename_ext = NULL;
  return file;
}
