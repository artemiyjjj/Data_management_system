#include "storage/blocks/memory_representation/block_memory.h"
#include "common/data_structures/data_structures_operations_result.h"

LINKED_LIST_DEFINE(Cl_value_mem)
LINKED_LIST_DEFINE(Cl_key_mem)
LINKED_LIST_DEFINE(Cl_sys_block_head_info_mem)
LINKED_LIST_DEFINE(Cl_sys_block_avaliable_mem)

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

static void set_common_attributes(const struct block_mem_sign_ref *block_ref, const block_index bl_index) {
    struct block_head_mem* bl = block_ref -> block_mem_ptr.block_head_ptr;
    bl -> changed = false;
    bl -> sign = block_ref -> sign;
    bl -> bl_index = bl_index;
}

static enum alloc_code init_linked_list_to_block_mem(struct block_mem_sign_ref* const block_ref) {
    struct operations_result linked_list_res = {0};
    switch (block_ref -> sign) {
        case BL_SIGN_HEAD:
            linked_list_res = linked_list_Cl_sys_block_head_info_mem_init((Cl_sys_block_head_info_mem){0});
        break;
        case BL_SIGN_META:
            linked_list_res = linked_list_Cl_sys_block_avaliable_mem_init((Cl_sys_block_avaliable_mem){0});
        break;
        case BL_SIGN_NAMES:
            linked_list_res = linked_list_Cl_value_mem_init((Cl_value_mem){0});
        break;
        case BL_SIGN_DATA_FC:
            if (block_ref->block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_KEY) {
                linked_list_res = linked_list_Cl_key_mem_init((Cl_key_mem){0});
            } else if (block_ref->block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_VALUE) {
                linked_list_res = linked_list_Cl_value_mem_init((Cl_value_mem){0});
            // } else if (block_type_ref->block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_BIG_VALUE) {
                // linked_list_res = linked_list_Cl_value_mem_init()
            } else return MEM_ALLOC_FAILED;
        break;
        case BL_SIGN_DATA_VC:
            linked_list_res = linked_list_Cl_value_mem_init((Cl_value_mem){0});
            break;
    }
    if (linked_list_res.code == OPERATION_SUCCES) { //todo занести присваивание внутрь свитч относительно типа блока
        block_ref -> block_mem_ptr.block_head_ptr -> list_cells = linked_list_res.operation_result;
        return MEM_ALLOC_SUCCEED;
    }
    return MEM_ALLOC_FAILED;
}


/* Creates a block of a given type in memory.

 Returns a pointer to the start of a created block. Fills block with defaul data, other attributes are left unset and uninitialized.

 Need to free struct block_mem_type_ref -> block_mem_ptr.block_head_ptr
 */
enum alloc_code create_block_mem(const block_index bl_index, struct block_mem_sign_ref* const block_ref) {
    block_ref -> block_mem_ptr.block_head_ptr = malloc(get_block_size(block_ref -> sign));
    if (block_ref -> block_mem_ptr.block_head_ptr == NULL) {
        return MEM_ALLOC_FAILED;
    }
    // todo что то сделать с инициализацией листов в блоках: сейчас они есть обнуленные при создании - нужна логика работы с первым элементом листа
    init_linked_list_to_block_mem(block_ref);
    set_common_attributes(block_ref, bl_index);
    return MEM_ALLOC_SUCCEED;
}

static enum block_signature get_block_signature(void* const block) {
    return BL_SIGN_HEAD;//todo
}

/* Searches a cell matching given conditions.

 Returns pointer to a linked list with cells, matching given conditions.
 */
struct cell_mem_sign_ref select_cell_mem(struct block_mem_sign_ref* const block_ref, enum cell_select_mode select_mode, struct cell_index cell_index, struct data data) {
    // enum block_signature sign = get_block_signature(block);
    return (struct cell_mem_sign_ref){0};//todo
}

/* Performs update of a given block with given data.

 Adds new cells to or removes old ones from a block of data.
 */
struct cell_index update_block_mem(struct block_mem_sign_ref* const block_ref, enum block_update_mode update_mode, struct cell_index cell_index, struct data cell_data) {
// todo select, queries and so
    return (struct cell_index){0};
}

void do_nothing(void) {}

/* Deletes block of data in memory. */
void delete_block_mem(const struct block_mem_sign_ref block_ref) {
    switch (block_ref.sign) {
        case BL_SIGN_HEAD:
            block_ref.block_mem_ptr.block_head_ptr -> list_cells ?
            linked_list_Cl_sys_block_head_info_mem_delete(block_ref.block_mem_ptr.block_head_ptr -> list_cells) : do_nothing();
            break;
        case BL_SIGN_META:
            block_ref.block_mem_ptr.block_meta_ptr -> list_cells ?
            linked_list_Cl_sys_block_avaliable_mem_delete(block_ref.block_mem_ptr.block_meta_ptr -> list_cells) : do_nothing();
            break;
        case BL_SIGN_NAMES:
            block_ref.block_mem_ptr.block_names_ptr -> list_cells ?
            linked_list_Cl_value_mem_delete(block_ref.block_mem_ptr.block_names_ptr -> list_cells) : do_nothing();
            break;
        case BL_SIGN_DATA_FC:
            if (block_ref.block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_KEY) {
                block_ref.block_mem_ptr.block_data_fc_ptr -> list.list_keys ?
                linked_list_Cl_key_mem_delete(block_ref.block_mem_ptr.block_data_fc_ptr -> list.list_keys) : do_nothing();
            } else if (block_ref.block_mem_ptr.block_data_fc_ptr -> cell_sign == CL_SIGN_VALUE) {
                block_ref.block_mem_ptr.block_data_fc_ptr -> list.list_values ?
                linked_list_Cl_value_mem_delete(block_ref.block_mem_ptr.block_data_fc_ptr -> list.list_values) : do_nothing();
            }
            break;
        case BL_SIGN_DATA_VC:
            block_ref.block_mem_ptr.block_data_vc_ptr -> list_cells ?
            linked_list_Cl_value_mem_delete(block_ref.block_mem_ptr.block_data_vc_ptr -> list_cells) : do_nothing();
            break;
    }
    free(block_ref.block_mem_ptr.block_head_ptr);
}
