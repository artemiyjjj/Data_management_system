#ifndef BLOCK_UTILS_H
#define BLOCK_UTILS_H

#include <stdint.h>

typedef unsigned int block_index;
typedef unsigned int block_offset;
typedef unsigned int block_capasity;

unsigned int convert_block_index_to_file_offset(const block_index bl_index);

/* Signatures that defines types of blocks.
    - Type block contains available data types for the application.
    - Data block contains cells, which are responsible for storing application data of particular type.
    - Head block contains positions of the data-blocks, which are containing start of a new document tree.
*/
enum block_signature {
    BL_SIGN_HEAD = 0,
    BL_SIGN_DATA_FC,
    BL_SIGN_DATA_VC,
    BL_SIGN_NAMES,
    BL_SIGN_META,
} ;

enum block_update_mode {
    BL_UPD_ADD = 0,
    BL_UPD_REMOVE,
};

enum cell_select_mode {
    CL_SELECT_BY_NAME = 0,
    CL_SELECT_BY_VALUE
};

enum block_operations_statuses {
    BL_CREATED_SUCCEED = 0,
    BL_CREATED_FAILURE,
};

struct block_mem_type_ref {
    enum block_signature sign;
    union block_mem_ptr {
        struct block_head_mem* block_head_ptr;
        struct block_data_fixed_cells_mem* block_data_fc_ptr;
        struct block_data_variable_cells_mem* block_data_vc_ptr;
        struct block_names_mem* block_names_ptr;
        struct block_meta_mem* block_meta_ptr;
    } block_mem_ptr;
};

struct block_disk_type_ref {
    enum block_signature sigm;
    union block_disk_ptr {
        struct block_head* block_head_ptr;
        struct block_data_fixed_cells* block_data_fc_ptr;
        struct block_data_variable_cells* block_data_vc_ptr;
        struct block_names* block_names_ptr;
        struct block_meta* block_meta_ptr;
    } block_disk_ptr;
};

#endif //BLOCK_UTILS_H
