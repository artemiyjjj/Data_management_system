#include <stdint.h>
#include "include/file/internals/blocks/utils.h"

struct block_head {
    block_signature sign;
    uint32_t free_block_space_start; 
    uint32_t free_block_space_end;  
    uint32_t occupied_cells_amount;



};

struct block_data {
    block_signature sign;
    uint32_t free_block_space_start;
    uint32_t free_block_space_end;
    uint32_t occupied_cells_amount;

};

struct block_types {
    block_signature sign;
    uint32_t free_block_space_start;
    uint32_t free_block_space_end;
    uint32_t occupied_cells_amount;

};
