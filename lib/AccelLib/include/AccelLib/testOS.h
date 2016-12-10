#ifndef TESTOS_H_INCLUDED
#define TESTOS_H_INCLUDED

/** Détecte & définit l'environnement cible de la compilation */
#if defined(_WIN32) || defined(_win32) || defined(WIN32) || defined(win32) || defined(__WIN32__) || defined(__win32__) //__WINRT__
    #define _OS_WIN32 true
#elif defined(_WIN64) || defined(_win64) || defined(WIN64) || defined(win64) || defined(__WIN64__) || defined(__win64__)
    #define _OS_WIN64 true
#elif defined(LINUX) || defined(linux) || defined(_LINUX) || defined(_linux) || defined(__LINUX) || defined(__linux)
    #define _OS_LINUX true
#elif defined(__APPLE__) || defined(APPLE)
    #define _OS_APPLE true
#elif defined(__UNIX__) || defined(UNIX) || defined(unix) || defined(_UNIX) || defined(_unix)
    #define _OS_UNIX true
#endif // _WIN32

#if defined(_OS_WIN32) || defined(_OS_WIN64)
    #define _IS_WINDOWS true
    //#warning System Windows detected
#elif defined(_OS_UNIX) || defined(_OS_LINUX) || defined(_OS_APPLE)
    #define _IS_UNIX true
    #if !defined(_OS_LINUX) && !defined(_OS_APPLE)
        #warning Unknow System Unix detected
    #else
        //#message System Unix detected
    #endif
#else
    #error System not recognize
#endif // defined


/** Détecte le compilateur utilisé */
#if defined(_MSC_VER) || defined(MSVC) // Microsoft compiler
    #define _CMPL_MSVC true
#elifdef __GNUC__ // GNU compiler
    #define _CMPL_GNUC true
#else
    #warning Define your compiler
#endif // Compil

#endif // TESTOS_H_INCLUDED
