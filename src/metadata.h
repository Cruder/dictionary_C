#ifndef __METADATA_H__
#define __METADATA_H__

#include <stdio.h>
#include <stdbool.h>

bool createMetadata(const char *filename);
FILE* OpenMetadataFile(const char *filename, const char *rights);

#endif /* end of include guard: __METADATA_H__ */
