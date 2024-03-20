#ifndef BLOCK_COMMON_H
#define BLOCK_COMMON_H

#include "storage/blocks/file_representation/block_types_file.h"
#include "storage/blocks/file_representation/block_file.h"
#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/memory_representation/block_memory.h"
#include "storage/cells/cell_common.h"

enum block_parsing_status parse_block_file_to_mem(const struct block_file_sign_ref* const src_block, union block_mem_ptr* const dest_block);

enum block_parsing_status parse_block_mem_to_file(const unsigned int block_size, const struct block_mem_sign_ref* const src_block, union block_file_ptr* const dest_block);

#endif //BLOCK_COMMON_H
