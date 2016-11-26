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
   if(!checkDictionaryPath()) {
     return false;
   }
   FILE *file = openDictionaryFile(filename, "w");
   if(!file) {
     return false;
   }
   fprintf(file, "=== DICTIONARY TYPE ===\n");
   fclose(file);
   return createMetadata(filename);
 }

 /**
  * \fn Dictionary *emptyDictionary()
  *
  * \brief Init a Dictionary struct with default values
  * \return Dictionary pointer
  */
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

/**
 * \fn void freeDictionary(Dictionary *dico)
 * \param dico Dictionary pointer
 *
 * \brief Free a Dictionary struct
 */
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

/**
 * \fn Dictionary* selectDictionary(const char *filename)
 * \param filename String corresponding to the name of the file to select
 *
 * \brief Load a dictionary
 * \return Dictionary* pointer to the Dictionary
 */
Dictionary* selectDictionary(const char *filename) {
  Dictionary *dico;
  dico = emptyDictionary();
  dico->filename = malloc(sizeof(char) * (strlen(filename) + 1));
  strcpy(dico->filename, filename);
  dico->metadata = loadMetadata(filename);
  displayMetadata(dico->metadata);
  return dico;
}

/**
 * \fn bool checkDictionaryPath()
 *
 * \brief Check path 'resources/dictionaries'. Create folders if they don't exist
 * \return Boolean of success or not
 */
bool checkDictionaryPath() {
  struct stat st = {0};
  if (stat("resources", &st) == -1) {
    if(mkdir("resources", 0777) != 0) {
      return false;
    }
  }
  if (stat("resources/dictionaries", &st) == -1) {
    if(mkdir("resources/dictionaries", 0777) != 0) {
      return false;
    }
  }
  return true;
}
