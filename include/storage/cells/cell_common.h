#ifndef CELL_COMMON_H
#define CELL_COMMON_H

#include <malloc.h>

#include "storage/blocks/file_representation/block_file.h"
#include "storage/blocks/memory_representation/block_memory.h"
#include "storage/cells/file_representation/cell_types.h"
#include "storage/cells/memory_representation/cell_types.h"
#include "storage/cells/utils.h"

#include "utils/status_codes.h"

enum cell_parsing_status parse_cell_mem_to_file(const struct cell_mem_sign_ref* const src_cell, union cell_file_ptr* const dest_cell);

enum block_parsing_status parse_cells_mem_to_file(const struct block_mem_sign_ref* const src_block, union cell_file_ptr* const dest_cell, const unsigned int block_size);


enum cell_parsing_status parse_cell_file_to_mem(const struct cell_file_sign_ref* const src_cell, union cell_mem_ptr const dest_cell);

enum block_parsing_status parse_cells_file_to_mem(const struct block_file_sign_ref* const src_cell, union cell_mem_ptr* const dest_cell);


int get_file_cell_size_from_mem_cell(const struct cell_mem_sign_ref* const cell_ref);

int get_mem_cell_size_from_file_cell(const struct cell_file_sign_ref* const cell_ref);

#endif //CELL_COMMON_H
