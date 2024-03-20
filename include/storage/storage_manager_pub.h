#ifndef STORAGE_MANAGER_PUB_H
#define STORAGE_MANAGER_PUB_H

#include "common/data_structures/linked_list.h"
#include "blocks/block_manager_pub.h"
#include "storage/utils.h"

struct storage_manager {
	struct storage_info storage_info;
	struct linked_list_block_manager* list_block_manager; //todo вопрос 4
};

#endif //STORAGE_MANAGER_PUB_H
