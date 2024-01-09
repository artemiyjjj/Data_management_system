#include "storage/blocks/block_manager.h"

block_index new_avaliable_block_index;

void* block_mem_pointers[];
void* block_disk_pointers[];

void select_cell(char* cell_name) {

}

void create_block(enum block_signature bl_signature) {
    void* new_block = create_block_mem(bl_signature);
    block_mem_pointers[new_avaliable_block_index] =
}

/* Performs update of block in memory and disk form and then sync it with file. */
void update_block(block_index bl_index, enum block_update_mode update_mode, char* cell_name, struct data cell_data) {

}

void delete_block(block_index bl_index) {

}