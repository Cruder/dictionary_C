#include "gestbib.h"
#include "gestorth.h"

/**
 * \fn void printMainMenu()
 * \brief Function for display the main menu
 *
 */
void printMainMenu() {
    printf("\n\n*** Dictionaries management ***\n\n"
                   "\t1. Open an existing dictionary\n"
                   "\t2. Create an empty dictionary\n"
                   "\t3. Create a dictionary with a text file\n"
                   "\t4. Remove a dictionary\n"
                   "\t0. Quit\n\n");
}

/**
 * \fn void printMenu()
 * \brief Function for display the second menu
 *
 */
void printMenu() {
    printf("\n\n--- Dictionary ---\n\n"
                   "\t1. Add a word\n"
                   "\t2. Search a word\n"
                   "\t0. Return to Dictionaries management\n\n");
}

/**
 * \fn void mainMenu()
 * \brief Function for guide user into the main menu
 *
 */
void mainMenu(void) {
    int choice;
    do {
        printMainMenu();
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 4));
        switch (choice) {
            case 1:
                menuOpenDictionary();
                break;
            case 2:
                menuCreateDictionary();
                break;
            case 3:
                menuCreateDictionaryFromFile();
                break;
            case 4:
                printf("remove\n");
                break;
            case 0:
                printf("Good bye!\n");
                break;
        }
    } while(choice != 0);
}

void menuOpenDictionary(void) {
    char *dico = menuSelectDictionary();
    if(dico != NULL) {
        menu(selectDictionary(dico));
        free(dico);
        dico = NULL;
    }
}

char *menuSelectDictionary(void) {
    size_t count;
    char **dicos = listDictionaries("resources/dictionaries", &count);
    if(dicos == NULL) {
        printf("An error has occured.\n");
        return NULL;
    }

    printf("Select a dictionary\n");
    displayDictionaries(dicos, count);
    printf("\t0. CANCEL - Back to menu\n");
    int choice;
    do {
        printf("Your choice: ");
    } while(!getIntRange(&choice, 0, count));
    if(choice == 0) {
        freeBiChar(dicos, count);
        return NULL;
    }

    char *value = malloc(sizeof(char) * (strlen(dicos[choice - 1]) + 1));
    strcpy(value, dicos[choice - 1]);
    freeBiChar(dicos, count);
    return value;
}

/**
 * \fn void mainMenu()
 * \brief Function for guide user into the second menu
 *
 */
void menu(Dictionary *dico) {
    int choice;
    do {
        printMenu();
        do {
            printf("Your choice: ");
        } while(!getIntRange(&choice, 0, 2));

        switch (choice) {
            case 1:
                printf("Add a word to dico %s\n", dico->filename);
                menuAddDictionaryWord(dico);
                break;
            case 2:
                printf("Search a word to dico %s\n", dico->filename);
                break;
            case 0:
                freeDictionary(dico);
                clear();
                break;
        }
    } while(choice != 0);
}

/**
 * \fn void menuCreateDictionary()
 * \brief Function to help the user creating a dictionary
 *
 */
void menuCreateDictionary() {
    char *filename;
    printf("Dictionary filename: ");
    filename = malloc(sizeof(char) * 255);
    getString(255, filename);
    if(createDictionary(filename)) {
        printf("Dictionary %s has been created.\n", filename);
    } else {
        printf("An error as occured when creating dictionary %s.\n", filename);
    }
    free(filename);
}

/**
 * \fn void menuAddDictionaryWord(Dictionary *dico)
 * \param dico The dictionary where to put the new word
 *
 * \brief Function to display the menu `add a word`
 *
 */
void menuAddDictionaryWord(Dictionary *dico) {
    dico->file = openDictionaryFile(dico->filename, "r+");

    char *word = (char *) malloc(sizeof(char) * 255);
    do {
        printf("Enter a word: ");
    } while (!getString(255, word));

    long pos = positionForWord(dico, word);
    if (pos == -1) {
        return;
    }
    printf("pos -> %ld\n", pos);
    addWordFile(dico->file, word, pos);
    metadataWordAdded(dico->metadata, dico->filename, word);

    free(word);
    fclose(dico->file);
    dico->file = NULL;
}

/**
 * \fn void swapChar(char **a, char **b)
 * \param a Pointer to a string
 * \param b Pointer to a string
 *
 * \brief Invert two strings
 */
void swapChar(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * \fn void quickSort(char **array, int start, int end)
 * \param array The array of strings to sort
 * \param start Index of the array where to start the sort
 * \param end Index of the array where to finish the sort
 *
 * \brief Sort an array of strings with quick sort algorithm
 */
void quickSort(char **array, int start, int end) {
  int left = start - 1;
  int right = end + 1;
  char *pivot = malloc(sizeof(char) * 255);
  strcpy(pivot, array[start]);

  if(start >= end) {
    return;
  }

  while(1) {
    do {
      right--;
    } while(strcmp(array[right], pivot) > 0);
    do {
      left++;
    } while(strcmp(array[left], pivot) < 0);

    if(left < right) {
      swapChar(&array[left], &array[right]);
    } else {
      break;
    }
  }

  quickSort(array, start, right);
  quickSort(array, right + 1, end);
  free(pivot);
}

/**
 * \fn int countFileWord(const char *filename)
 * \param filename The path of the file on which to count words
 *
 * \brief Count the number of words into a given file
 * \return The number of words into the given file in Integer
 */
int countFileWord(const char *filename) {
  char c;
  int count = 0;
  FILE *file = fopen(filename, "r");
  if(file == NULL) {
    return -1;
  }
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      count++;
    }
  }
  fclose(file);
  return count;
}

/**
 * \fn int dictionaryFromFile(const char *filename, const char *dico_name)
 * \param filename The path of the file to parse into a dictionary
 * \param dico_name Name of the dico to create
 *
 * \brief Create a new dictionary from a file conaining words separated by carriage return
 * \return Integer of the code error
 */
int dictionaryFromFile(const char *filename, const char *dico_name) {
  int count;
  char **words = readTxtFile(filename, &count);
  if (words == NULL) {
    return 1;
  }
  quickSort(words, 0, count - 1);
  words = strSortedMakeUniq(words, &count);
  if (createDictionary(dico_name) == false) {
    return dictionaryFromFileEx(NULL, words, count, 2);
  }
  Dictionary *dico = selectDictionary(dico_name);
  if (dico == NULL) {
    return dictionaryFromFileEx(NULL, words, count, 3);
  }
  dico->file = openDictionaryFile(dico->filename, "r+");
  if (dico->file == NULL) {
    return dictionaryFromFileEx(dico, words, count, 4);
  }
  fseek(dico->file, 0, SEEK_END);
  for (size_t i = 0; i < count; i++) {
    fputs(words[i], dico->file);
  }
  if(synchronizeMetadata(dico) == false) {
    return dictionaryFromFileEx(dico, words, count, 5);
  }
  return dictionaryFromFileEx(dico, words, count, 0);
}

/**
 * \fn int dictionaryFromFileEx(Dictionary *dic, char **words, int count, int status)
 * \param dic Dictionary to free
 * \param words Array is string to free
 * \param count Number of strings into the given array
 * \param status Code error to raise
 *
 * \brief Manage Exception for the function int dictionaryFromFile(const char *filename, const char *dico_name)
 * \return Status of the Excpetion
 */
int dictionaryFromFileEx(Dictionary *dic, char **words, int count, int status) {
  freeDictionary(dic);
  freeBiChar(words, count);
  return status;
}

/**
 * \fn char **readTxtFile(const char *filename, int* count)
 * \param filename The path of the file on which to collect the words
 * \param count A pointer of Integer on which the words wil be count
 *
 * \brief Read a txt file and collect words
 * \return Array with the strings from the given file
 */
char **readTxtFile(const char *filename, int* count) {
  *count = countFileWord(filename);
  FILE *file = fopen(filename, "r");
  if (*count == -1 || file == NULL) {
    return NULL;
  }
  char **words = mallocBiChar(*count, 255);
  if (words == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < *count; i++) {
    fgets(words[i], 255, file);
  }
  fclose(file);
  return words;
}

/**
 * \fn char **strSortedMakeUniq(char **strings, int *size)
 * \param strings The array of strings to make uniq
 * \param size Size of th array
 *
 * \brief Check for duplicate strings into a sorted array and make them uniq
 * \return Array of strings without duplicate
 */
char **strSortedMakeUniq(char **strings, int *size) {
  for (size_t i = 0; i < *size - 1; ++i) {
    if(strcmp(strings[i], strings[i + 1]) == 0) {
      free(strings[i + 1]);
      for (size_t j = i + 1; j < *size - 1; ++j) {
        strings[j] = strings[j + 1];
      }
      i--;
      strings[--(*size)] = NULL;
    }
  }
  return strings;
}

/**
 * \fn void menuCreateDictionaryFromFile(void)
 *
 * \brief Help the user to create a dictionary from a text file
 */
void menuCreateDictionaryFromFile(void) {
  char *filename = malloc(sizeof(char) * 255);
  char *diconame = malloc(sizeof(char) * 255);
  printf("Please tape the path to your txt file: ");
  getString(255, filename);
  printf("Now give a name to the new dictionary: ");
  getString(255, diconame);
  switch (dictionaryFromFile(filename, diconame)) {
    case 1:
      printf("An error occured when reading the file.\n");
      break;
    case 2:
      printf("An error occured when creating the dictionary.\n");
      break;
    case 3:
    case 4:
      printf("An error occured when opening the dictionary.\n");
      break;
    case 5:
      printf("An error occured when setting the metadata.\n");
      break;
    default:
      printf("Dictionary %s has been created\n", diconame);
  }
  free(filename);
  free(diconame);
}
