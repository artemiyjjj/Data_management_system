#ifndef BLOCK_MEMORY_H
#define BLOCK_MEMORY_H

#include "storage/blocks/utils.h"


void* create_block_mem(enum block_signature bl_sign);

/* Function for searching a cell with a certain name.

 Returns pointer to a cell with a given name
 */
void* select_cell_mem(void* block, char* cell_name);

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(void* block, enum block_update_mode update_mode, char* cell_name, struct data cell_data);


/* Function for deleting block of data in memory. */
void delete_block_mem(block_index bl_index);



#endif //BLOCK_MEMORY_H
