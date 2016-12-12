#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include <AccelLib/terminal.h>

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
 * \struct ColorStr
 * \brief Simlple structure for color text
 */
typedef struct ColorStr {
    COLOR_TERMINAL fg, bg;
    char *str;
} ColorStr;

ColorStr txtColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg);
ColorStr nullColor();

void menuAskString(const ColorStr question,
                   const COLOR_TERMINAL answerColor, char *answer[], const unsigned int answerSize,
                   const bool answerAllowVoid);
char menuAskChar(const ColorStr question,
                 const COLOR_TERMINAL answerColor, const bool answerAllowVoid);
bool menuAskYesNo(const ColorStr question,
                  const COLOR_TERMINAL answerColor, const char answerYes, const char answerNo,
                  const MenuDefault answerDefault);

void menuSection(const char str[]);
void menuSectionColor(const ColorStr section);
void menuTitle(const char str[]);
void menuTitleColor(const ColorStr title);

bool menuEntriesValid(const char choice, const MenuEntry entries[], const unsigned int nb);
void menuChoicePrint(const ColorStr title, const ColorStr msg, const MenuEntry choices[], const unsigned int nb);
char menuChoice(const ColorStr title, const ColorStr msg, const MenuEntry choices[], const unsigned int nb);


#endif // MENU_H_INCLUDED
