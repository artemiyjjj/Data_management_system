#include "storage/blocks/disk_representation/block_disk.h"

#include <assert.h>

static void set_common_attributes(void* const block, const enum block_signature bl_sign,
								const block_index bl_index) {
	struct block_common* bl = block;
	bl -> sign = bl_sign;
	bl -> bl_index = bl_index;
}

/* Transforms mem cell to disk cell and returns it's address by argument _cell_disk_ptr_.
		можно вынести в отдельный файл
 Addres _cell_disk_addr_ in some scenarios might be memory contents area.
 Returns
 - size of resulted disk cell in bytes as returning value.
 - newly created disk cell address as second parameter.

 When disk cell becomes unneeded, free(*cell addr*) should be performed on returned address.
 */
enum cell_parsing_statuses parse_cell_mem_to_disk(const struct cell_mem_type_ref* const cell_mem_type_ref, const void* cell_disk_ptr) {
	switch (cell_mem_type_ref -> sign) {
		case CL_SIGN_KEY: {
			struct Cl_key* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_key_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_key;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> key_name_cell =  cell_mem -> name_cell -> cell_index;
			cell_disk -> parent_cell = cell_mem -> parent_cell -> cell_index;
			cell_disk -> key_name_cell = cell_mem -> child_list -> cell_index;
			cell_disk -> state.subkeys_amount = cell_mem -> state.subkeys_amount;
			cell_disk_ptr = cell_disk;
		}
		break;
		case CL_SIGN_VALUE: {
			const struct Cl_value_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_value;
			struct Cl_value* cell_disk = malloc(sizeof(*cell_disk) + cell_mem -> value_size);
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> value_type = cell_mem -> data.type;
			cell_disk -> value_size = cell_mem -> value_size;
			memcpy(&(cell_disk -> value), &(cell_mem -> data), cell_mem -> value_size);
			cell_disk_ptr = cell_disk;
		}
		break;
		case CL_SIGN_BIG_VALUE: {
			struct Cl_big_value* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_big_value_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_big_value;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> value_name =  cell_mem -> name_cell -> cell_index;
			cell_disk -> index_cell_of_parts = cell_mem -> list_of_parts -> cell_index;
			cell_disk -> big_value_size = cell_mem -> big_value_size;
			cell_disk_ptr = cell_disk;
		}
		break;
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE: {
			struct Cl_index* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_index_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_index;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> key_subkey_or_value_cell = cell_mem -> indexing_cell.key_cell -> cell_index;
			cell_disk -> next_cell = cell_mem -> next_index_cell -> cell_index;
			cell_disk_ptr = cell_disk;
		}
		break;
		case CL_SIGN_SYS_HEAD_INFO: {
			struct Cl_sys_block_head_info* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_sys_block_head_info_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_head_info;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> bl_index = cell_mem -> bl_index;
			cell_disk -> bl_sign = cell_mem -> bl_sign;
			cell_disk -> bl_avaliable_space = cell_mem -> avaliable_space;
			cell_disk_ptr = cell_disk;
		}
		break;
		case CL_SIGN_SYS_BLOCK_AVALIABLE: {
			struct Cl_sys_block_avaliable* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_sys_block_avaliable_mem* cell_mem = cell_mem_type_ref -> cell_mem_ptr.cell_avaliable;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> cell_index = cell_mem -> cell_index;
			cell_disk_ptr = cell_disk;
		}
		break;
		default: {
			return CELL_PARSING_FAILED;
		}
	}
	return CELL_PARSING_SUCCEED;
}

/* Performs transformation of given block's cells in memory form to corresponding cells of disk form.
		можно вынести в отдельный файл
 Saves transformed cells to the given address, which should be _block_content_ attribute of block in disk form.
 */
static enum block_parsing_statuses parse_cells_mem_to_disk(const struct block_mem_type_ref* const block_mem_type_ref, void* const block_contents_ptr) {
	struct cell_mem_type_ref cell_mem_type_ref;
	unsigned int cell_length;
	int bl_contents_size;
	int bl_contetns_iterator = 0;
	switch (block_mem_type_ref -> sign) {
		case BL_SIGN_HEAD:
			cell_mem_type_ref.sign = CL_SIGN_SYS_HEAD_INFO;
			bl_contents_size = block_size - sizeof(struct block_head);
			struct linked_list_CL_sys_block_head_info_mem* linked_list = block_mem_type_ref -> block_mem_ptr.block_head_ptr -> list_cells;
			while (linked_list -> next != NULL) {
				cell_mem_type_ref.cell_mem_ptr.cell_head_info = &(linked_list -> data);
				cell_length = get_real_disk_cell_size_from_mem_cell(cell_mem_type_ref.cell_mem_ptr.cell_head_info);
				assert(bl_contetns_iterator <= bl_contents_size); // return BLOCK_PARSING_FAILED;
				parse_cell_mem_to_disk(&cell_mem_type_ref, block_contents_ptr);
				bl_contetns_iterator += cell_length;
			}

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
		case BL_SIGN_HEAD: {
			struct block_head* bl_h_d = block_disk_ptr -> block_head_ptr;
			const struct block_head_mem* bl_h_m = block_mem_type_ref -> block_mem_ptr.block_head_ptr;
			bl_h_d -> cell_length = get_real_disk_cell_size_from_mem_cell( (void*) bl_h_m );
			bl_h_d -> root_data_cell = bl_h_m -> root_data_cell;
			bl_h_d -> state.blocks_amount = bl_h_m -> state.blocks_amount;
			bl_h_d -> state.next_head_block = bl_h_m -> state.next_head_block;
			bl_h_d -> state.occupied_cells_amount = bl_h_m -> state.occupied_cells_amount;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_h_d -> block_contents);
			break;
		}
		case BL_SIGN_META: {
			struct block_meta* bl_m_d = block_disk_ptr -> block_meta_ptr;
			const struct block_meta_mem* bl_m_m = block_mem_type_ref -> block_mem_ptr.block_meta_ptr;
			bl_m_d -> cell_lenght = get_real_disk_cell_size_from_mem_cell( (void*) bl_m_m);
			bl_m_d -> state.free_cells_amount_in_block = bl_m_m -> state.free_cells_amount_in_block;
			bl_m_d -> state.next_block_in_subsystem = bl_m_m -> state.next_block_in_subsystem;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_m_d -> block_contents);
			break;
		}
		case BL_SIGN_NAMES: {
			struct block_names* bl_n_d = block_disk_ptr -> block_names_ptr;
			const struct block_names_mem* bl_n_m = block_mem_type_ref -> block_mem_ptr.block_names_ptr;
			bl_n_d -> state.free_bytes_amount = bl_n_m -> state.free_bytes_amount;
			bl_n_d -> state.new_cell_start = bl_n_m -> state.new_cell_start;
			bl_n_d -> state.new_value_start = bl_n_m -> state.new_value_start;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_n_d -> block_contents);
			break;
		}
		case BL_SIGN_DATA_FC: {
			struct block_data_fixed_cells* bl_df_d = block_disk_ptr -> block_data_fc_ptr;
			const struct block_data_fixed_cells_mem* bl_df_m = block_mem_type_ref -> block_mem_ptr.block_data_fc_ptr;
			bl_df_d -> cell_lenght = get_real_disk_cell_size_from_mem_cell( (void*) bl_df_m);
			bl_df_d -> state.free_cells_amount = bl_df_m -> state.free_cells_amount;
			bl_df_d -> state.new_cell_start = bl_df_m -> state.new_cell_start;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_df_d -> block_contents);
			break;
		}
		case BL_SIGN_DATA_VC: {
			struct block_data_variable_cells* bl_dv_d = block_disk_ptr -> block_data_vc_ptr;
			const struct block_data_variable_cells_mem* bl_dv_m = block_mem_type_ref -> block_mem_ptr.block_data_vc_ptr;
			bl_dv_d -> state.free_bytes_amount = bl_dv_m -> state.free_bytes_amount;
			bl_dv_d -> state.new_cell_start = bl_dv_m -> state.new_cell_start;
			bl_dv_d -> state.new_value_start = bl_dv_m -> state.new_value_start;
			parse_cells_mem_to_disk(block_mem_type_ref, bl_dv_d -> block_contents);
			break;
		}
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
	if (NULL == block_mem_type_ref || NULL == block_mem_type_ref -> block_mem_ptr.block_head_ptr) {
		return TRUNCATE_FAILED;
	}
	const int file_offset = convert_block_index_to_file_offset(block_mem_type_ref -> block_mem_ptr.block_head_ptr->bl_index);
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

void delete_block_disk(const int fd, block_index bl_index) {

}
