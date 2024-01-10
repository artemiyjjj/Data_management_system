#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <stdio.h>
#include "controller/queries/queries.h"
#include "storage/blocks/block_manager.h"
#include "storage/file/file_interaction.h"
#include "utils/status_codes.h"

#include "storage/structure/document_tree/document_tree.h"

// TREE_DECLARE(DT_node)

enum storage_statuses init_storage(const char filename[], const unsigned int param_block_size);


void select_value(struct select_query* const query);

void insert_value(struct insert_query* const query);

void update_value(struct update_query* const query);

void delete_value(struct delete_query* const query);

#endif //STORAGE_MANAGER_H
