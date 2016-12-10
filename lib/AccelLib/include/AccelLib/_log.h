#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED

/** Fonction de log dans un fichier au nom générrer aléatoirement (mais unique) */
/* flog et non log car conflit avec math.h ... */

#ifdef NDEBUG
    #define flog_init(b_aff_src) ((void)0)
    #define flog(msg, ...) ((void)0)
    #define flog_add(msg, ...) ((void)0)
#else
    #include <stdarg.h>
    #include <stdbool.h>
void flog_init(const bool aff_src, const char *file, const int line);
#define flog_init(b_aff_src) flog_init(b_aff_src, __FILE__, __LINE__)

#define FLOG_B 1
#ifndef FLOG_B
    void flog(const char *file, const int line, const const char * format, ...);
    #define flog(format, ...)     flog(__FILE__, __LINE__, format, __VA_ARGS__)
    void flog_add(const char *file, const int line, const const char * format, ...);
    #define flog_add(format, ...)     flog_add(__FILE__, __LINE__, format, __VA_ARGS__)
#else
    void flog_b(bool newLine, const char *file, const int line, const const char * format, ...);
    #define flog(format, ...)     flog_b(true, __FILE__, __LINE__, format, __VA_ARGS__)
    #define flog_add(format, ...) flog_b(false, __FILE__, __LINE__, format, __VA_ARGS__)
#endif // FLOG_B

/* au cas ou si l'utilisateur en a besoin */
bool flog_is_affSrc();
bool flog_is_init();
#endif // NDEBUG


#endif // _LOG_H_INCLUDED
