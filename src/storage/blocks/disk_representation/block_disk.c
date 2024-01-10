#include "storage/blocks/disk_representation/block_disk.h"
#include "storage/blocks/memory_representation/block_memory.h"

#include "storage/file/file_interaction.h"

static void set_common_attributes(void* const block, const enum block_signature bl_sign, const block_index bl_index) {
	struct block_common* bl = block;
	bl -> sign = bl_sign;
	bl -> bl_index = bl_index;
}

/* Performs transformation of memory cells of given block in memory form to correspondinf cells of disk form.

 Saves transformed cells to the given address, which should be _block_content_ attribute of block in disk form.
 */
static enum block_parsing_statuses parse_cells_mem_to_disk(const struct block_mem_type_ref* const block_mem_type_ref, void* const block_contents_ptr) {
	int contents_size;
	int bl_contetns_iterator = 0;
	const enum block_signature bl_sign = block_mem_type_ref -> sign;
	switch (bl_sign) {
		case BL_SIGN_HEAD:
			contents_size = block_size - sizeof(struct block_head);
			struct linked_list_CL_sys_block_head_info_mem* linked_list = block_mem_type_ref -> block_mem_ptr.block_head_ptr -> list_cells;

			break;
		case BL_SIGN_META:

			break;
		case BL_SIGN_NAMES:

			break;
		case BL_SIGN_DATA_FC:

			break;
		case BL_SIGN_DATA_VC:

			break;
		default:
			return BLOCK_PARSING_FAILED;
	}
	return BLOCK_PARSING_SUCCEED;
}


enum block_parsing_statuses parse_block_mem_to_disk(const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr) {
	if (NULL == block_mem_type_ref || NULL == block_mem_type_ref -> block_mem_ptr.block_head_ptr) {
		return BLOCK_PARSING_FAILED;
	}
	const enum block_signature bl_sign = block_mem_type_ref -> sign;
	set_common_attributes(
		block_disk_ptr -> block_head_ptr,
		bl_sign,
		block_mem_type_ref -> block_mem_ptr.block_head_ptr -> bl_index);

	switch (bl_sign) {
		case BL_SIGN_HEAD:
			struct block_head* bl_d = block_disk_ptr -> block_head_ptr;
			const struct block_head_mem* bl_m = block_mem_type_ref -> block_mem_ptr.block_head_ptr;
			bl_d -> cell_length = get_disk_cell_size(CL_SIGN_SYS_HEAD_INFO);
			bl_d -> root_data_cell = bl_m -> root_data_cell;
			bl_d -> state.blocks_amount = bl_m -> state.blocks_amount;
			bl_d -> state.next_head_block = bl_m -> state.next_head_block;
			bl_d -> state.occupied_cells_amount = bl_m -> state.occupied_cells_amount;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_d -> block_contents);
			break;
		case BL_SIGN_META:

			break;
		case BL_SIGN_NAMES:

			break;
		case BL_SIGN_DATA_FC:

			break;
		case BL_SIGN_DATA_VC:

			break;
		default:
			return BLOCK_PARSING_FAILED;
	}
	return BLOCK_PARSING_SUCCEED;
}

/* Creates new block from existing memory block and adds it to the end of storage file.

 Allocates _block_size_ memory for a newly creating block, parses given block in memory form
 and stores new block at the end of file (at file offset, referring to position, given in memory form block).

 */
enum truncate_codes create_block_disk(const int fd, const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr) {
	const int file_offset = convert_block_index_to_file_offset(block_mem_type_ref -> block_mem_ptr.block_head_ptr->bl_index);
	if (NULL == block_mem_type_ref || NULL == block_mem_type_ref -> block_mem_ptr.block_head_ptr) {
		return TRUNCATE_FAILED;
	}
	block_disk_ptr -> block_head_ptr = malloc(block_size);
	if (NULL == block_disk_ptr -> block_head_ptr) {
		return TRUNCATE_FAILED;
	}
	if (parse_block_mem_to_disk(block_mem_type_ref, block_disk_ptr) == BLOCK_PARSING_SUCCEED) {
		return write_new_block_to_file(fd, file_offset, block_disk_ptr->block_head_ptr);
	} else {
		return TRUNCATE_FAILED;
	}
}

void update_block_disk(const int fd, const struct block_mem_type_ref* const block_mem_type_ref, union block_disk_ptr* const block_disk_ptr) {

}
