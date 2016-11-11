#include "gestbib.h"

/**
 * \fn void printMainMenu()
 * \brief Function for display the main menu
 *
 */
void printMainMenu() {
  printf("\n\n*** Dictionnries management ***\n\n"
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
         "\t0. Return to Dictionnries management\n\n");
}

/**
 * \fn void mainMenu()
 * \brief Function for guide user into the main menu
 *
 */
void mainMenu() {
  int choice;
  printMainMenu();
  do {
    do {
      printf("Your choice: ");
    } while(!getIntRange(&choice, 0, 4));

    switch (choice) {
      case 1:
        menu();
        break;
      case 2:
        printf("create empty\n");
        break;
      case 3:
        printf("create full\n");
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

/**
 * \fn void mainMenu()
 * \brief Function for guide user into the second menu
 *
 */
void menu() {
  int choice;
  printMenu();
  do {
    do {
      printf("Your choice: ");
    } while(!getIntRange(&choice, 0, 2));

    switch (choice) {
      case 1:
        printf("Add a word\n");
        break;
      case 2:
        printf("Search a word\n");
        break;
      case 0:
        clear();
        printMainMenu();
        break;
    }
  } while(choice != 0);
}
