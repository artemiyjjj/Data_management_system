#include "storage/cells/disk_representation/cell_types.h"
#include "storage/cells/memory_representation/cell_types.h"

int get_mem_cell_size(const enum cell_signature cell_sign) {
	switch (cell_sign) {
		case CL_SIGN_KEY:
			return sizeof(CL_key_mem);
		case CL_SIGN_VALUE:
			return sizeof(CL_value_mem);
		case CL_SIGN_BIG_VALUE:
			return sizeof(CL_big_value_mem);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return sizeof(CL_index_mem);
		case CL_SIGN_SYS_HEAD_INFO:
			return sizeof(CL_sys_block_head_info_mem);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return sizeof(CL_sys_block_avaliable_mem);
		default:
			return 0;
	}
}

/* Returns size of a cell by _sizeof()_.

 Returns incorrect values in case cell has flexible array members.
 */
int get_disk_cell_size(const enum cell_signature cell_sign) {
	switch (cell_sign) {
		case CL_SIGN_KEY:
			return sizeof(struct Cl_key);
		case CL_SIGN_VALUE:
			return sizeof(struct Cl_value);
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
			return 0;
	}
}

/* Returns size of a cell, calculated by cell size + cell value (if present). */
int get_real_disk_cell_size(void* const disk_cell_ptr) {
	struct Cl_key *cell = disk_cell_ptr;
	const enum cell_signature sign = cell -> sign;
	switch (sign) {
		case CL_SIGN_KEY:
			return get_disk_cell_size(CL_SIGN_KEY);
		case CL_SIGN_VALUE:
			const struct Cl_value *cell_value = disk_cell_ptr;
			return get_disk_cell_size(CL_SIGN_VALUE) + cell_value -> value_size;
		case CL_SIGN_BIG_VALUE:
			return get_disk_cell_size(CL_SIGN_BIG_VALUE);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return get_disk_cell_size(CL_SIGN_INDEX_KEY);
		case CL_SIGN_SYS_HEAD_INFO:
			return get_disk_cell_size(CL_SIGN_SYS_HEAD_INFO);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return get_disk_cell_size(CL_SIGN_SYS_BLOCK_AVALIABLE);
		default:
			return -1;
	}
}

int get_real_disk_cell_size_from_mem_cell(void* const mem_cell_ptr) {
	struct CL_key_mem *cell = (CL_key_mem*) mem_cell_ptr;
	const enum cell_signature sign = cell -> sign;
	switch (sign) {
		case CL_SIGN_KEY:
			return get_disk_cell_size(CL_SIGN_KEY);
		case CL_SIGN_VALUE:
			const struct CL_value_mem *cell_value = mem_cell_ptr;
		return get_disk_cell_size(CL_SIGN_VALUE) + cell_value -> value_size;
		case CL_SIGN_BIG_VALUE:
			return get_disk_cell_size(CL_SIGN_BIG_VALUE);
		case CL_SIGN_INDEX_KEY:
		case CL_SIGN_INDEX_VALUE:
			return get_disk_cell_size(CL_SIGN_INDEX_KEY);
		case CL_SIGN_SYS_HEAD_INFO:
			return get_disk_cell_size(CL_SIGN_SYS_HEAD_INFO);
		case CL_SIGN_SYS_BLOCK_AVALIABLE:
			return get_disk_cell_size(CL_SIGN_SYS_BLOCK_AVALIABLE);
		default:
			return -1;
	}
}
