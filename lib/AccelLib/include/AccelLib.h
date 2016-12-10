#ifndef ACCELLIB_H_INCLUDED
#define ACCELLIB_H_INCLUDED
/*
Cette librairie essaye d'être au maximum multi-plateforme (principalement Windows (MinGW) et Unix (GCC)).
*/
/*
Fichier raccourci incluant toutes les sous-parties.
*/

/** Permet de tester/détecter l'environnement de compilation */
//#include "AccelLib\testOS.h"

/** pseudo-librairie de logging légère */
//#include "AccelLib\_log.h"

/** Fonctionnalités relative au temps */
#include "AccelLib\time.h"

/** Permet une utilisation avancée du terminal */
#include "AccelLib\terminal.h"

/** Gestion légère des versions */
#include "AccelLib\version.h"

/** Fonctionnalités relative aux chaines de caractère */
#include "AccelLib\strings.h"

/** Fonctionnalités relative aux fichiers */
#include "AccelLib\file.h"

#endif // ACCELLIB_H_INCLUDED
