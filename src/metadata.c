#include "metadata.h"

#include <stdlib.h>
#include <string.h>

bool createMetadata(const char *filename) {
  FILE *file = OpenMetadataFile(filename, "w");
  if (!file) {
    return false;
  }
  fprintf(file, "# dictionary\n");
  fprintf(file, "# length: 0\n");
  for(char i = 0; i < 26; ++i) {
    fprintf(file, "# %c_start: -1\n", 'a' + i);
  }
  fclose(file);
  return true;
}

FILE* OpenMetadataFile(const char *filename, const char *rights) {
  char *filename_ext = malloc(strlen(filename) + 32);
  sprintf(filename_ext, "resources/dictionaries/.%s.mda", filename);
  FILE *file = fopen(filename_ext, rights);
  free(filename_ext);
  filename_ext = NULL;
  return file;
}
