#ifndef BLOCK_UTILS_H
#define BLOCK_UTILS_H

#include <stdint.h>

typedef unsigned int block_index;
typedef unsigned int block_offset;
typedef unsigned int block_capasity;

/* Signatures that defines types of blocks.
    - Type block contains available data types for the application.
    - Data block contains cells, which are responsible for storing application data of particular type.
    - Head block contains positions of the data-blocks, which are containing start of a new document tree.
*/
typedef enum {
    Bl_sign_head = 0,
    Bl_sign_data,
    Bl_sign_meta,
    Bl_sign_names,
} block_signature;

#endif //BLOCK_UTILS_H
