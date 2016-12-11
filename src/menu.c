#include "menu.h"
#include <AccelLib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

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
        scanf("%c%*[^\n]", &answer);
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
