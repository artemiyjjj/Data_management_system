#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include <stdio.h>

#include "file_representation/block_file.h"
#include "storage/blocks/block_manager_pub.h"
#include "storage/blocks/utils.h"
#include "utils/status_codes.h"


enum block_manager_creation_mode {
	BM_CREATE_MODE_NEW = 0,
	BM_CREATE_MODE_EXISTING
};

enum block_init_status init_block_manager(const struct block_manager_config bl_manager_config, const enum block_manager_creation_mode, struct block_manager* const block_manager);

void delete_block_manager_struct(const struct block_manager* block_manager);

void select_cell(char* cell_name); //todo selections, queries and so

enum block_manager_blocks_creation_status create_block(struct block_manager* const block_manager, const enum block_signature bl_signature);

/* Performs update of block in memory and file form and then sync it with file. */
enum block_manager_blocks_update_status update_block(struct block_manager* const block_manager, const block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data);

enum block_manager_blocks_deletion_status delete_block(struct block_manager* const block_manager, const block_index bl_index);

#endif //BLOCK_MANAGER_H
