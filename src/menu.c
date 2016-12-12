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
void Menu_sectionColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    const size_t len = strlen(str) + 2*2;
    unsigned int i;
    const char spec[2] = {SECTION_CHAR, '\0'};
    for(i=0 ; i < len ; i++)
        color_puts(fg, bg, spec);
    color_printf(fg, bg, "\n%c %s %c\n", SECTION_CHAR, str, SECTION_CHAR);
    for(i=0 ; i < len ; i++)
        color_puts(fg, bg, spec);
    putchar('\n');
}

/**
 * \brief Print a title
 * \param the string of the title
 */
void Menu_title(const char str[]) {
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
void Menu_titleColor(const char str[], const COLOR_TERMINAL fg, const COLOR_TERMINAL bg) {
    color_printf(fg, bg, " %s %c\n", str, TITLE_CHAR_END);
    const size_t len = strlen(str) + 3 -1;
    unsigned int i;
    /*const*/ char spec[2] = {TITLE_CHAR_UNDER, '\0'};
    for(i=0 ; i < len ; i++)
        color_puts(fg, bg, spec);
    spec[0] = TITLE_CHAR_CROSS;
    color_puts(fg, bg, spec);
    putchar('\n');
}

/**
 * \brief Print the title, message and choices of a menu
 * \param title : title of the menu
 * \param msg : message of menu (facultatif)
 * \param choices : choices of the menu
 * \param nb : number of choices
 */
void Menu_ChoicePrint(const ColorStr title, const ColorStr msg, const Menu_entry choices[], const unsigned int nb) {
    Menu_titleColor(title.str, title.fg, title.bg);
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
bool Menu_entries_valid(const char choice, const Menu_entry entries[], const unsigned int nb) {
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
char Menu_Choice(const ColorStr title, const ColorStr msg, const Menu_entry choices[], const unsigned int nb) {
    bool continu = true;
    char choice;
    uint8_t cnt;
    while(continu) {
        clear_terminal();
        Menu_ChoicePrint(title, msg, choices, nb);
        putchar('\n');
        cnt = 0;
        while(continu && (cnt < 5)) {
            choice = Menu_askChar(COLOR_LIGHT_GRAY, "Your choice :", COLOR_LIGHT_BLUE, true);
            printf("answer = %c\n", choice);
            continu = !Menu_entries_valid(choice, choices, nb);
            printf("continu = %u\n", continu);
            cnt++;
            printf("cnt = %u\n", cnt);
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
void Menu_askString(const COLOR_TERMINAL question_color, const char question[],
                    const COLOR_TERMINAL answer_color, char *answer[], const unsigned int answer_size,
                    const bool answer_allow_void) {
    char *buffer = NULL;
    do {
        color_printf(question_color, COLOR_BLACK, "%s ", question);
        //scanf("%" STR(sizeof(UINT32_MAX)-1) "[^\n]%*[^\n]", answer);
        scanf("%m[^\n]", &buffer);
        if(buffer == NULL) { //si scanf n'a pas réussi à alloué le buffer
            answer[0] = '\0';
            return;
        } else
            strncpy(*answer, buffer, answer_size);
    } while((!answer_allow_void) && (strlen(*answer) <= 0));
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
char Menu_askChar(const COLOR_TERMINAL question_color, const char question[],
                  const COLOR_TERMINAL answer_color, const bool answer_allow_void) {
    char answer;
    do {
        color_printf(question_color, COLOR_BLACK, "%s ", question);
        scanf("%c%*c", &answer);
    } while((!answer_allow_void) && (answer == '\n'));
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
bool Menu_askYesNo(const COLOR_TERMINAL question_color, const char question[],
                   const COLOR_TERMINAL answer_color, const char answer_yes, const char answer_no, const Menu_Default answer_default) {
    const bool allow_void = (answer_default != Menu_Any);
    char answer;
    do {
        answer = Menu_askChar(question_color, question, answer_color, allow_void);
        if(answer == '\n') //si l'utilisateur à répondu vide donc défaut
            answer = (answer_default == Menu_Yes) ? answer_yes : answer_no;
    } while((answer != answer_yes) && (answer != answer_no));
    return tolower(answer) == tolower(answer_yes);
}
