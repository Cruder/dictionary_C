#include "metadata.h"
#include <stdlib.h>
#include <string.h>

/**
 * \fn bool createMetadata(const char *filename)
 * \param filename String corresponding to the name of the file to create
 *
 * \brief Function for creating a default metadata file
 * \return Boolean of success or not
 */
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

/**
 * \fn FILE* openDictionaryFile(const char *filename, const char *rights)
 * \param filename String corresponding to the name of the file to open
 * \param rights String with open mode of the file
 *
 * \brief Function for opening a metadata file
 * \return FILE* pointer to the file, NULL if failure
 */
FILE* OpenMetadataFile(const char *filename, const char *rights) {
  char *filename_ext = malloc(strlen(filename) + 32);
  sprintf(filename_ext, "resources/dictionaries/.%s.mda", filename);
  FILE *file = fopen(filename_ext, rights);
  free(filename_ext);
  filename_ext = NULL;
  return file;
}
