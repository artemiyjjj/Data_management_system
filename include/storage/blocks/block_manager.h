#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include "storage/blocks/utils.h"
#include "storage/blocks/disk_representation/block_disk.h"
#include "storage/blocks/memory_representation/block_memory.h"

void select_cell(char* cell_name);

void create_block(enum block_signature bl_signature);

/* Performs update of block in memory and disk form and then sync it with file. */
void update_block(block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data);

void delete_block(block_index bl_index);


#endif //BLOCK_MANAGER_H
