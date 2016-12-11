#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#define STR(s) #s

/**
 * \brief Convertir une chaine de caractère en minuscule
 * \param str chaine de caractère à convertir
 *
 * Utilise en interne la fonction tolower de ctype
 */
void str_tolower(char str[]);

/**
 * \brief Convertir une chaine de caractère en majuscule
 * \param str chaine de caractère à convertir
 *
 * Utilise en interne la fonction toupper de ctype
 */
void str_toupper(char str[]);


#endif // STRINGS_H_INCLUDED
