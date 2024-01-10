#ifndef BLOCK_H
#define BLOCK_H

#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/disk_representation/block_types_disk.h"
#include "storage/blocks/utils.h"
#include "storage/cells/disk_representation/cell_types.h"
#include "utils/status_codes.h"


extern unsigned int block_size;

enum block_parsing_statuses parse_block_mem_to_disk(const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr);

enum truncate_codes create_block_disk(const int fd, const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr);

void update_block_disk(const int fd, const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr);

#endif //BLOCK_H
