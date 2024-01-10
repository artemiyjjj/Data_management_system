#ifndef BLOCK_MEMORY_H
#define BLOCK_MEMORY_H

#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/utils.h"
#include "storage/cells/utils.h"
#include "utils/status_codes.h"

enum alloc_codes create_block_mem(struct block_mem_type_ref* const block_type_ref, const block_index bl_index);

/* Function for searching a cell with a certain name.

 Returns pointer to a cell with a given name
 */
void* select_cell_mem(struct block_mem_type_ref* const block_type_ref, enum cell_select_mode select_mode, char* cell_name);

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(struct block_mem_type_ref* const block_type_ref, enum block_update_mode update_mode, char* cell_name, struct data cell_data);


/* Function for deleting block of data in memory. */
void delete_block_mem(const struct block_mem_type_ref block_type_ref);



#endif //BLOCK_MEMORY_H
