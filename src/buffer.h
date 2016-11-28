#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#define clear_error() errno = 0

typedef uint8_t bufType;
/**
 * \struct BufferCircular
 * \brief Structure définissant un buffer circulaire
 */
typedef struct BufferCircular BufferCircular;

/**
 * \brief Créer un buffer circulaire
 * \param size taille du buffer
 * \return Le buffer initialisé
 */
BufferCircular* BufferCircular_create(const unsigned int size);

/**
 * \brief Libère un buffer circulaire
 * \param bufc pointeur vers le buffer circulaire
 */
void BufferCircular_free(BufferCircular **bufc);


/**
 * \brief Retourne la taille (maximale) du buffer circulaire
 * \param bufc buffer dont on veut connaitre la taille
 * \return la taille du buffer
 */
unsigned int BufferCircular_size(const BufferCircular *bufc);

/**
 * \brief Retourne la taille des données présentes dans le buffer
 * \param bufc buffer à vérifier
 * \return nombre de données dans le buffer
 */
unsigned int BufferCircular_available(const BufferCircular *bufc);

/**
 * \brief Test si le buffer est vide
 * \param bufc le buffer à tester
 * \return true si le buffer est vide, false sinon
 */
bool BufferCircular_isEmpty(const BufferCircular *bufc);

/**
 * \brief Test si le buffer est plein
 * \param bufc buffer à tester
 * \return true si le buffer est plein, false sinon
 */
/*inline*/ bool BufferCircular_isFull(const BufferCircular *bufc);

/**
 * \brief ajoute un élément au buffer
 * \param bufc buffer auquel ajouter l'élément
 * \param byte octet à ajouter
 * \return true si l'ajout à réussi, false sinon
 */
bool BufferCircular_put(BufferCircular *bufc, const bufType byte);

/**
 * \brief récupère un élément du buffer
 * \param bufc buffer duquel récupérer un élément
 * \return octect du buffer
 */
bufType BufferCircular_get(BufferCircular *bufc);

/**
 * \brief ajoute un ensemble d'élément au buffer
 * \param bufc buffer en question
 * \param bytes tableau contenant les données à ajouter
 * \param size nombre d'élément à ajouter
 * \return le nombre d'élément ajoutés
 */
unsigned int BufferCircular_puts(BufferCircular *bufc, const bufType bytes[], const unsigned int size);

/**
 * \brief récupérer un ensemble d'élément du buffer
 * \param bufc buffer
 * \param bytes table de taille size acceuillant les données du buffer
 * \param size taille du tableau d'acceuil
 * \return le nombre d'élément récupérés
 */
unsigned int BufferCircular_gets(BufferCircular *bufc, bufType bytes[], const unsigned int size);


#endif // BUFFER_H_INCLUDED
