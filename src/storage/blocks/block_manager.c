#include "storage/blocks/block_manager.h"

#include <assert.h>


LINKED_LIST_DEFINE(block_manager)


enum alloc_code init_block_manager_struct(const struct block_manager_config bl_manager_config, struct block_manager* const block_manager) {
    if (bl_manager_config.max_loaded_blocks_amount < 1) {
        perror("Failed to init block_manager structure: Max loaded blocks amount should be greater than zero.\n");
        return MEM_ALLOC_FAILED;
    }
    if (bl_manager_config.storage_info->fd < 0) {
        perror("Failed to init block_manager structure: fd is not correct");
        return MEM_ALLOC_FAILED;
    }
    block_manager -> storage_info = *bl_manager_config.storage_info;
    block_manager -> max_loaded_blocks_amount = bl_manager_config.max_loaded_blocks_amount;

    block_manager -> block_mem_pointers.load_block_amount = 0;
    struct block_mem_sign_ref** mem_block_array = malloc(sizeof(struct block_mem_sign_ref*) * bl_manager_config.max_loaded_blocks_amount);
    if (NULL == mem_block_array) {
        return MEM_ALLOC_FAILED;
    }
    for (unsigned int i = 0; i < bl_manager_config.max_loaded_blocks_amount; i++) {
        mem_block_array[i] = NULL;
    }
    block_manager -> block_mem_pointers.block_ref_array = mem_block_array;

    block_manager -> block_file_pointers.load_block_amount = 0;
    struct block_file_sign_ref** file_block_array = malloc(sizeof(struct block_file_sign_ref*) * bl_manager_config.max_loaded_blocks_amount);
    if (NULL == file_block_array) {
        free(mem_block_array);
        return MEM_ALLOC_FAILED;
    }
    for (unsigned int i = 0; i < bl_manager_config.max_loaded_blocks_amount; i++) {
        file_block_array[i] = NULL;
    }
    block_manager -> block_file_pointers.block_ref_array = file_block_array;

    return MEM_ALLOC_SUCCEED;
}

static void update_block_manager_load(struct block_manager* block_manager,
                                struct block_mem_sign_ref* const mem_block,
                                struct block_file_sign_ref* const file_block)
{
    int loaded_block_pair = 0;
    for (; loaded_block_pair < block_manager -> max_loaded_blocks_amount; loaded_block_pair++) {
        if (block_manager -> block_mem_pointers.block_ref_array[loaded_block_pair] != NULL) {
            break;
        }
    }
    block_manager -> block_mem_pointers.block_ref_array[loaded_block_pair] = mem_block;
    block_manager -> block_mem_pointers.load_block_amount++;
    assert(block_manager -> block_file_pointers.block_ref_array[loaded_block_pair] != NULL);
    block_manager -> block_file_pointers.block_ref_array[loaded_block_pair] = file_block;
    block_manager -> block_mem_pointers.load_block_amount++;
}

static void update_block_manager_unload(struct block_manager* block_manager,
                                const struct block_mem_sign_ref* const mem_block,
                                const struct block_file_sign_ref* const file_block)
{
    int unloaded_block_pair = 0;
    for (; unloaded_block_pair < block_manager -> max_loaded_blocks_amount; unloaded_block_pair++) {
        if (block_manager -> block_mem_pointers.block_ref_array[unloaded_block_pair] == mem_block) {
            break;
        }
    }
    assert(block_manager -> block_mem_pointers.block_ref_array[unloaded_block_pair] != NULL);
    block_manager -> block_mem_pointers.block_ref_array[unloaded_block_pair] = NULL;
    block_manager -> block_mem_pointers.load_block_amount--;
    block_manager -> block_file_pointers.block_ref_array[unloaded_block_pair] = NULL;
    block_manager -> block_mem_pointers.load_block_amount--;
}

//todo вопрос 1
void delete_block_manager_struct(const struct block_manager* block_manager) {
    // for (int i = 0; i < block_manager->block_mem_pointers.load_block_amount; i++) {
    //     bl
    // }
    free(block_manager -> block_file_pointers.block_ref_array);
    free(block_manager -> block_mem_pointers.block_ref_array);
}

/* Initialize block_manager and it's inner structures.
 */
enum block_init_status init_block_manager(const struct block_manager_config bl_manager_config, const enum block_manager_creation_mode creation_mode,
                                            struct block_manager* const block_manager)
{
    init_block_manager_struct(bl_manager_config, block_manager);
    // логика чтения информации о состоянии блоков в хранилище
    switch (creation_mode) {
        case BM_CREATE_MODE_NEW: {
            block_manager -> new_avaliable_block_index = 0;
            if (BLOCK_MANAGER_BLOCKS_CREATION_FAILED == create_block(block_manager, BL_SIGN_HEAD)) {
                return BLOCK_INIT_FAILED;
            }

        }
        break;
        case BM_CREATE_MODE_EXISTING: {
            // todo parse block head info
            //block_manager -> new_avaliable_block_index = block_head -> new_avaliable_block_index;
            //block_manager -> storage_info.block_size = block_head -> block_size
        }
        break;
        default:
            return BLOCK_INIT_FAILED;
    }
    return BLOCK_INIT_SUCCED;
}


/* Может сделать два метода для разных критериев поиска*/
void select_cell(char cell_name[]) {
    char* a = cell_name;
    cell_name = a; //delete
}

/* Creates block in the file, maps it into the memory and initializes its header.

 Updates it's block_manager state when loads new block.
 *Need to free block_mem_sign_ref and block_file_sign_ref in block_manager when block is unloaded.
 */
enum block_manager_blocks_creation_status create_block(struct block_manager* const block_manager, const enum block_signature bl_signature) {
    struct block_mem_sign_ref* new_mem_block_ptr = malloc(sizeof(*new_mem_block_ptr));
    struct block_file_sign_ref* new_file_block_ptr = malloc(sizeof(*new_file_block_ptr));
    new_mem_block_ptr -> sign = bl_signature;
    new_file_block_ptr -> sign = bl_signature;

    const enum alloc_code block_mem_creation_code = create_block_mem(
        block_manager -> new_avaliable_block_index,
        new_mem_block_ptr
        );

    if (block_mem_creation_code == MEM_ALLOC_FAILED) {
        return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    }

    enum truncate_code block_file_creation_code = create_block_file(block_manager -> storage_info, block_manager -> new_avaliable_block_index);
    if (block_file_creation_code == TRUNCATE_FAILED) {
        free(new_mem_block_ptr -> block_mem_ptr.block_head_ptr);
        return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    }
    block_manager -> new_avaliable_block_index++;

    enum mmap_code load_block_code = read_block_file(
        block_manager -> storage_info,
        block_manager -> new_avaliable_block_index,
        &(new_file_block_ptr -> block_file_ptr));

    if (load_block_code == MMAP_FAILED_INCOMPATIBLE_PAGE_SIZE) {
        perror("Failed to mmap file region: given page size is not acceptable (divisible by 4096).\n");
        return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    }
    else if (load_block_code == MMAP_FAILED) {
        perror("Failed to mmap file region.\n");
    }

    enum msync_code update_block_code = update_block_file(
        block_manager -> storage_info,
        new_mem_block_ptr,
        &(new_file_block_ptr -> block_file_ptr));

    if (update_block_code == MSYNC_FAILED) {
        return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    }

    update_block_manager_load(block_manager, new_mem_block_ptr, new_file_block_ptr);

    return BLOCK_MANAGER_BLOCKS_CREATION_SUCCEED;
}

/* Performs update of block in memory and disk form and then sync it with file. */
// void update_block(block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data) {
//
// }
enum block_manager_blocks_update_status update_block(struct block_manager* const block_manager, const block_index bl_index,
                                                    enum block_update_mode update_mode, char* cell_name, struct data cell_data)
{
    // struct block_file_sign_ref* file_block;
    //  /* if (block -> bl_index in block_manager -> file_blocks) {
    // *   file_block = that
    // *}
    // * else load_block(bl_index)
    // * ...
    // */
    // enum msync_code update_block_code = update_block_file(
    //     block_manager -> storage_info,
    //     new_mem_block_ptr,
    //     &(new_file_block_ptr -> block_file_ptr));
    //
    // if (update_block_code == MSYNC_FAILED) {
    //     return BLOCK_MANAGER_BLOCKS_UPDATE_FAILED;
    // }
    return BLOCK_MANAGER_BLOCKS_UPDATE_FAILED;
    // for (int i = 0, i < block_manager -> block_mem_pointers.load_block_amount, i ++) {
    //     struct block_mem_sign_ref* mem_block_ptr = block_manager -> block_mem_pointers.block_ref_array[];
    //     // struct block_file_sign_ref* file_block_ptr = malloc(sizeof(*new_file_block_ptr));
    // }
    //
    //
    //
    // enum msync_code update_block_code = update_block_file(
    //     block_manager -> storage_info,
    //     new_mem_block_ptr,
    //     &(new_file_block_ptr -> block_file_ptr));
    // if (update_block_code == MSYNC_FAILED) {
    //     return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    // }
    //
    // if (sync_block(block_manager -> storage_info, new_file_block_ptr -> block_file_ptr.block_head_ptr) == MSYNC_FAILED) {
    //     perror("Failed to sync created block.\n");
    //     return BLOCK_MANAGER_BLOCKS_CREATION_FAILED;
    // }
    //
    // update_block_manager_load(block_manager, new_mem_block_ptr, new_file_block_ptr);
    //
    // return BLOCK_MANAGER_BLOCKS_UPDATE_FAILED;
}


enum block_manager_blocks_deletion_status delete_block(struct block_manager* const block_manager, const block_index bl_index) {
    return BLOCK_MANAGER_BLOCKS_DELETION_FAILED;
}
