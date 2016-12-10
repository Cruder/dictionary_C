#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdbool.h>
#include <sys/types.h>

bool getFileSize(const char *filepath, off_t *size);

#endif // FILE_H_INCLUDED
