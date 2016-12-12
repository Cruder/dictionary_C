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
 * \brief Helper function for create ColorStr structure
 * \param fg : color of the font or foregroung
 * \param bg : color of the background
 * \param str : text to color
 * \return ColorStr strcture initialise with datas
 */
ColorStr txtColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    ColorStr cs = (ColorStr){.fg = fg, .bg = bg, .str = str};
    return cs;
}

/**
 * \brief Helper function for create null ColorStr structure
 * \return ColorStr strcture initialise to null
 */
ColorStr nullColor() {
    ColorStr cs = {.fg = COLOR_BLACK, .bg = COLOR_BLACK, .str = NULL};
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
void menuSectionColor(const ColorStr section) {
    const size_t len = strlen(section.str) + 2*2;
    unsigned int i;
    const char spec[2] = {SECTION_CHAR, '\0'};
    for(i=0 ; i < len ; i++)
        color_puts(section.fg, section.bg, spec);
    color_printf(section.fg, section.bg, "\n%c %s %c\n", SECTION_CHAR, section.str, SECTION_CHAR);
    for(i=0 ; i < len ; i++)
        color_puts(section.fg, section.bg, spec);
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
void menuTitleColor(const ColorStr title) {
    color_printf(title.fg, title.bg, " %s %c\n", title.str, TITLE_CHAR_END);
    const size_t len = strlen(title.str) + 3 -1;
    unsigned int i;
    /*const*/ char spec[2] = {TITLE_CHAR_UNDER, '\0'};
    for(i=0 ; i < len ; i++)
        color_puts(title.fg, title.bg, spec);
    spec[0] = TITLE_CHAR_CROSS;
    color_puts(title.fg, title.bg, spec);
    putchar('\n');
}

/**
 * \brief Print the title, message and choices of a menu
 * \param title : title of the menu
 * \param msg : message of menu (facultatif)
 * \param choices : choices of the menu
 * \param nb : number of choices
 */
void menuChoicePrint(const ColorStr title, const ColorStr msg, const MenuEntry choices[], const unsigned int nb) {
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
char menuChoice(const ColorStr title, const ColorStr msg, const MenuEntry choices[], const unsigned int nb) {
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
void menuAskString(const ColorStr question,
                   const COLOR_TERMINAL answerColor, char *answer[], const unsigned int answerSize,
                   const bool answerAllowVoid) {
    char *buffer = NULL;
    do {
        color_printf(question.fg, question.bg, "%s ", question.str);
        //scanf("%" STR(sizeof(UINT32_MAX)-1) "[^\n]%*[^\n]", answer);
        scanf("%m[^\n]", &buffer);
        if(buffer == NULL) { //si scanf n'a pas réussi à alloué le buffer
            answer[0] = '\0';
            return;
        } else
            strncpy(*answer, buffer, answerSize);
    } while((!answerAllowVoid) && (strlen(*answer) <= 0));
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
char menuAskChar(const ColorStr question,
                 const COLOR_TERMINAL answerColor, const bool answerAllowVoid) {
    char answer;
    do {
        color_printf(question.fg, question.bg, "%s ", question.str);
        scanf("%c%*c", &answer);
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
bool menuAskYesNo(const ColorStr question,
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
