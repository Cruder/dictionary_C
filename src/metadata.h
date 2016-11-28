#ifndef __METADATA_H__
#define __METADATA_H__

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

/** @struct Metadata
 *  @brief Structure des métadonnées d'un dictionnaire
 *  @var Metadata::letters
 *  Positions de la 1ère lettre des mots (ordre alphabétique)
 *  @var Metadata::letters::ligne
 *  Positions de la ligne
 *  @var Metadata::letters::bytes
 *  Positions de l'octet, utilisé pour se positionner dans le fichier
 *  @var Metadata::file
 *  Fichier des métadonnées
 */
 typedef struct Metadata {
  size_t length; //nombre de lignes/mots
  struct /*section*/ {
      /*unsigned*/ int ligne;
      long bytes;
  } letters[26]; // Position on the document
  FILE *file;
} Metadata;

Metadata* emptyMetadata();
bool createMetadata(const char *filename);
Metadata* loadMetadata(const char *filename);
FILE* openMetadataFile(const char *filename, const char *rights);
void freeMetadata(Metadata **m);
void displayMetadata(const Metadata *m);
void updateWordInfo(Metadata *meta, const uint8_t letter, const size_t len);

#endif /* end of include guard: __METADATA_H__ */
