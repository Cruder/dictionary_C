#include "dictionary.h"
#include <string.h>

/**
 * \fn bool createDictionary(const char *filename)
 * \param filename String corresponding to the name of the file to create
 *
 * \brief Function for creating an empty dictionary file
 * \return Boolean of success or not
 */
 bool createDictionary(const char *filename) {
   FILE *file = openDictionaryFile(filename, "w");
   if(!file) {
     return false;
   }
   fprintf(file, "=== DICTIONARY TYPE ===\n");
   fclose(file);
   return createMetadata(filename);
 }

Dictionary *emptyDictionary() {
  Dictionary *d = malloc(sizeof(Dictionary));
  d->metadata = NULL;
  d->file = NULL;
  d->filename = NULL;
  return d;
}

/**
 * \fn FILE* openDictionaryFile(const char *filename, const char *rights)
 * \param filename String corresponding to the name of the file to open
 * \param rights String with open mode of the file
 *
 * \brief Function for opening a dictionary file
 * \return FILE* pointer to the file, NULL if failure
 */
FILE* openDictionaryFile(const char *filename, const char *rights) {
  char *filename_ext = malloc(strlen(filename) + 32);
  sprintf(filename_ext, "resources/dictionaries/%s.dic", filename);
  FILE *file = fopen(filename_ext, rights);
  free(filename_ext);
  filename_ext = NULL;
  return file;
}

void freeDictionary(Dictionary *dico) {
  freeMetadata(dico->metadata);
  dico->metadata = NULL;
  if(dico->file) {
    fclose(dico->file);
  }
  dico->file = NULL;
  free(dico->filename);
  dico->filename = NULL;
  free(dico);
  dico = NULL;
}

Dictionary* selectDictionary(const char *filename) {
  Dictionary *dico;
  dico = emptyDictionary();
  dico->filename = malloc(sizeof(char) * (strlen(filename) + 1));
  strcpy(dico->filename, filename);
  dico->metadata = loadMetadata(filename);
  displayMetadata(dico->metadata);
  return dico;
}
