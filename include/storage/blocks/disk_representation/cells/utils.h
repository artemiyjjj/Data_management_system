#ifndef CELL_UTILS_H
#define CELL_UTILS_H

#include "storage/blocks/utils.h"

/* Cell position identifier in blocks of cells.

 Shows cell position containing index of the block and offset from a beggining of the block.
*/
struct cell_index {
    block_index bl_index;
    block_offset bl_offset;
};

struct cell_index create_cell_index(const block_index bl_index, const block_offset bl_offset);

void change_block_index(struct cell_index* cell, const  block_index block_index);

void change_block_offset(struct cell_index* cell, const block_offset bl_offset);

/*
Signatures of cell-structure types for cells storing different data-types
in the context of programm logic.
*/
enum cell_signature {
    Cl_sign_key = 0,
    Cl_sign_value,
    Cl_sign_big_value,
    Cl_sign_index_key,
    Cl_sign_index_value,
    Cl_sign_sys_head_info,
    Cl_sign_sys_block_avaliable,
};

#endif
