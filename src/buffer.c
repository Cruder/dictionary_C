#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>

#define inline static inline

struct BufferCircular {
    bufType *buf; /*!< la zone mémoire du buffer */
    unsigned int size; /*!< la taille du buffer */
    unsigned int pos_start, pos_end; /*!< la position de début et de fin des données dans le buffer */
};

BufferCircular* BufferCircular_create(const unsigned int size) {
    if(size <= 0) {
        errno = EINVAL; // Invalid argument (POSIX.1)
        return NULL;
    }
    clear_error();
    BufferCircular *bufc = calloc(1, sizeof(BufferCircular));
    if(bufc == NULL)
        perror("calloc(BufferCircular)");
    else {
        clear_error();
        bufc->buf = malloc(sizeof(uint8_t) * size);
        if(bufc->buf == NULL) {
            perror("malloc(buffer)");
            free(bufc);
            bufc = NULL;
        } else
            bufc->size = size;
            //bufc->pos_put = bufc->pos_get = 0;
    }
    return bufc;
}

void BufferCircular_free(BufferCircular **bufc) {
    if(bufc != NULL) {
        free((*bufc)->buf);
        free(*bufc);
        *bufc = NULL;
    }
}

/**
 * Si les données s'étendent de la fin au début du buffer.
 */
inline bool BufferCircular_intern_jumpEndStart(const BufferCircular *bufc) {
    return bufc->pos_start > bufc->pos_end;
}

unsigned int BufferCircular_size(const BufferCircular *bufc) {
    return bufc->size;
}

unsigned int BufferCircular_available(const BufferCircular *bufc) {
    if(BufferCircular_intern_jumpEndStart(bufc))
        return (BufferCircular_size(bufc) - bufc->pos_start) + bufc->pos_end;
    else
        return bufc->pos_end - bufc->pos_start;
}

bool BufferCircular_isEmpty(const BufferCircular *bufc) {
    return bufc->pos_end == bufc->pos_start;
}

/*inline*/ bool BufferCircular_isFull(const BufferCircular *bufc) {
    return BufferCircular_available(bufc) <= 0;
}

/**
 * factorisation code d'insertion dans le buffer
 */
inline void BufferCircular_intern_put(BufferCircular *bufc, const bufType byte) {
    if(bufc->pos_end >= bufc->size) //si curseur arrivé à fin
        bufc->pos_end = 0;
    bufc->buf[bufc->pos_end] = byte;
}

bool BufferCircular_put(BufferCircular *bufc, const bufType byte) {
    if(BufferCircular_isFull(bufc)) { //si buffer plein, alors on ne peut pas ajouter
        //errno = EDQUOT; // Disk quota exceeded (POSIX.1)
        errno = ENOBUFS; // No buffer space available (POSIX.1 (XSI STREAMS option))
        return false;
    } else {
        BufferCircular_intern_put(bufc, byte);
        return true;
    }
}

/**
 * factorisation code de récupération dans le buffer
 */
inline bufType BufferCircular_intern_get(BufferCircular *bufc) {
    bufType tmp = bufc->buf[bufc->pos_start];
    if(bufc->pos_start == bufc->size)
        bufc->pos_start = 0;
    else
        bufc->pos_start++;
    return tmp;
}

bufType BufferCircular_get(BufferCircular *bufc) {
    if(BufferCircular_isEmpty(bufc)) {
        errno = ENODATA; // No message is available on the STREAM head read queue (POSIX.1)
        return 0;
    } else {
        return BufferCircular_intern_get(bufc);
    }
}

unsigned int BufferCircular_puts(BufferCircular *bufc, const bufType bytes[], const unsigned int size) {
    if((size <= 0) || (bufc == NULL) || (bytes == NULL)) {
        errno = EINVAL; // Invalid argument (POSIX.1)
        return 0;
    } else {
        unsigned int rest_buf = BufferCircular_size(bufc) - BufferCircular_available(bufc);
        unsigned int rest_tabl = size;
        unsigned int copied = 0;
        while((rest_buf > 0) && (rest_tabl > 0)) {
            BufferCircular_intern_put(bufc, bytes[copied]);
            rest_buf--;
            rest_tabl--;
            copied++;
        }
        return copied;
    }
}

unsigned int BufferCircular_gets(BufferCircular *bufc, bufType bytes[], const unsigned int size) {
    if((size <= 0) || (bufc == NULL) || (bytes == NULL)) {
        errno = EINVAL; // Invalid argument (POSIX.1)
        return 0;
    } else {
        unsigned int rest_buf = BufferCircular_available(bufc);
        unsigned int rest_tabl = size;
        unsigned int copied = 0;
        while((rest_buf > 0) && (rest_tabl > 0)) {
            bytes[copied] = BufferCircular_intern_get(bufc);
            rest_buf--;
            rest_tabl--;
            copied++;
        }
        return copied;
    }
}
