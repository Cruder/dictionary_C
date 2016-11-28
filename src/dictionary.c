#include "dictionary.h"
#include "gestmemory.h"

#include "input.h"
#include "gestmemory.h"
#include "buffer.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef _WIN32
    #define mkdir(path, acl) mkdir(path)
#endif // _WIN32

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
  * \fn Dictionary *empgit push --set-upstream origin new_branchtyDictionary()
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
  freeMetadata(&(dico->metadata));
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

/*
 * \fn ssize_t countDictionaries(char *dirname)
 * \params dirname String corresponding to the name of the directory
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
 * \fn char **listDictionaries(char *dirname)
 * \params dirname String corresponding to the name of the directory
 *
 * \brief List all dictionnaries on a directory
 * \return NULL if error or the count of dictionaries found
 */
char **listDictionaries(char *dirname, size_t *count) {
  *count = countDictionaries(dirname);
  if(*count == -1) {
    return NULL;
  }
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
  return dictionaries;
}

/**
 * \fn void displayDictionaries(char *dirname)
 *
 * \brief List all dictionnaries on a directory
 */
void displayDictionaries(char *dirname) {
  size_t count;
  char **dicos = listDictionaries("resources/dictionaries", &count);
  for(size_t i = 0; i < count; ++i) {
    dicos[i][strlen(dicos[i]) - 4] = '\0';
  }
  printf("Dictionaries: \n");
  for(size_t i = 0; i < count; ++i) {
    printf("\t%zu. %s\n", i, dicos[i]);
  }
  freeBiChar(dicos, count);
}

/**
 * \brief Ajoute des mots au dictionnaire
 * \var words tableau de string de mot à ajouter au dictionnaire, et trié par ordre alphabétique
 * \return false if error, true if success
 */
 /*
 int main(int argc, char const *argv[]) {
  //////////////////////////////////////////////////////////////////////////////
  // INIT
  //////////////////////////////////////////////////////////////////////////////
  FILE *file = fopen("test.txt", "r+");
  char str[] = "Ajout"; // The word
  size_t strlength = sizeof(str) + 1; // The size

  const long posword = 3; // ftell where I put the word
  long endfile = 0;

  fseek(file, 0, SEEK_END);
  endfile = ftell(file); // Where is the end of the file

  //////////////////////////////////////////////////////////////////////////////
  // Write word to add file space
  //////////////////////////////////////////////////////////////////////////////
  fwrite(str, 1, strlength, file);
  fseek(file, endfile, SEEK_SET);


  //////////////////////////////////////////////////////////////////////////////
  // Move the file content to strlength bits
  //////////////////////////////////////////////////////////////////////////////
  for(long i = endfile; i >= posword; --i) {
    fseek(file, -1, SEEK_CUR); // Get the char
    char tmp = fgetc(file);
    fseek(file, strlength, SEEK_CUR); // Go where to overwrite
    fputc(tmp, file); // overwrite
    fseek(file, i, SEEK_SET);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Write word
  //////////////////////////////////////////////////////////////////////////////
  fseek(file, posword + 1, SEEK_SET);
  fwrite(str, 1, strlength, file);

  fclose(file);
  return 0;
}
 */
bool addAllWords(const Dictionary *dic, const char *words[], const unsigned int size) {
    if((dic == NULL) || (words == NULL) || (size < 0))
        return false;
    else if(size == 0)
        return true; //rien à faire
    else {
        /*static char *tmpname = tmpnam(NULL); //nom de fichier temporaire (et unique en principe)
        clear_error();
        FILE *tmpwork = fopen(tmpname, "w");
        if(tmpwork == NULL) {
            perror("add words");
            return false;
        }
        fclose(tmpwork);
        remove(tmpname);
        */
        char *buf = malloc(size*WORD_MAXLENGTH+size); // tableau pour stocker les mots durant l'insertion
        if(buf == NULL) {
            fprintf(stderr, "add words -> malloc : error memory allocation\n");
            return false;
        } else {
            static char temp[WORD_MAXLENGTH +1] = {'\0'};
            /* on récupère la taille totale des mots à ajouter */
            unsigned int i;
            size_t len = 0;
            for(i=0 ; i < size ; i++)
                len += strlen(words[i]) + 1;
            /* puis on agrandi le fichier de cette taille */
            fseek(dic->file, 0, SEEK_END); //fin du fichier
            while(len > 0) {
                fputc('.', dic->file);
                len--;
            }
            /* puis on insère les mots en décalant les autres si nécessaire */
            rewind(dic->file);
            bool continu = true;
            int res;
            for(i=0 ; i < size ; i++) { //pour chaque mot
                /* on se place au bon endroit */
                while(continu) {
                    if(fgets(temp, sizeof(temp), dic->file) == NULL) { //vérifie si une erreur se produit
                        fprintf(stderr, "Error on get content of .dic\n");
                        return false;
                    } else {
                        res = strcasecmp(words[i], temp);
                        if(res > 0)
                            continu = false;
                        else if(res == 0) {
                            continu = false;
                            continue; /// le mot existe déjà, on passe donc au prochain (boucle for)
                        }
                    }
                }
                /* le mot est trouvé, il faut maintenant décalé  */
            }

            free(buf);
            return true;
        }
    }
}

/**
 * \brief Ajoute un mot au dictionnaire
 * \return false if error, true if success
 */
bool addWord(const Dictionary *dic, const char *word) {
    if((dic == NULL) || (word == NULL) || (strlen(word) <= 0))
        return false;
    else {
        const char *tmp[] = {word};
        bool result = addAllWords(dic, tmp, 1);
        return result;
    }
}

/**
 * \brief tri un tableau de chaine de caractère
 * note: utilise un tri à bulle
 * TODO : implémenter meilleur algo de tri
 */
void tri_strings(char *tabl[], const unsigned int size) {
    unsigned int i   = 0; // Variable de boucle
    char *tmp = NULL; // Variable de stockage temporaire
    bool en_desordre = true; // Booléen marquant l'arrêt du tri si le tableau est ordonné
    while (en_desordre) { // Boucle de répétition du tri et le test qui arrête le tri dès que le tableau est ordonné(en_desordre=FALSE)
        en_desordre = false; //Supposons le tableau ordonné
        for (i=0; i < size-1; i++) // Vérification des éléments des places j et j+1
            if(strcasecmp(tabl[i], tabl[i+1]) > 0 ) { // Si les 2 éléments sont mal triés
                /* Inversion des 2 éléments */
                tmp = tabl[i+1];
                tabl[i+1] = tabl[i];
                tabl[i] = tmp;
                en_desordre = true; // Le tableau n'est toujours pas trié
            }
    }
}

bool addTextFile(const char *nameTxt, const Dictionary *dic) {
    /// while file not fully read
    /// get fisrt block of n words
    /// trié le block -> tri_strings()
    /// ajouter les mots --> addwords()
    return false;
}
