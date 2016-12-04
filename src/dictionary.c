#include "dictionary.h"
#include "gestmemory.h"
#include "gestorth.h"
#include "metadata.h"

#include <string.h>
#include <dirent.h>

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
  if(dico != NULL) {
    freeMetadata(dico->metadata);
    dico->metadata = NULL;
    if(dico->file) {
      fclose(dico->file);
    }
    dico->file = NULL;
    free(dico->filename);
    dico->filename = NULL;
    free(dico);
  }
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

/*
 * \fn ssize_t countDictionaries(char *dirname)
 * \param dirname String corresponding to the name of the directory
 *
 * \brief Count dictionaries on a directory
 * \return -1 if error or the count of dictionaries found
 */
ssize_t countDictionaries(char *dirname) {
  ssize_t count = 0;
  DIR *dir = opendir(dirname);
  struct dirent *ent;
  if (dir) {
    while ((ent = readdir(dir)) != NULL) {
      if(ent->d_type == DT_REG && strlen(ent->d_name) > 4) {
        char *ext = (ent->d_name + strlen(ent->d_name) - 4);
        if(strcmp(ext, ".dic") == 0) {
          ++count;
        }
      }
    }
    closedir(dir);
  } else {
    return -1;
  }
  return count;
}

/**
 * \fn char **listDictionaries(char *dirname, ssize_t *count)
 * \param dirname String corresponding to the name of the directory
 * \param count *ssize_t corresponding to pointer of dictionnaries count
 *
 * \brief List all dictionnaries on a directory
 * \return NULL if error or the count of dictionaries found
 */
char **listDictionaries(char *dirname, size_t *count) {
  ssize_t dic_count = countDictionaries(dirname);
  if(dic_count == -1) {
    return NULL;
  }
  *count = (size_t)dic_count;
  char **dictionaries = mallocBiChar(*count, 255);
  DIR *dir = opendir(dirname);
  struct dirent *ent;
  if (dir) {
    size_t cursor = 0;
    while ((ent = readdir(dir)) != NULL) {
      if(ent->d_type == DT_REG) {
        char *ext = (ent->d_name + strlen(ent->d_name) - 4);
        if(strcmp(ext, ".dic") == 0) {
          strcpy(dictionaries[cursor++], ent->d_name);
        }
      }
    }
    closedir(dir);
  } else {
    freeBiChar(dictionaries, *count);
    return NULL;
  }

  for(size_t i = 0; i < *count; ++i) {
    dictionaries[i][strlen(dictionaries[i]) - 4] = '\0';
  }
  return dictionaries;
}

/**
 * \fn void displayDictionaries(char **dictionaries, size_t count)
 * \param dictionaries The list of all dictionaries
 * \param count The count of dictionaries
 *
 * \brief List all dictionnaries on a directory
 */
void displayDictionaries(char **dictionaries, size_t count) {
    printf("Dictionaries: \n");
    for(size_t i = 0; i < count; ++i) {
        printf("\t%zu. %s\n", i + 1, dictionaries[i]);
    }
}

/**
 * \fn long positionForWord(Dictionary *dic, char *word)
 * \param dic The dictionary
 * \param word The word to place in the dictionary
 * \return The position where to put the word, -1 in case of errors
 */
long positionForWord(Dictionary *dic, char *word) {
    if(dic == NULL || dic->file == NULL) {
        fprintf(stderr, "An error has occured\n");
        return -1;
    }
    long beginfile = dic->metadata->letters[word[0] - 'a'];
    fseek(dic->file, beginfile, SEEK_SET);
    while(1) {
        char *fw = (char *)malloc(sizeof(char) * 255);
        fscanf(dic->file, "%s\n", fw);
        int compare = strcmp(word, fw);
        printf("%s < %s %d\n", word, fw, compare);

        size_t fw_len = strlen(fw);
        free(fw);
        if(compare < 0) {
            fseek(dic->file, -fw_len - 1, SEEK_CUR);
            return ftell(dic->file);
        } else if(compare == 0) {
            fprintf(stderr, "Word %s already exist", word);
            return -1;
        } else if(feof(dic->file)) {
            return ftell(dic->file);
        }
    }
}

/**
 * \fn int addWordFile(FILE *file, char *word, const long position)
 * \param file A file
 * \param word Word to add in the file
 * \param position Where put this word on the file
 * \return 0 for success
 */
int addWordFile(FILE *file, char *word, const long position) {
    size_t strlength = strlen(word);

    long endfile = 0;

    fseek(file, 0, SEEK_END);
    endfile = ftell(file);

    fwrite(word, 1, strlength, file);
    fseek(file, endfile, SEEK_SET);
    for(long i = endfile; i >= position; --i) {
        fseek(file, -1, SEEK_CUR);
        int tmp = fgetc(file);
        fseek(file, strlength, SEEK_CUR);
        fputc(tmp, file);
        fseek(file, i, SEEK_SET);
    }
    fseek(file, position, SEEK_SET);
    printf("%s => %zu", word, strlength);
    fwrite(word, 1, strlength, file);
    fputc('\n', file);

    return 0;
}

/**
 * \fn bool synchronizeMetadata(Dictionary *dico)
 * \param dico Dictionary on which synchronize the metadata
 *
 * \brief Read a dictionary file and make the metadata consequently
 * \return Boolean of success or not
 */
bool synchronizeMetadata(Dictionary *dico) {
  if (dico->file == NULL) {
    dico->file = openDictionaryFile(dico->filename, "r+");
  }
  fseek(dico->file, 24, SEEK_SET);
  char *str = malloc(sizeof(char) * 255);
  long position = ftell(dico->file);
  char c = 'a' - 1;
  dico->metadata->length = 0;
  while (fgets(str, 255, dico->file) && c < 'z') {
    char letter = tolower(str[0]);
    if ((letter >= 'a' || letter <= 'z') && letter > c) {
      c = letter;
      dico->metadata->letters[letter - 'a'] = position;
    }
    dico->metadata->length++;
    position = ftell(dico->file);
  }
  free(str);
  fclose(dico->file);
  dico->file = NULL;
  return setMetadata(dico->metadata, dico->filename);
}
