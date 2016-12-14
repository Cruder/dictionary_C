#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include <AccelLib/terminal.h>

#define pause_msg() {color_printf(COLOR_DARK_GRAY, COLOR_BLACK, "Press any key to continue"); \
                 color_getchar(COLOR_BLACK, COLOR_BLACK);}

/**
 * \struct Menu_entry
 * \brief Structure of an entry of a menu
 */
typedef struct MenuEntry {
    const char choice;
    const char *msg;
} MenuEntry;

/**
 * \enum Menu_Default
 * \brief Default answer for a yes/no question
 */
typedef enum MenuDefault {
    DefaultNo, ///< Default answer is No
    DefaultYes, ///< Default answer is Yes
    DefaultAny ///< No default answer
} MenuDefault;

/**
 * \struct ColorOut
 * \brief Simlple structure for color text
 */
typedef struct ColorOut {
    COLOR_TERMINAL fg, bg;
    char *str;
} ColorOut;

ColorOut txtColor(/*const*/ char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);
ColorOut nullColor();

/**
 * \struct ColorOut
 * \brief Simlple structure for color text
 */
typedef struct ColorIn {
    COLOR_TERMINAL fg, bg;
    char **str;
    unsigned int size;
} ColorIn;

ColorIn inColor(/*const*/ char **str, const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);

void menuAskString(const ColorOut question, const ColorIn answer, const bool answerAllowVoid);
char menuAskChar(const ColorOut question,
                 const COLOR_TERMINAL answerColor, const bool answerAllowVoid);
bool menuAskYesNo(const ColorOut question,
                  const COLOR_TERMINAL answerColor, const char answerYes, const char answerNo,
                  const MenuDefault answerDefault);

void menuSection(const char str[]);
void menuSectionColor(const ColorOut section);
void menuTitle(const char str[]);
void menuTitleColor(const ColorOut title);

bool menuEntriesValid(const char choice, const MenuEntry entries[], const unsigned int nb);
void menuChoicePrint(const ColorOut title, const ColorOut msg, const MenuEntry choices[], const unsigned int nb);
char menuChoice(const ColorOut title, const ColorOut msg, const MenuEntry choices[], const unsigned int nb);


#endif // MENU_H_INCLUDED
