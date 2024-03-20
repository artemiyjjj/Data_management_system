#ifndef BLOCK_MANAGER_PUB_H
#define BLOCK_MANAGER_PUB_H


#include "common/data_structures/linked_list.h"
#include "storage/blocks/utils.h"
#include "storage/utils.h"

/* Data structure with options, needed to init block_manager.
 *
 * Making in const-value is forbidden.
 * _avaliable_block_index_ could be any value because it should init inside init_block_manager(...).
 *
 * storage_info - fd and block_size of opened storage.
 * max_loaded_blocks_amount - amount of mmaped blocks of each type at the same time.
 * avaliable_block_index - index of next creating block for block_manager (comes from block_head if it's initialized).
 */
struct block_manager_config {
	struct storage_info* storage_info;
	const unsigned int max_loaded_blocks_amount;
	const block_index* const avaliable_block_index;
};

enum block_manager_update_mode {
	BLOCK_MANAGER_UPDATE_INSERT = 0,
	BLOCK_MANAGER_UPDATE_DELETE
};


struct block_mem_ptr_list {
	unsigned int load_block_amount;
	struct block_mem_sign_ref** block_ref_array;
};

struct block_file_ptr_list {
	unsigned int load_block_amount;
	struct block_file_sign_ref** block_ref_array;
};

/*
 *
 * If file block is loaded, address will be valid, otherwise - NULL.
 * Stores addresses of loaded blocks in an array of size _max_loaded_blocks_amount_.
 *
 */
typedef struct block_manager {
	block_index new_avaliable_block_index;
	struct storage_info storage_info;
	unsigned int max_loaded_blocks_amount;
	struct block_mem_ptr_list block_mem_pointers;
	struct block_file_ptr_list block_file_pointers;
	// todo вопрос 4
} block_manager;

LINKED_LIST_DECLARE(block_manager)

enum alloc_code init_block_manager_struct(const struct block_manager_config bl_manager_config, struct block_manager* const block_manager);

void delete_block_manager_struct(const struct block_manager* block_manager);


#endif //BLOCK_MANAGER_PUB_H
