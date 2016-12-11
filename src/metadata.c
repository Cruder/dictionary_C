#include "metadata.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/**
 * \fn Metadata *emptyMetadata()
 *
 * \brief Function for init a Dictionary struct
 * \return Boolean of success or not
 */
Metadata *emptyMetadata() {
    Metadata *m = malloc(sizeof(Metadata));
    m->file = NULL;
    return m;
}

/**
 * \fn bool createMetadata(const char *filename)
 * \param filename String corresponding to the name of the file to create
 *
 * \brief Function for creating a default metadata file
 * \return Boolean of success or not
 */
bool createMetadata(const char *filename) {
    FILE *file = openMetadataFile(filename, "w");
    if (!file) {
        return false;
    }
    fprintf(file, "# dictionary\n");
    fprintf(file, "# length: 0\n");
    fprintf(file, "# threshold: 0\n");
    for(char i = 0; i < 26; ++i) {
        fprintf(file, "# %c_start: 24\n", 'a' + i);
    }
    fclose(file);
    return true;
}

/**
 * \fn FILE* openMetadataFile(const char *filename, const char *rights)
 * \param filename String corresponding to the name of the file to open
 * \param rights String with open mode of the file
 *
 * \brief Function for opening a metadata file
 * \return FILE* pointer to the file, NULL if failure
 */
FILE* openMetadataFile(const char *filename, const char *rights) {
    char *filename_ext = malloc(strlen(filename) + 32);
    sprintf(filename_ext, "resources/dictionaries/.%s.mda", filename);
    FILE *file = fopen(filename_ext, rights);
    free(filename_ext);
    filename_ext = NULL;
    return file;
}

/**
 * \fn Metadata *loadMetadata(const char *filename)
 * \param filename String corresponding to the name of the file to open
 *
 * \brief Function for opening a metadata file
 * \return FILE* pointer to the file, NULL if failure
 */
Metadata *loadMetadata(const char *filename) {
    Metadata *m = emptyMetadata();
    m->file = openMetadataFile(filename, "r");
    if(m->file) {
        fscanf(m->file, "# dictionary\n");
        fscanf(m->file, "# length: %zu\n", &m->length);
        fscanf(m->file, "# threshold: %zu\n", &m->threshold);
        for(size_t i = 0; i < 26; ++i) {
            char empty;
            fscanf(m->file, "# %c_start: %ld\n", &empty, &m->letters[i]);
        }
        fclose(m->file);
        m->file = NULL;
    }
    return m;
}

/**
 * \fn void freeMetadata(Metadata *m)
 * \param m Metadata struct pointer
 *
 * \brief Free the m Metadata struct
 */
void freeMetadata(Metadata *m) {
    if(m->file) {
        fclose(m->file);
        m->file = NULL;
    }
    free(m);
    m = NULL;
}

/**
 * \fn void displayMetadata(const Metadata *m)
 * \param m Metadata struct pointer
 *
 * \brief Display the length and all the start_letter
 */
void displayMetadata(const Metadata *m) {
    printf("length: %zu\n", m->length);
    printf("threshold: %zu\n", m->threshold);
    for (int i = 0; i < 26; i++) {
        printf("%c_start: %ld\n", 'a' + i, m->letters[i]);
    }
    printf("\n");
}

/**
 * \fn void metadataWordAdded(Metadata *m, const char *filename, char *word)
 * \param m Metadata struct pointer
 * \param filename The filename to open
 * \param word The word added to the dictionary
 *
 * \brief Update and save the metadata for a word
 */
void metadataWordAdded(Metadata *m, char *word) {
    size_t length = strlen(word) + 1; // Word + \n
    size_t begin = (size_t)(word[0] - 'a' + 1);


    for(size_t i = begin; i < 26; ++i) {
        m->letters[i] += length;
    }
    ++m->length;
}

/**
 * \fn bool setMetadata(Metadata *m, const char *filename)
 * \param m Metadata struct pointer
 * \param filename String corresponding to the name of the file to open
 *
 * \brief Display the length and all the start_letter
 */
bool setMetadata(Metadata *m, const char *filename) {
    m->file = openMetadataFile(filename, "w");
    if (m->file == NULL) {
        return false;
    }

    fprintf(m->file, "# dictionary\n");
    fprintf(m->file, "# length: %zu\n", m->length);
    fprintf(m->file, "# threshold: %zu\n", m->threshold);
    for(char i = 0; i < 26; ++i) {
        fprintf(m->file, "# %c_start: %ld\n", 'a' + i, m->letters[(int)i]);
    }
    fputc('\n', m->file);

    fclose(m->file);
    m->file = NULL;
    return true;
}

/**
 * \fn int removeMetadata(const char *filename)
 * \param filename The name of the file
 * \return The code of file delete
 */
int removeMetadata(const char *filename) {
    char *filename_ext = malloc(sizeof(char) * (strlen(filename) + 32));
    sprintf(filename_ext, "resources/dictionaries/.%s.mda", filename);
    if(metadataArePresent(filename)) {
        return remove(filename_ext);
    }
    return 0;
}

/**
 * \fn bool metadataArePresent(const char *filename)
 * \param filename The name of the file
 * \return true if metadata found, otherwise false
 */
bool metadataArePresent(const char *filename) {
    DIR *dir = opendir("resources/dictionaries");
    struct dirent *ent;
    if (dir) {
        char *filename_ext = malloc(sizeof(char) * (strlen(filename) + 6));
        sprintf(filename_ext, ".%s.mda", filename);
        while ((ent = readdir(dir)) != NULL) {
            if(strcmp(ent->d_name, filename_ext) == 0) {
                free(filename_ext);
                closedir(dir);
                return true;
            }
        }
        free(filename_ext);
        closedir(dir);
    }
    return false;
}
