#ifndef __METADATA_H__
#define __METADATA_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  size_t length;
  long letters[26]; // Position on the document
  FILE *file;
} Metadata;

Metadata *emptyMetadata();
bool createMetadata(const char *filename);
Metadata *loadMetadata(const char *filename);
FILE* openMetadataFile(const char *filename, const char *rights);
void freeMetadata(Metadata *m);
void displayMetadata(const Metadata *m);
bool setMetadata(Metadata *m, const char *filename);
void metadataWordAdded(Metadata *m, const char *filename, char *word);
int removeMetadata(const char *filename);
bool metadataArePresent(const char *filename);

#endif /* end of include guard: __METADATA_H__ */
