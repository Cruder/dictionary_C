#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>

/**
 * \struct Menu_entry
 * \brief Structure of an entry of a menu
 */
typedef struct Menu_entry {
    const char choice;
    const char msg[];
} Menu_entry;

/**
 * \enum Menu_Default
 * \brief Default answer for a yes/no question
 */
typedef enum Menu_Default {
    Menu_No, ///< Default answer is No
    Menu_Yes, ///< Default answer is Yes
    Menu_Any ///< No default answer
} Menu_Default;


void Menu_askString(const COLOR_TERMINAL question_color, const char question[],
                    const COLOR_TERMINAL answer_color, char *answer[], const unsigned int answer_size,
                    const bool answer_allow_void);
char Menu_askChar(const COLOR_TERMINAL question_color, const char question[],
                  const COLOR_TERMINAL answer_color, const bool answer_allow_void);
bool Menu_askYesNo(const COLOR_TERMINAL question_color, const char question[],
                   const COLOR_TERMINAL answer_color, const char answer_yes, const char answer_no,
                   const Menu_Default answer_default);



#endif // MENU_H_INCLUDED
