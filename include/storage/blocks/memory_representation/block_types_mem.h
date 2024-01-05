#ifndef BLOCK_TYPES_MEM_H
#define BLOCK_TYPES_MEM_H

#include <stdint.h>
#include "common/data_structures/linked_list.h"
#include "storage/blocks/disk_representation/cells/utils.h"
#include "storage/blocks/memory_representation/cells/cell_types.h"

LINKED_LIST_DEFINE(CL_sys_block_head_info_mem)
LINKED_LIST_DEFINE(CL_sys_block_avaliable_mem)
LINKED_LIST_DEFINE(CL_key_mem)
LINKED_LIST_DEFINE(CL_value_mem)


struct block_head_mem {
    bool changed;
    block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    cell_index root_data_cell;
    struct {
        unsigned int blocks_amount;
        unsigned int occupied_cells_amount;
        block_index next_head_block;
    } state;
    linked_list_CL_sys_block_head_info cell_list;
};

struct block_data_fixed_cells_mem {
    bool changed;
    block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    struct {
        unsigned int free_cells_amount;
        // Related to data allignment and distribution mechanisms. (Можно и в дисковое запихнуть, можно вынести в механизм вставки новых значений)
        block_offset new_cell_start;
        block_offset new_value_start;
    } state;
    union {
      linked_list_CL_key_mem;
      linked_list_CL_value_mem;
    } list;
};

struct block_data_variable_cells_mem {
    bool changed;
    block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset free_space_start;
    } state;
    linked_list_CL_value_mem list_cells;
};

struct block_names_mem {
    bool changed;
    block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset free_space_start_tail;
    } state;
    linked_list_CL_value_mem list_cells;
};

struct block_meta_mem {
    bool changed;
    block_signature sign;
    block_index bl_index;
    block_index next_block_in_subsystem;
    struct {
        unsigned int free_cells_amount_in_block;
    } state;
    linked_list_CL_sys_block_avaliable_mem;
};

#endif //BLOCK_TYPES_MEM_H
