#include "storage/blocks/memory_representation/block_memory.h"

static size_t get_block_size(const enum block_signature bl_sign) {
    switch (bl_sign) {
        case BL_SIGN_HEAD:
            return sizeof(struct block_head_mem);
        case BL_SIGN_DATA_FC:
            return sizeof(struct block_data_fixed_cells_mem);
        case BL_SIGN_DATA_VC:
            return sizeof(struct block_data_variable_cells_mem);
        case BL_SIGN_NAMES:
            return sizeof(struct block_names_mem);
        case BL_SIGN_META:
            return sizeof(struct block_meta_mem);
        default:
            return 0;
    }
}

static void set_common_attributes(void* const block, const enum block_signature bl_sign, const block_index bl_index) {
    struct block_head_mem* bl = block;
    bl -> changed = false;
    bl -> sign = bl_sign;
    bl -> bl_index = bl_index;
}

static enum block_signature get_block_signature(void* const block) {
    return BL_SIGN_HEAD;//todo
}


/* Creates a block of a given type in memory.

 Returns a pointer to the start of a created block. Fills block with defaul data, other attributes are left unset and uninitialized.
 */
enum alloc_codes create_block_mem(struct block_mem_type_ref* const block_type_ref, const block_index bl_index) {
    void* block_ptr = block_type_ref -> block_mem_ptr.block_head_ptr;
    block_ptr = malloc(get_block_size(block_type_ref -> sign));
    if (block_ptr == NULL) {
        return MEM_ALLOC_FAILED;
    }
    set_common_attributes(block_ptr, block_type_ref -> sign, bl_index);
    return MEM_ALLOC_SUCCEED;
}

/* Searches a cell with a certain name.

 Returns pointer to a cell with a given name
 */
void* select_cell_mem(struct block_mem_type_ref* const block_type_ref, enum cell_select_mode select_mode, char* cell_name) {
    enum block_signature sign = get_block_signature(block);
    return 0;//todo
}

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(void* block, enum block_update_mode update_mode, char* cell_name, struct data cell_data) {
    exit((int) block);

    return (struct cell_index){0};
}


/* Deletes block of data in memory. */
void delete_block_mem(const struct block_mem_type_ref block_type_ref) {
    switch (block_type_ref.sign) {
        case BL_SIGN_HEAD:
            linked_list_CL_sys_block_head_info_mem_delete(block_type_ref.block_mem_ptr.block_head_ptr -> list_cells);
            break;
        case BL_SIGN_META:
            linked_list_CL_sys_block_avaliable_mem_delete(block_type_ref.block_mem_ptr.block_meta_ptr -> list_cells);
            break;
        case BL_SIGN_NAMES:
            linked_list_CL_value_mem_delete(block_type_ref.block_mem_ptr.block_names_ptr -> list_cells);
            break;
        case BL_SIGN_DATA_FC:
            if (block_type_ref.block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_KEY) {
                linked_list_CL_key_mem_delete(block_type_ref.block_mem_ptr.block_data_fc_ptr -> list.list_keys);
            } else if (block_type_ref.block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_VALUE) {
                linked_list_CL_value_mem_delete(block_type_ref.block_mem_ptr.block_data_fc_ptr -> list.list_values);
            }
            break;
        case BL_SIGN_DATA_VC:
            linked_list_CL_value_mem_delete(block_type_ref.block_mem_ptr.block_data_vc_ptr -> list_cells);
            break;
    }
    free(block_type_ref.block_mem_ptr.block_head_ptr);
}
