#include <assert.h>

#include "storage/blocks/file_representation/block_file.h"


/* Creates new block in the end of file storage.

 Stores new empty space for a block at the end of file of size
 _block_size_ at file offset, computed from avaliable block position.
 */
enum truncate_code create_block_file(const struct storage_info storage_info, const block_index new_block_index) {
	const int file_offset = compute_file_offset_from_block_index(storage_info.block_size, new_block_index);
	// if (parse_block_mem_to_file(src_block, dest_block, storage_info.block_size) == BLOCK_PARSING_SUCCEED) {
	return create_empty_block(storage_info, file_offset);
}

/* Reads a block from given storage_info's fd.

 Stores mmaped region start address at dest_block_mapping argument.
 */
enum mmap_code read_block_file(const struct storage_info storage_info, block_index bl_index, union block_file_ptr* dest_block_mapping) {
	int file_offset = compute_file_offset_from_block_index(storage_info.block_size, bl_index);
	return load_block(storage_info, file_offset, (void*) &dest_block_mapping -> block_head_ptr);
}

/* Update mmaped block contents with given memory block contents and sync it with the file.

 Determines the difference between the memory and file versions of blocks and syncronizes them.
 */
enum msync_code update_block_file(const struct storage_info storage_info, const struct block_mem_sign_ref* const mem_src_block, union block_file_ptr* const dest_block_maped) {
	enum block_parsing_status parse_status = parse_block_mem_to_file(storage_info.block_size, mem_src_block, dest_block_maped);
	if (parse_status == BLOCK_PARSING_FAILED) {
		return sync_block(storage_info, dest_block_maped);
	}
	return MSYNC_FAILED;
}

enum truncate_code delete_block_file(const struct storage_info storage_info, block_index bl_index) {
	return TRUNCATE_FAILED;
}
