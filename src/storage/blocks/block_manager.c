#include "storage/blocks/block_manager.h"

#include "storage/blocks/memory_representation/block_memory.h"

extern struct block_manager block_manager;

void init_block_manager(int storage_fd, ) {
    int a = storage_fd;
    storage_fd = a;
}



/* Может сделать два метода для разных критериев поиска*/
void select_cell(char cell_name[]) {
    char* a = cell_name;
    cell_name = a; //delete
}

// поменять возвр тип на енам
void create_block(const enum block_signature bl_signature) {
    void* new_mem_block_ptr = NULL;
    // void* new_disk_block_ptr = NULL;
    // enum truncate_codes block_disk_creation_code;
    const enum alloc_codes block_mem_creation_code = create_block_mem(
        bl_signature,
        block_manager.new_avaliable_block_index,
        new_mem_block_ptr);
    if (block_mem_creation_code == MEM_ALLOC_FAILED) {
    // переделать
    }
    // switch (bl_signature) {
    //     case BL_SIGN_HEAD:
    //         create_block_head((struct block_head_mem*) new_mem_block_ptr);
    //         break;
    //     case BL_SIGN_DATA_FC:
    //         create_block_data_fixed_cells((struct block_data_fixed_cells_mem*) new_mem_block_ptr);
    //         break;
    //     case BL_SIGN_DATA_VC:
    //         create_block_meta(new_mem_block_ptr);
    //         break;
    //     case BL_SIGN_NAMES:
    //         create_block_names(new_mem_block_ptr);
    //         break;
    //     case BL_SIGN_META:
    //         create_block_meta(new_mem_block_ptr);
    //         break;
    //     default: return ;
    // }
    // block_manager.block_mem_pointers[block_manager.new_avaliable_block_index] = new_mem_block_ptr;
    // block_manager.new_avaliable_block_index++;
}

/* Performs update of block in memory and disk form and then sync it with file. */
// void update_block(block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data) {
//
// }

void delete_block(const block_index bl_index) {
    block_index a = bl_index;
    exit(a);//delete
}
