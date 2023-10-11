#include <stdint.h>
#include "include/file/internals/blocks/blocks.h"

/* Cell position identifier in blocks of cells. Shows cell position relative to a beggining of the block, where cell is placed in. 
*/
 struct cell_index{
    block_index bl_index;
    block_offset bl_offset;
};

cell_index create_cell_index(block_index, block_offset);

cell_index* change_block_index(cell_index*, block_index);

cell_index* change_block_offset(cell_index*, block_offset);

/* Defenition of a cell-structure type. For cells which can have different purposes.
*/
enum cell_signature {
    Cl_sign_node = 0,
    Cl_sign_value,
    Cl_sign_big_value,
    Cl_sign_key_index,
    Cl_sign_value_index,
    Cl_sign_value_data
};