#include "metadata.h"
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>
#ifndef PRIdS
    #if defined(_WIN32) || defined(MSVC)
        #define PRIdS "Id" //"Iu"
      #else
        #define PRIdS "zd" //"zu"
    #endif // _WIN32
#endif // PRIdS

/**
 * \fn Metadata *emptyMetadata()
 *
 * \brief Function for init a Dictionary struct
 * \return Boolean of success or not
 */
Metadata* emptyMetadata() {
  Metadata *m = calloc(1, sizeof(Metadata));
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
  FILE *file = openMetadataFile(filename, "w");
  if (!file) {
    return false;
  }
  fprintf(file, "# dictionary\n");
  fprintf(file, "# length: 0\n");
  for(char i = 0 ; i < 26 ; i++) {
    fprintf(file, "# %c_start: -1 ; 0\n", 'a' + i);
  }
  fclose(file);
  return true;
}

/**
 * \fn FILE* openMetadataFile(const char *filename, const char *rights)
 * \param filename String corresponding to the name of the file to open
 * \param rights String with open mode of the file
 *
 * \brief Function for opening a metadata file
 * \return FILE* pointer to the file, NULL if failure
 */
FILE* openMetadataFile(const char *filename, const char *mode) {
  char *filename_ext = malloc(strlen(filename) + 32);
  sprintf(filename_ext, "resources/dictionaries/.%s.mda", filename);
  FILE *file = fopen(filename_ext, mode);
  free(filename_ext);
  filename_ext = NULL;
  return file;
}

/**
 * \fn Metadata *loadMetadata(const char *filename)
 * \param filename String corresponding to the name of the file to open
 *
 * \brief Function for opening a metadata file
 * \return FILE* pointer to the file, NULL if failure
 */
Metadata *loadMetadata(const char *filename) {
  Metadata *m = emptyMetadata();
  m->file = openMetadataFile(filename, "r");
  if(m->file) {
    fscanf(m->file, "# dictionary\n");
    fscanf(m->file, "# length: %"PRIdS"\n", &m->length);
    char empty;
    for(size_t i = 0 ; i < 26 ; ++i) {
      fscanf(m->file, "# %c_start: %d ; %ld\n", &empty, &m->letters[i].ligne, &m->letters[i].bytes);
    }
    fclose(m->file);
    m->file = NULL;
  }
  return m;
}

/**
 * \fn void freeMetadata(Metadata *m)
 * \param m Metadata struct pointer
 *
 * \brief Free the m Metadata struct
 */
void freeMetadata(Metadata **m) {
  if((*m)->file) {
    fclose((*m)->file);
    (*m)->file = NULL;
  }
  free(*m);
  *m = NULL;
}

/**
 * \fn void displayMetadata(const Metadata *m)
 * \param m Metadata struct pointer
 *
 * \brief Display the length and all the start_letter
 */
void displayMetadata(const Metadata *m) {
  printf("length: %"PRIdS"\n", m->length);
  for (int i = 0; i < 26; i++) {
    printf("%c_start: %u\n", 'a' + i, m->letters[i].ligne);
  }
  printf("\n");
}
