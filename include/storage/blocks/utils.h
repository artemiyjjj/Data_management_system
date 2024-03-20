#ifndef BLOCK_UTILS_H
#define BLOCK_UTILS_H

#include <stdint.h>


typedef unsigned int block_index;
typedef unsigned int block_offset;
typedef unsigned int block_capasity;

unsigned int compute_file_offset_from_block_index(const unsigned int block_size, const block_index bl_index);

/* Signatures that defines types of blocks.
    - Name block contains names of key and value cells.
    - Data block contains cells, which are responsible for storing application data of particular type.
    - Head block contains positions of the data-blocks, which are containing start of a new document tree.
*/
enum block_signature {
    BL_SIGN_HEAD = 0,
    BL_SIGN_DATA_FC,
    BL_SIGN_DATA_VC,
    BL_SIGN_NAMES,
    BL_SIGN_META,
};

enum block_update_mode {
    BL_UPD_ADD = 0,
    BL_UPD_REMOVE,
    BL_UPD_UPDATE
};

enum cell_select_mode {
    CL_SELECT_BY_NAME = 0,
    CL_SELECT_BY_VALUE
};

enum block_operations_statuses {
    BL_CREATED_SUCCEED = 0,
    BL_CREATED_FAILURE,
};

#endif //BLOCK_UTILS_H
