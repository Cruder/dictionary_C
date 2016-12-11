#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include <AccelLib/terminal.h>

/**
 * \struct Menu_entry
 * \brief Structure of an entry of a menu
 */
typedef struct Menu_entry {
    const char choice;
    const char *msg;
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

/**
 * \struct ColorStr
 * \brief Simlple structure for color text
 */
typedef struct ColorStr {
    COLOR_TERMINAL fg, bg;
    char *str;
} ColorStr;

ColorStr txtColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);
ColorStr nullColor();

void Menu_askString(const COLOR_TERMINAL question_color, const char question[],
                    const COLOR_TERMINAL answer_color, char *answer[], const unsigned int answer_size,
                    const bool answer_allow_void);
char Menu_askChar(const COLOR_TERMINAL question_color, const char question[],
                  const COLOR_TERMINAL answer_color, const bool answer_allow_void);
bool Menu_askYesNo(const COLOR_TERMINAL question_color, const char question[],
                   const COLOR_TERMINAL answer_color, const char answer_yes, const char answer_no,
                   const Menu_Default answer_default);

void Menu_section(const char str[]);
void Menu_sectionColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);
void Menu_title(const char str[]);
void Menu_titleColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);

bool Menu_entries_valid(const char choice, const Menu_entry entries[], const unsigned int nb);
void Menu_ChoicePrint(const ColorStr title, const ColorStr msg, const Menu_entry choices[], const unsigned int nb);
char Menu_Choice(const ColorStr title, const ColorStr msg, const Menu_entry choices[], const unsigned int nb);


#endif // MENU_H_INCLUDED
