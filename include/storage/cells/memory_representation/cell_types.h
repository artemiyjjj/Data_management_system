#ifndef CELL_TYPES_MEM_H
#define CELL_TYPES_MEM_H

#include <stdbool.h>

#include "common/data_types.h"
#include "storage/blocks/utils.h"

/* Cell for storing in memory value of key-value pair of document tree.

 In case _changed_ is set, handler of disk cell should
 check both name and value and override them.
*/
typedef struct Cl_value_mem {
    bool changed;
    struct cell_index cell_index;
    enum cell_signature sign;
    unsigned int value_size;
    struct data data;
} Cl_value_mem;

typedef struct Cl_key_mem {
    bool changed;
    struct cell_index cell_index;
    enum cell_signature sign;
    char* key_name;
    struct Cl_value_mem *name_cell;
    struct Cl_key_mem *parent_cell;
    struct Cl_index_mem *child_list;
    struct {
        unsigned int subkeys_amount;
    } state;
} Cl_key_mem;


/* Cell for storing large variables.

 Changes state is set then child value nodes are being changed.
 For saving changed child value, check _changed_ flag at children's state.
 */
typedef struct Cl_big_value_mem {
    bool changed;
    struct cell_index cell_index;
    enum cell_signature sign;
    char* name;
    struct Cl_value_mem *name_cell;
    struct Cl_index_mem *list_of_parts;
    unsigned int big_value_size;
} Cl_big_value_mem;

typedef struct Cl_index_mem {
    bool changed;
    struct cell_index cell_index;
    enum cell_signature sign;
    union {
        Cl_key_mem* key_cell;
        Cl_value_mem* value_cell;
    } indexing_cell;
    struct Cl_index_mem *next_index_cell;
} Cl_index_mem;

/* Cell for storing info about each block.

 Used in blocks of type _block_head_.
*/
typedef struct Cl_sys_block_head_info_mem {
    enum cell_signature sign;
    struct cell_index cell_index;
    block_index bl_index;
    enum block_signature bl_sign;
    unsigned int avaliable_space;
} Cl_sys_block_head_info_mem;

// do not use
typedef struct Cl_sys_block_avaliable_mem {
    enum cell_signature sign;
    struct cell_index cell_index;
    // todo системные клетки и блоки
} Cl_sys_block_avaliable_mem;

/* Common structure for cell initialization. */
struct cell_mem_sign_ref {
    enum cell_signature sign;
    union cell_mem_ptr {
        struct Cl_key_mem* cell_key;
        struct Cl_value_mem* cell_value;
        struct Cl_big_value_mem* cell_big_value;
        struct Cl_index_mem* cell_index;
        struct Cl_sys_block_head_info_mem* cell_head_info;
        struct Cl_sys_block_avaliable_mem* cell_avaliable;
    } cell_mem_ptr;
};


int get_mem_cell_size(const struct cell_mem_sign_ref* const cell_ref);

#endif