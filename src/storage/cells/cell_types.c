#include "storage/cells/file_representation/cell_types.h"
#include "storage/cells/memory_representation/cell_types.h"

#include "storage/cells/cell_common.h"

int get_mem_cell_size(const struct cell_mem_sign_ref* const cell_ref) {
	switch (cell_ref -> sign) {
		case CL_SIGN_KEY:
			return sizeof(Cl_key_mem);
		case CL_SIGN_VALUE:
			return sizeof(Cl_value_mem);
		case CL_SIGN_BIG_VALUE:
			return sizeof(Cl_big_value_mem);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return sizeof(Cl_index_mem);
		case CL_SIGN_SYS_HEAD_INFO:
			return sizeof(Cl_sys_block_head_info_mem);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return sizeof(Cl_sys_block_avaliable_mem);
		default:
			return 0;
	}
}

/* Returns size of a cell, calculated by cell size + cell value (if present). */
int get_file_cell_size(const struct cell_file_sign_ref* const cell_ref) {
	switch (cell_ref -> sign) {
		case CL_SIGN_KEY:
			return sizeof(*cell_ref -> cell_file_ptr.cell_key);
		case CL_SIGN_VALUE:
			struct Cl_value *cell_value = cell_ref -> cell_file_ptr.cell_value;
			return sizeof(*cell_value) + cell_value -> value_size;
		case CL_SIGN_BIG_VALUE:
			return sizeof(*cell_ref -> cell_file_ptr.cell_big_value);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return sizeof(cell_ref -> cell_file_ptr.cell_index);
		case CL_SIGN_SYS_HEAD_INFO:
			return sizeof(cell_ref -> cell_file_ptr.cell_head_info);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return sizeof(cell_ref -> cell_file_ptr.cell_avaliable);
		default:
			return -1;
	}
}
