#include "storage/blocks/block_common.h"

enum block_parsing_status parse_block_file_to_mem(const struct block_file_sign_ref* const src_block, union block_mem_ptr* const dest_block) {
	return BLOCK_PARSING_SUCCEED; //todo
}


static void set_common_attributes(void** const block, const enum block_signature bl_sign, const block_index bl_index) {
	struct block_common* bl = (struct block_common*) *block;
	bl -> sign = bl_sign;
	bl -> bl_index = bl_index;
}

enum block_parsing_status parse_block_mem_to_file(const unsigned int block_size, const struct block_mem_sign_ref* const src_block_mem, union block_file_ptr* const dest_block_file) {
	if (NULL == src_block_mem || NULL == src_block_mem -> block_mem_ptr.block_head_ptr) {
		return BLOCK_PARSING_FAILED;
	}
	const enum block_signature bl_sign = src_block_mem -> sign;
	set_common_attributes(
		(void*) &dest_block_file -> block_head_ptr,
		bl_sign,
		src_block_mem -> block_mem_ptr.block_head_ptr -> bl_index);

	switch (bl_sign) {
		case BL_SIGN_HEAD: {
			struct block_head* bl_h_d = dest_block_file -> block_head_ptr;
			const struct block_head_mem* bl_h_m = src_block_mem -> block_mem_ptr.block_head_ptr;
			bl_h_d -> cell_length = get_file_cell_size_from_mem_cell( (void*) bl_h_m );
			bl_h_d -> root_data_cell = bl_h_m -> root_data_cell;
			bl_h_d -> state.blocks_amount = bl_h_m -> state.blocks_amount;
			bl_h_d -> state.next_head_block = bl_h_m -> state.next_head_block;
			bl_h_d -> state.occupied_cells_amount = bl_h_m -> state.occupied_cells_amount;
			parse_cells_mem_to_file(src_block_mem, bl_h_d -> block_contents, block_size);
			break;
		}
		case BL_SIGN_META: {
			struct block_meta* bl_m_d = dest_block_file -> block_meta_ptr;
			const struct block_meta_mem* bl_m_m = src_block_mem -> block_mem_ptr.block_meta_ptr;
			bl_m_d -> cell_lenght = get_file_cell_size_from_mem_cell( (void*) bl_m_m);
			bl_m_d -> state.free_cells_amount_in_block = bl_m_m -> state.free_cells_amount_in_block;
			bl_m_d -> state.next_block_in_subsystem = bl_m_m -> state.next_block_in_subsystem;
			parse_cells_mem_to_file(src_block_mem, bl_m_d -> block_contents, block_size);
			break;
		}
		case BL_SIGN_NAMES: {
			struct block_names* bl_n_d = dest_block_file -> block_names_ptr;
			const struct block_names_mem* bl_n_m = src_block_mem -> block_mem_ptr.block_names_ptr;
			bl_n_d -> state.free_bytes_amount = bl_n_m -> state.free_bytes_amount;
			bl_n_d -> state.new_cell_start = bl_n_m -> state.new_cell_start;
			bl_n_d -> state.new_value_start = bl_n_m -> state.new_value_start;
			parse_cells_mem_to_file(src_block_mem, bl_n_d -> block_contents, block_size);
			break;
		}
		case BL_SIGN_DATA_FC: {
			struct block_data_fixed_cells* bl_df_d = dest_block_file -> block_data_fc_ptr;
			const struct block_data_fixed_cells_mem* bl_df_m = src_block_mem -> block_mem_ptr.block_data_fc_ptr;
			bl_df_d -> cell_lenght = get_file_cell_size_from_mem_cell( (void*) bl_df_m);
			bl_df_d -> state.free_cells_amount = bl_df_m -> state.free_cells_amount;
			bl_df_d -> state.new_cell_start = bl_df_m -> state.new_cell_start;
			parse_cells_mem_to_file(src_block_mem, bl_df_d -> block_contents, block_size);
			break;
		}
		case BL_SIGN_DATA_VC: {
			struct block_data_variable_cells* bl_dv_d = dest_block_file -> block_data_vc_ptr;
			const struct block_data_variable_cells_mem* bl_dv_m = src_block_mem -> block_mem_ptr.block_data_vc_ptr;
			bl_dv_d -> state.free_bytes_amount = bl_dv_m -> state.free_bytes_amount;
			bl_dv_d -> state.new_cell_start = bl_dv_m -> state.new_cell_start;
			bl_dv_d -> state.new_value_start = bl_dv_m -> state.new_value_start;
			parse_cells_mem_to_file(src_block_mem, bl_dv_d -> block_contents, block_size);
			break;
		}
		default:
			return BLOCK_PARSING_FAILED;
	}
	return BLOCK_PARSING_SUCCEED;
}
