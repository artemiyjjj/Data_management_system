#include "storage/cells/disk_representation/cell_types.h"
#include "storage/cells/memory_representation/cell_types.h"

int get_mem_cell_size(const enum cell_signature cell_sign) {
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

int get_disk_cell_size(const enum cell_signature cell_sign) {
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


