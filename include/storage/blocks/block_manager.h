#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include "storage/blocks/utils.h"
#include "storage/blocks/disk_representation/block_disk.h"

struct block_mem_ptr_array {
	unsigned int mem_block_load_amount;
	struct block_mem_type_ref block_mem_sign_and_pointers[];
};

struct block_disk_ptr_array {
	unsigned int disk_block_load_amount;
	struct block_disk_type_ref block_disk_sign_and_pointers[];
};

/*

 If disk block is loaded, address will be valid, otherwise - NULL.
 */
struct block_manager {
    block_index new_avaliable_block_index;

    struct block_mem_ptr_array* block_mem_pointers;
    struct block_disk_ptr_array* block_disk_pointers;
};

void init_block_manager(int storage_fd);

void select_cell(char* cell_name);

void create_block(enum block_signature bl_signature);

/* Performs update of block in memory and disk form and then sync it with file. */
void update_block(const block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data);

void delete_block(const block_index bl_index);


#endif //BLOCK_MANAGER_H
