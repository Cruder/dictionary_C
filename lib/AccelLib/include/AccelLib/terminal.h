#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include <stdarg.h> //va_args
#include "testOS.h"
#include <stdint.h>

void term_resize(const unsigned short int lng, const unsigned short int col);
//void term_posWin(const unsigned int x, const unsigned int y);
void term_posCursor(const unsigned int x, const unsigned int y);


/// Couleurs du terminal
typedef enum COLOR_TERMINAL
{
  #ifdef _IS_WINDOWS
    COLOR_BLACK=0x0,        COLOR_RED=0x4,        COLOR_GREEN=0x2,         COLOR_YELLOW=0x6,
    COLOR_BLUE=0x1,         COLOR_MAGENTA=0x5,    COLOR_CYAN=0x3,          COLOR_WHITE=0xF,
    COLOR_LIGHT_GRAY=0x7,   COLOR_DARK_GRAY=0x8,  COLOR_LIGHT_RED=0xC,     COLOR_LIGHT_GREEN=0xA,
    COLOR_LIGHT_YELLOW=0xE, COLOR_LIGHT_BLUE=0x9, COLOR_LIGHT_MAGENTA=0xD, COLOR_LIGHT_CYAN=0xB
  #else
    COLOR_BLACK=0,         COLOR_RED=1,         COLOR_GREEN=2,          COLOR_YELLOW=3,
    COLOR_BLUE=4,          COLOR_MAGENTA=5,     COLOR_CYAN=6,           COLOR_WHITE=67,
    COLOR_LIGHT_GRAY=7,    COLOR_DARK_GRAY=60,  COLOR_LIGHT_RED=61,     COLOR_LIGHT_GREEN=62,
    COLOR_LIGHT_YELLOW=63, COLOR_LIGHT_BLUE=64, COLOR_LIGHT_MAGENTA=65, COLOR_LIGHT_CYAN=66
  #endif
} COLOR_TERMINAL;

/* compatibilité avec ancien nommage des couleurs de base */
#define BLACK   COLOR_BLACK
#define RED     COLOR_RED
#define GREEN   COLOR_GREEN
#define YELLOW  COLOR_YELLOW
#define BLUE    COLOR_BLUE
#define MAGENTA COLOR_MAGENTA
#define CYAN    COLOR_CYAN
#define WHITE   COLOR_WHITE


/*!
 * Fonction effaçant le terminal
 */
void clear_terminal();

/*!
 * Printf en couleur. Les deux premiers paramètres sont les couleurs d'écriture et de fond (mettre une des valeurs parmi :
 * BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN et WHITE).
 * Les parmètres suivants sont comme le printf "normal" : chaîne de format puis toutes les valeurs à afficher
 */
int color_printf(COLOR_TERMINAL fg, COLOR_TERMINAL bg, const char * format, ...);

/*!
 * puts() en couleur.
 * S'utilise comme le puts "normal".
 */
int color_puts(COLOR_TERMINAL fg, COLOR_TERMINAL bg, const char *chaine);

/*!
 * putchar() en couleur.
 * S'utilise comme le putchar "normal".
 */
int color_putchar(COLOR_TERMINAL fg, COLOR_TERMINAL bg, const int caract);

/*!
 * Scanf en couleur. Les deux premiers paramètres sont les couleurs d'écriture et de fond (mettre une des valeurs parmi :
 * BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN et WHITE).
 * Les parmètres suivants sont comme le scanf "normal" : chaîne de format puis toutes les valeurs à récupérer
 */
int color_scanf(COLOR_TERMINAL fg, COLOR_TERMINAL bg, const char * format, ...);

/*!
 * gets() en couleur.
 * S'utilise comme le gets "normal".
 */
char* color_gets(COLOR_TERMINAL fg, COLOR_TERMINAL bg, char *s);

/*!
 * getchar() en couleur.
 * S'utilise comme le getchar "normal".
 */
int color_getchar(COLOR_TERMINAL fg, COLOR_TERMINAL bg);


typedef struct Size {
    uint16_t w, h;
} Size;

/*!
 * Récupère la taille de la console (en nombre de caractères)
 */
Size term_size();

#endif // TERMINAL_H_INCLUDED
