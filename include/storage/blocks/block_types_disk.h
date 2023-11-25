#include <stdint.h>
#include "include/file/internals/blocks/utils.h"

/* 
Block head contains meta data of block types, amount of free 
*/
struct block_head {
    block_signature sign;
    // unsigned int free_block_space_start; 
    // unsigned int free_block_space_end;  
    unsigned int occupied_cells_amount;
    byte[] block_contents;
};

struct block_data {
    block_signature sign;
    cell_type block_data_type;
    unsigned int free_block_cells_amount;
    byte[] block_contents;
};


struct block_names {
    block_signature sign;
    byte[] block_contents;
}

struct block_meta {
    block_signature sign;
    
}

