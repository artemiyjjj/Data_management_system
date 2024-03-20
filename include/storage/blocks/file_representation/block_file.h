#ifndef BLOCK_H
#define BLOCK_H

#include <string.h>

#include "storage/blocks/block_common.h"
#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/file_representation/block_types_file.h"
#include "storage/file/file_interaction.h"
#include "storage/blocks/utils.h"
#include "storage/blocks/block_manager_pub.h"
#include "utils/status_codes.h"


enum truncate_code create_block_file(const struct storage_info storage_info, const block_index new_block_index);

enum mmap_code read_block_file(const struct storage_info storage_info, block_index bl_index, union block_file_ptr* dest_block_mapping);

enum msync_code update_block_file(const struct storage_info storage_info, const struct block_mem_sign_ref* const src_block, union block_file_ptr* const dest_block_maped);

enum truncate_code delete_block_file(const struct storage_info storage_info, block_index bl_index);

#endif //BLOCK_H
