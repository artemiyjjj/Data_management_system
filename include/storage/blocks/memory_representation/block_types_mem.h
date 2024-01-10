#ifndef BLOCK_TYPES_MEM_H
#define BLOCK_TYPES_MEM_H

#include "common/data_structures/linked_list.h"
#include "storage/cells/utils.h"
#include "storage/cells/memory_representation/cell_types.h"
#include "utils/status_codes.h"

LINKED_LIST_DECLARE(CL_value_mem)
LINKED_LIST_DECLARE(CL_key_mem)
LINKED_LIST_DECLARE(CL_sys_block_head_info_mem)
LINKED_LIST_DECLARE(CL_sys_block_avaliable_mem)

LINKED_LIST_DEFINE(CL_value_mem)
LINKED_LIST_DEFINE(CL_key_mem)
LINKED_LIST_DEFINE(CL_sys_block_head_info_mem)
LINKED_LIST_DEFINE(CL_sys_block_avaliable_mem)

struct block_common_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
};


struct block_head_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    struct cell_index root_data_cell;
    CL_key_mem* root_cell_mem;
    struct {
        unsigned int blocks_amount;
        unsigned int occupied_cells_amount;
        block_index next_head_block;
    } state;
    struct linked_list_CL_sys_block_head_info_mem* list_cells;
};

struct block_data_fixed_cells_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    struct {
        unsigned int free_cells_amount;
        // Related to data allignment and distribution mechanisms. (Можно и в дисковое запихнуть, можно вынести в механизм вставки новых значений)
        block_offset new_cell_start;
        block_offset new_value_start;
    } state;
    enum cell_signature cell_sign;
    union {
      struct linked_list_CL_key_mem* list_keys;
      struct linked_list_CL_value_mem* list_values;
    } list;
};

struct block_data_variable_cells_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset free_space_start;
    } state;
    struct linked_list_CL_value_mem* list_cells;
};

struct block_names_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset free_space_start_tail;
    } state;
    struct linked_list_CL_value_mem* list_cells;
};

struct block_meta_mem {
    bool changed;
    enum block_signature sign;
    block_index bl_index;
    block_index next_block_in_subsystem;
    struct {
        unsigned int free_cells_amount_in_block;
    } state;
    struct linked_list_CL_sys_block_avaliable_mem* list_cells;
};

#endif //BLOCK_TYPES_MEM_H
