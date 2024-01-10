#ifndef CELL_UTILS_H
#define CELL_UTILS_H

#include "storage/blocks/utils.h"

/*
Signatures of cell-structure types for cells storing different data-types
in the context of programm logic.
*/
enum cell_signature {
	CL_SIGN_KEY = 0,
	CL_SIGN_VALUE,
	CL_SIGN_BIG_VALUE,
	CL_SIGN_INDEX_KEY,
	CL_SIGN_INDEX_VALUE,
	CL_SIGN_SYS_HEAD_INFO,
	CL_SIGN_SYS_BLOCK_AVALIABLE,
};

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


#endif
