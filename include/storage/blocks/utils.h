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
enum block_signature {
    BL_SIGN_HEAD = 0,
    BL_SIGN_DATA,
    BL_SIGN_META,
    BL_SIGN_NAMES,
} ;

enum block_update_mode {
    BL_UPD_ADD = 0,
    BL_UPD_REMOVE,
};

enum cell_select_mode {
    CL_SELECT_BY_NAME = 0,
    CL_SELECT_BY_VALUE
};

#endif //BLOCK_UTILS_H
