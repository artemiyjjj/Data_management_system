#ifndef BLOCK_TYPES_DISK_H
#define BLOCK_TYPES_DISK_H

#include "storage/blocks/cells/utils.h"
#include "storage/blocks/utils.h"
#include "utils/types.h"

/* Block head contains meta data of block types, amount of free
*/
struct block_head {
    block_signature sign;

    unsigned int occupied_cells_amount;
    byte block_contents[];
};

/* Block containing data cells [?of any cell type] with fixed
 lenght of data.

 Allows to use slab mechanism to store values,
 delete and update data without fragmentation and to mark a block
 of this type with amount of free cells with certain lenght to
 quickly allocate new cells.
 */
struct block_data_fixed_cells {
    block_signature sign;
    unsigned int cell_lenght;
    struct {
        unsigned int free_block_cells_amount;
    } state;
    byte block_contents[];
};

/* Block containing data cells [?of any cell type] with variable
 lenght of data.

 Requires to use certain slab mechanism to avoid fragmentation.
 Blocks of this type are marked with amount of avaliable bytes
 in a block.
 */
struct block_data_variable_cells {
    block_signature sign;
    struct  {
        unsigned int free_bytes_amount;
        block_offset free_space_start_tail;
    } state;
    byte blick_contents[];
};

/* Block containing key-cell's names as values-cells of Strings
 * with jenkins-hash of these names for faster searching for a name.
 */
struct block_names {
    block_signature sign;
    struct {
        unsigned int free_bytes_amount;
    } state;
    byte block_contents[];
};

struct block_meta {
    block_signature sign;

    byte block_contents[];
};

#endif //BLOCK_TYPES_DISK_H
