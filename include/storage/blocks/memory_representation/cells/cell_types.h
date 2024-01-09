#ifndef CELL_TYPES_MEM_H
#define CELL_TYPES_MEM_H

#include <stdbool.h>
#include "common/data_types.h"

/* Cell for storing in memory value of key-value pair of document tree.

 In case _changed_ is set, handler of disk cell should
 check both name and value and override them.
*/
typedef struct CL_value_mem {
    bool changed;
    enum cell_signature sign;
    char* name;
    struct CL_value_mem *name_cell;
    unsigned int value_size;
    struct data data;
} CL_value_mem;

typedef struct CL_key_mem {
    bool changed;
    enum cell_signature sign;
    char* key_name;
    struct CL_value_mem *name_cell;
    struct CL_value_mem *parent_cell;
    struct CL_index_mem *child_list;
    struct {
        unsigned int subkeys_amount;
    } state;
} CL_key_mem;


/*

 Changes state is set then child value nodes are being changed.
 For saving changed child value, check _changed_ flag at children's state.
 */
typedef struct CL_big_value_mem {
    bool changed;
    enum cell_signature sign;
    char* name;
    struct Cl_value_mem * name_cell;
    struct CL_index_mem * list_of_parts;
    unsigned int big_value_size;
} CL_big_value_mem;

typedef struct CL_index_mem {
    bool changed;
    enum cell_signature sign;
    union {
        struct CL_key_mem;
        struct Cl_value_mem;
    } indexing_cell;
    struct CL_index_mem * next_index_cell;
} CL_index_mem;

/* Cell for storing info about each block.

 Used in blocks of type _block_head_.
*/
typedef struct CL_sys_block_head_info_mem {
    enum cell_signature sign;
    block_index bl_index;
    enum block_signature bl_sign;
    unsigned int avaliable_space;
} CL_sys_block_head_info_mem;


typedef struct CL_sys_block_avaliable_mem {
    enum cell_signature sign;
    // todo системные клетки и блоки
} CL_sys_block_avaliable_mem;

#endif