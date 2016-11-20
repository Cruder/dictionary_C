#include "metadata.h"
#include <stdlib.h>
#include <string.h>

Metadata *emptyMetadata() {
  Metadata *m = malloc(sizeof(Metadata));
  m->file = NULL;
  return m;
}

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
 * \fn FILE* OpenMetadataFile(const char *filename, const char *rights)
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


Metadata *loadMetadata(const char *filename) {
  Metadata *m = emptyMetadata();
  m->file = OpenMetadataFile(filename, "r");
  fscanf(m->file, "# dictionary\n");
  fscanf(m->file, "# length: %zu\n", &m->length);
  for(size_t i = 0; i < 26; ++i) {
    char empty;
    fscanf(m->file, "# %c_start: %d\n", &empty, &m->letters[i]);
  }
  fclose(m->file);
  m->file = NULL;
  return m;
}

void freeMetadata(Metadata *m) {
  if(m->file) {
    fclose(m->file);
    m->file = NULL;
  }
  free(m);
  m = NULL;
}

void displayMetadata(const Metadata *m) {
  printf("length: %zu\n", m->length);
  for (int i = 0; i < 26; i++) {
    printf("%c_start: %d\n", 'a' + i, m->letters[i]);
  }
  printf("\n");
}
