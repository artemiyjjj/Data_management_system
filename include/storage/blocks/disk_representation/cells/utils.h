#ifndef CELL_UTILS_H
#define CELL_UTILS_H

#include "storage/blocks/utils.h"

/* Cell position identifier in blocks of cells.

 Shows cell position relative to a beggining of the block, where cell is placed in.
*/
struct cell_index {
    block_index bl_index;
    block_offset bl_offset;
};

struct cell_index* create_cell_index(block_index, block_offset);

void change_block_index(struct cell_index*, block_index);

void change_block_offset(struct cell_index*, block_offset);

/*
Signatures of cell-structure types for cells storing different data-types
in the context of programm logic.
*/
typedef enum {
    Cl_sign_key_node = 0,
    Cl_sign_value,
    Cl_sign_big_value,
    Cl_sign_key_index,
    Cl_sign_value_index,
    Cl_sys_sign_block_avaliable,

} cell_signature;


#endif
