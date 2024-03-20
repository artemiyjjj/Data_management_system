#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <stdio.h>
#include "controller/queries/queries.h"
#include "storage/blocks/block_manager.h"
#include "storage/storage_manager_pub.h"
#include "utils/status_codes.h"

#include "storage/structure/document_tree/document_tree.h"

// TREE_DECLARE(DT_node)

enum storage_init_status init_storage(const char filename[], const struct block_manager_config bl_manager_config, struct storage_manager* const storage_manager);

enum storage_close_status close_storage(struct storage_manager* const storage_manager);

void select_value(struct select_query* const query);

void insert_value(struct insert_query* const query);

void update_value(struct update_query* const query);

void delete_value(struct delete_query* const query);

#endif //STORAGE_MANAGER_H
