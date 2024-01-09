#include "storage/blocks/memory_representation/block_types_mem.h"

/* Creates a block of a given type in memory.

 Returns a pointer to the start of a created block.
 */
void* create_block_mem(enum block_signature bl_sign) {
   void* new_block_ptr = malloc()
   return ;
}

/* Searches a cell with a certain name.

 Returns pointer to a cell with a given name
 */
void* select_cell_mem(void* block, char* cell_name) {

}

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(void* block, enum block_update_mode update_mode, char* cell_name, struct data cell_data) {

}


/* Deletes block of data in memory. */
void delete_block_mem(block_index bl_index) {

}
