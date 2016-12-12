#include "menu.h"
#include <AccelLib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

#define SECTION_CHAR '='
#define TITLE_CHAR_UNDER '-'
#define TITLE_CHAR_CROSS '+'
#define TITLE_CHAR_END '|'
#define SUBTITLE_CHAR '-'

#define MENU_OPT_CHAR '.'
#define MENU_ASK_COLOR_FG COLOR_LIGHT_GRAY
#define MENU_ASK_COLOR_BG COLOR_BLACK
#define askColor(str) txtColor(str, MENU_ASK_COLOR_FG, MENU_ASK_COLOR_BG)

#define puts(input) fputs(input, stdout)
#define color_puts(fg, bg, str) color_printf(fg, bg, "%s", str) //puts() insère un \n ...

/**
 * \brief Helper function for create ColorOut structure
 * \param fg : color of the font or foregroung
 * \param bg : color of the background
 * \param str : text to color
 * \return ColorOut strcture initialise with datas
 */
ColorOut txtColor(/*const*/ char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    ColorOut cs = (ColorOut){.fg = fg, .bg = bg, .str = str};
    return cs;
}

/**
 * \brief Helper function for create null ColorOut structure
 * \return ColorOut strcture initialise to null
 */
ColorOut nullColor() {
    ColorOut cs = {.fg = COLOR_BLACK, .bg = COLOR_BLACK, .str = NULL};
    return cs;
}

/**
 * \brief Helper function for create ColorIn structure
 * \param fg : color of the font or foregroung
 * \param bg : color of the background
 * \param str : string where save the input
 * \return ColorIn strcture initialise with datas
 */
ColorIn inColor(/*const*/ char **str, const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    ColorIn cs = (ColorIn){.fg = fg, .bg = bg, .str = str};
    return cs;
}

/**
 * \brief Print a section title
 * \param str : the title of the secion
 */
void Menu_section(const char str[]) {
    const size_t len = strlen(str) + 2*2;
    unsigned int i;
    for(i=0 ; i < len ; i++)
        putchar(SECTION_CHAR);
    printf("\n%c %s %c\n", SECTION_CHAR, str, SECTION_CHAR);
    for(i=0 ; i < len ; i++)
        putchar(SECTION_CHAR);
    putchar('\n');
}

/**
 * \brief Print a section title
 * \param str : the title of the secion
 * \param fg : the color the font or foreground
 * \param bg : the color the background
 */
void menuSectionColor(const ColorOut section) {
    const size_t len = strlen(section.str) + 2*2;
    unsigned int i;
    for(i=0 ; i < len ; i++)
        color_putchar(section.fg, section.bg, SECTION_CHAR);
    color_printf(section.fg, section.bg, "\n%c %s %c\n", SECTION_CHAR, section.str, SECTION_CHAR);
    for(i=0 ; i < len ; i++)
        color_putchar(section.fg, section.bg, SECTION_CHAR);
    putchar('\n');
}

/**
 * \brief Print a title
 * \param the string of the title
 */
void menuTitle(const char str[]) {
    printf(" %s %c\n", str, TITLE_CHAR_END);
    const size_t len = strlen(str) + 3 -1;
    unsigned int i;
    for(i=0 ; i < len ; i++)
        putchar(TITLE_CHAR_UNDER);
    putchar(TITLE_CHAR_CROSS);
    putchar('\n');
}

/**
 * \brief Print a title
 * \param the string of the title
 */
void menuTitleColor(const ColorOut title) {
    color_printf(title.fg, title.bg, " %s %c\n", title.str, TITLE_CHAR_END);
    const size_t len = strlen(title.str) + 3 -1;
    unsigned int i;
    for(i=0 ; i < len ; i++)
        color_putchar(title.fg, title.bg, TITLE_CHAR_UNDER);
    color_putchar(title.fg, title.bg, TITLE_CHAR_CROSS);
    putchar('\n');
}

/**
 * \brief Print the title, message and choices of a menu
 * \param title : title of the menu
 * \param msg : message of menu (facultatif)
 * \param choices : choices of the menu
 * \param nb : number of choices
 */
void menuChoicePrint(const ColorOut title, const ColorOut msg, const MenuEntry choices[], const unsigned int nb) {
    menuTitleColor(title);
    if(msg.str != NULL)
        color_printf(msg.fg, msg.bg, "%s\n\n", msg.str);
    unsigned int i;
    for(i=0 ; i < nb ; i++) {
        printf("\t%c", choices[i].choice);
        printf("%c ", MENU_OPT_CHAR);
        printf("%s\n", choices[i].msg);
    }
}

/**
 * \brief Test if choice is valid
 * \param choice : the choice to check
 * \param entries : entries to see
 * \param nb : number of entries to see
 * \return true if choice is in entries, false else
 */
bool menuEntriesValid(const char choice, const MenuEntry entries[], const unsigned int nb) {
    unsigned int i;
    const char comp = tolower(choice);
    for(i=0 ; i < nb ; i++)
        if(tolower(entries[i].choice) == comp)
            return true;
    return false;
}

/**
 * \brief Show a menu and return the choice of user
 * \param title : title of the menu
 * \param msg : message of menu (facultatif)
 * \param choices : choices of the menu
 * \return the choice of user
 */
char menuChoice(const ColorOut title, const ColorOut msg, const MenuEntry choices[], const unsigned int nb) {
    bool continu = true;
    char choice;
    uint8_t cnt;
    while(continu) {
        clear_terminal();
        menuChoicePrint(title, msg, choices, nb);
        putchar('\n');
        cnt = 0;
        while(continu && (cnt < 5)) {
            choice = menuAskChar(askColor("Your choice :"), COLOR_LIGHT_BLUE, true);
            continu = !menuEntriesValid(choice, choices, nb);
            cnt++;
        }
    }
    return choice;
}

/**
 * \brief Menu that ask question to user
 * \param question_color color of the question
 * \param question the question to the user
 * \param answer_color color of user answer
 * \param answer string where save the response
 * \param answer_size the max size of the response (without the \0)
 * \param answer_allow_void allow the answer can be void (if no then re-ask while it's void)
 *
 * Do a question to the user and ask while user haven't answer.
 */
void menuAskString(const ColorOut question, const ColorIn answer, const bool answerAllowVoid) {
    char *buffer = NULL;
    do {
        color_printf(question.fg, question.bg, "%s ", question.str);
        //scanf("%" STR(sizeof(UINT32_MAX)-1) "[^\n]%*[^\n]", answer);
        color_scanf(answer.fg, answer.bg, "%m[^\n]", &buffer);
        if(buffer == NULL) { //si scanf n'a pas réussi à alloué le buffer
            *(answer.str)[0] = '\0';
            return;
        } else
            strncpy(*(answer.str), buffer, answer.size);
    } while((!answerAllowVoid) && (strlen(*(answer.str)) <= 0));
}

/**
 * \brief Menu that ask question to user
 * \param question_color color of the question
 * \param question the question to the user
 * \param answer_color color of user answer
 * \param answer_allow_void allow the answer can be void (if no then re-ask while it's void)
 * \return the character done by user, \n if void
 *
 * Do a question to the user and ask while user haven't answer.
 */
char menuAskChar(const ColorOut question,
                 const COLOR_TERMINAL answerColor, const bool answerAllowVoid) {
    char answer;
    do {
        color_printf(question.fg, question.bg, "%s ", question.str);
        color_scanf(answerColor, MENU_ASK_COLOR_BG, "%c%*c", &answer);
    } while((!answerAllowVoid) && (answer == '\n'));
    return answer;
}

/**
 * \brief Menu that ask question to user with response yes/no
 * \param question_color color of the question
 * \param question the question to the user
 * \param answer_color color of user answer
 * \param answer_yes character for yes response
 * \param answer_no character for no response
 * \param answer_default permit a default response if user respond void
 * \return true if yes, false if no
 *
 * Do a question to the user where answer can only be yes or no, and ask while user haven't answer.
 */
bool menuAskYesNo(const ColorOut question,
                  const COLOR_TERMINAL answerColor, const char answerYes, const char answerNo,
                  const MenuDefault answerDefault) {
    const bool allow_void = (answerDefault != DefaultAny);
    char answer;
    do {
        answer = menuAskChar(question, answerColor, allow_void);
        if(answer == '\n') //si l'utilisateur à répondu vide donc défaut
            answer = (answerDefault == DefaultYes) ? answerYes : answerNo;
    } while((answer != answerYes) && (answer != answerNo));
    return tolower(answer) == tolower(answerYes);
}
