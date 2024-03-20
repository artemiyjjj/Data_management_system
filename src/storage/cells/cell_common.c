#include "storage/cells/cell_common.h"


int get_file_cell_size_from_mem_cell(const struct cell_mem_sign_ref* const cell_ref) {
	switch (cell_ref -> sign) {
		case CL_SIGN_KEY:
			return sizeof(struct Cl_key);
		case CL_SIGN_VALUE:
			return sizeof(struct Cl_value) + cell_ref -> cell_mem_ptr.cell_value -> value_size;
		case CL_SIGN_BIG_VALUE:
			return sizeof(struct Cl_big_value);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return sizeof(struct Cl_index);
		case CL_SIGN_SYS_HEAD_INFO:
			return sizeof(struct Cl_sys_block_head_info);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return sizeof(struct Cl_sys_block_avaliable);
		default:
			return -1;
	}
}

int get_mem_cell_size_from_file_cell(const struct cell_file_sign_ref* const cell_ref) {
	switch (cell_ref -> sign) {
		case CL_SIGN_KEY:
			return sizeof(struct Cl_key);
		case CL_SIGN_VALUE:
			return sizeof(struct Cl_value) + cell_ref -> cell_file_ptr.cell_value -> value_size;
		case CL_SIGN_BIG_VALUE:
			return sizeof(struct Cl_big_value);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return sizeof(struct Cl_index);
		case CL_SIGN_SYS_HEAD_INFO:
			return sizeof(struct Cl_sys_block_head_info);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return sizeof(struct Cl_sys_block_avaliable);
		default:
			return -1;
	}
}


/* Transforms mem cell to disk cell and returns it's address by argument _cell_disk_ptr_.
		можно вынести в отдельный файл
 Addres _cell_disk_addr_ in some scenarios might be memory contents area.
 Returns
 - size of resulted disk cell in bytes as returning value.
 - newly created disk cell address as second parameter.

 When file cell becomes unneeded, free(*cell addr*) should be performed on returned address.
 */
enum cell_parsing_status parse_cell_mem_to_file(const struct cell_mem_sign_ref* const src_cell, union cell_file_ptr* const dest_cell) {
	switch (src_cell -> sign) {
		case CL_SIGN_KEY: {
			struct Cl_key* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_key_mem* cell_mem = src_cell -> cell_mem_ptr.cell_key;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> key_name_cell =  cell_mem -> name_cell -> cell_index;
			cell_disk -> parent_cell = cell_mem -> parent_cell -> cell_index;
			cell_disk -> key_name_cell = cell_mem -> child_list -> cell_index;
			cell_disk -> state.subkeys_amount = cell_mem -> state.subkeys_amount;
			dest_cell -> cell_key = cell_disk;
		}
		break;
		case CL_SIGN_VALUE: {
			const struct Cl_value_mem* cell_mem = src_cell -> cell_mem_ptr.cell_value;
			struct Cl_value* cell_disk = malloc(sizeof(*cell_disk) + cell_mem -> value_size); //todo пригодится гет сайз коммон
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> value_type = cell_mem -> data.type;
			cell_disk -> value_size = cell_mem -> value_size;
			memcpy(&(cell_disk -> value), &(cell_mem -> data), cell_mem -> value_size);
			dest_cell -> cell_value = cell_disk;
		}
		break;
		case CL_SIGN_BIG_VALUE: {
			struct Cl_big_value* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_big_value_mem* cell_mem = src_cell -> cell_mem_ptr.cell_big_value;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> value_name =  cell_mem -> name_cell -> cell_index;
			cell_disk -> index_cell_of_parts = cell_mem -> list_of_parts -> cell_index;
			cell_disk -> big_value_size = cell_mem -> big_value_size;
			dest_cell -> cell_big_value = cell_disk;
		}
		break;
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE: {
			struct Cl_index* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_index_mem* cell_mem = src_cell -> cell_mem_ptr.cell_index;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> key_subkey_or_value_cell = cell_mem -> indexing_cell.key_cell -> cell_index;
			cell_disk -> next_cell = cell_mem -> next_index_cell -> cell_index;
			dest_cell -> cell_index = cell_disk;
		}
		break;
		case CL_SIGN_SYS_HEAD_INFO: {
			struct Cl_sys_block_head_info* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_sys_block_head_info_mem* cell_mem = src_cell -> cell_mem_ptr.cell_head_info;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> bl_index = cell_mem -> bl_index;
			cell_disk -> bl_sign = cell_mem -> bl_sign;
			cell_disk -> bl_avaliable_space = cell_mem -> avaliable_space;
			dest_cell -> cell_head_info = cell_disk;
		}
		break;
		case CL_SIGN_SYS_BLOCK_AVALIABLE: {
			struct Cl_sys_block_avaliable* cell_disk = malloc(sizeof(*cell_disk));
			const struct Cl_sys_block_avaliable_mem* cell_mem = src_cell -> cell_mem_ptr.cell_avaliable;
			cell_disk -> sign = cell_mem -> sign;
			cell_disk -> cell_index = cell_mem -> cell_index;
			dest_cell -> cell_avaliable = cell_disk;
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
 Saves transformed cells to the given address, which should be _block_content_ attribute of block in file form.
 */
enum block_parsing_status parse_cells_mem_to_file(const struct block_mem_sign_ref* const src_mem_block, union cell_file_ptr* const dest_cell, const unsigned int block_size) {
	struct cell_mem_sign_ref mem_cell_ref= (struct cell_mem_sign_ref) {0};
	unsigned int cell_length;
	int bl_contents_size;
	int bl_contetns_iterator = 0;

	switch (src_mem_block -> sign) {
		case BL_SIGN_HEAD: {
			mem_cell_ref.sign = CL_SIGN_SYS_HEAD_INFO;
			bl_contents_size = block_size - sizeof(struct block_head);
			struct linked_list_Cl_sys_block_head_info_mem* linked_list = src_mem_block -> block_mem_ptr.block_head_ptr -> list_cells;
			while (linked_list -> next != NULL) {
				mem_cell_ref.cell_mem_ptr.cell_head_info = &(linked_list -> data);
				cell_length = get_file_cell_size_from_mem_cell(&mem_cell_ref);
				if (bl_contetns_iterator <= bl_contents_size) {
					return BLOCK_PARSING_FAILED;
				}
				parse_cell_mem_to_file(&mem_cell_ref, dest_cell);
				bl_contetns_iterator += cell_length;
			}
		}
			break;
		case BL_SIGN_META: {
			mem_cell_ref.sign = CL_SIGN_SYS_BLOCK_AVALIABLE;
			bl_contents_size = block_size - sizeof(struct block_meta);
			struct linked_list_Cl_sys_block_avaliable_mem* linked_list = src_mem_block -> block_mem_ptr.block_meta_ptr -> list_cells;
			while (linked_list -> next != NULL) {

//todo
			}
		}
			break;
		case BL_SIGN_NAMES:
			mem_cell_ref.sign = CL_SIGN_VALUE;
			bl_contents_size = block_size - sizeof(struct block_names);
			break;
		case BL_SIGN_DATA_FC:
			mem_cell_ref.sign = CL_SIGN_VALUE;
			bl_contents_size = block_size - sizeof(struct block_data_fixed_cells);
			break;
		case BL_SIGN_DATA_VC:

			break;
		default:
			return BLOCK_PARSING_FAILED;
	}
	return BLOCK_PARSING_SUCCEED;
}

enum cell_parsing_status parse_cell_file_to_mem(const struct cell_file_sign_ref* const src_cell, union cell_mem_ptr const dest_cell) {
	return CELL_PARSING_SUCCEED;
}
//todo
enum block_parsing_status parse_cells_file_to_mem(const struct block_file_sign_ref* const src_cell, union cell_mem_ptr* const dest_cell) {
	return BLOCK_PARSING_FAILED;
}
