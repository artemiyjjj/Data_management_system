#ifndef CELL_UTILS_H
#define CELL_UTILS_H

#include <stdint.h>
#include "storage/blocks/utils.h"

/* Cell position identifier in blocks of cells. Shows cell position relative to a beggining of the block, where cell is placed in. 
*/
typedef struct {
    block_index bl_index;
    block_offset bl_offset;
} cell_index;

cell_index create_cell_index(block_index, block_offset);

cell_index* change_block_index(cell_index*, block_index);

cell_index* change_block_offset(cell_index*, block_offset);

/*
 * Defenition of a cell-structure type for cells storing different data-types.
*/
typedef enum {
    Cl_sign_node = 0,
    Cl_sign_value,
    Cl_sign_big_value,
    Cl_sign_key_index,
    Cl_sign_value_index,
    Cl_sign_value_data
} cell_signature;

#endif
