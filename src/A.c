#include <stdio.h>
#include <assert.h>

#include "storage/storage_manager.h"


#define MAX_LOADED_BLOCKS_AMOUNT 5

#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char *argv[]) {

	struct storage_manager storage_manager;
	struct block_manager_config bl_manager_config = {
		.storage_info = &storage_manager.storage_info,
		.max_loaded_blocks_amount = MAX_LOADED_BLOCKS_AMOUNT,
		.avaliable_block_index = 0
	};

	enum storage_init_status storage_init_status = init_storage(argv[1], bl_manager_config, &storage_manager);
	if (STORAGE_INIT_FAILED == storage_init_status) {
		return 1;
	}

	close_storage(&storage_manager);
	// while (1) {
	// 	//do
	// 	break;
	// }

	return 0;
}