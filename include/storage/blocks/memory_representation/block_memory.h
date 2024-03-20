#ifndef BLOCK_MEMORY_H
#define BLOCK_MEMORY_H

#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/utils.h"
#include "storage/cells/utils.h"
#include "utils/status_codes.h"


enum alloc_code create_block_mem(const block_index bl_index, struct block_mem_sign_ref* const block_ref);

/* Function for searching a cell with a certain name.

 Returns pointer to a cell with a given name
 */
struct cell_mem_sign_ref select_cell_mem(struct block_mem_sign_ref* const block_sign_ref, enum cell_select_mode select_mode, struct cell_index cell_index, struct data data);

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(struct block_mem_sign_ref* const block_ref, enum block_update_mode update_mode, struct cell_index cell_index, struct data cell_data);


/* Function for deleting block of data in memory. */
void delete_block_mem(const struct block_mem_sign_ref block_ref);


#endif //BLOCK_MEMORY_H
