#ifndef CELL_TYPES_MEM_H
#define CELL_TYPES_MEM_H

#include <stdbool.h>

/* Cell for storing in memory value of key-value pair of document tree.

 In case _changed_ is set, handler of disk cell should
 check both name and value and override them.
*/
struct CL_value_mem {
    bool changed;
    enum data_type value_type;
    unsigned int value_size;
    union {
        int int_value;
        double double_value;
        char* string_ptr;
        bool bool_value;
    } value;
};

struct CL_key_mem {
    bool changed;
    char* key_name;
    struct CL_value_mem *name_cell;
    struct CL_value_mem *parent_cell;
    struct CL_index_mem *child_list;
    struct {
        unsigned int subkeys_amount;
    } state;
};



struct CL_big_value_mem {
    char* name;
    struct Cl_value_mem * name_cell;
    struct CL_index_mem * list_of_parts;
    unsigned int big_value_size;
};

struct CL_index_mem {
    bool changed;
    cell_signature signature;
    union {
        struct CL_key_mem;
        struct Cl_value_mem;
    } indexing_cell;
    struct CL_index_mem * next_index_cell;
};

/* Cell for storing info about each block.

 Used in blocks of type _block_head_.
*/
struct CL_sys_block_head_info_mem {
    block_index bl_index;
    block_signature bl_sign;
    unsigned int avaliable_space;
};


struct CL_sys_block_avaliable_mem {
    // todo системные клетки и блоки
};

#endif