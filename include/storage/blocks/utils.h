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
    Bl_sign_head = 0,
    Bl_sign_data,
    Bl_sign_meta,
    Bl_sign_names,
} ;

enum block_update_mode {
    Bl_upd_add,
    Bl_upd_remove,
};

enum cell_select_mode {
    Cl_
};

#endif //BLOCK_UTILS_H
