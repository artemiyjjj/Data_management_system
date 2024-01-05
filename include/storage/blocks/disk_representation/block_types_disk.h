#ifndef BLOCK_TYPES_DISK_H
#define BLOCK_TYPES_DISK_H

#include "storage/blocks/disk_representation/cells/utils.h"
#include "utils/types.h"

/* Block head contains general meta data about blocks.

 Stores information about all existing blocks as block index and
 signature. In case then blocks amount becomes greater than
 avaliable head-block contents space, new head block creates to
 continue storing
*/
struct block_head {
    block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    cell_index root_data_cell;
    struct {
        int blocks_amount;
        unsigned int occupied_cells_amount;
        block_index next_head_block;
    } state;
    byte block_contents[];
};

/* Block containing data cells, possibly of any cell type, with
 fixed lenght of each cell.

 Allows to use slab mechanism to store values,
 delete and update data without fragmentation and to mark a block
 of this type with amount of free cells with certain lenght to
 quickly allocate new cells.
 */
struct block_data_fixed_cells {
    block_signature sign;
    block_index bl_index;
    unsigned int cell_lenght;
    struct {
        unsigned int free_cells_amount;
    } state;
    byte block_contents[];
};

/* Block containing data cells of any cell type and lenght of \
 a cell might vary.

 Requires to use certain slab mechanism to avoid fragmentation.
 Blocks of this type are marked with amount of avaliable bytes
 in a block.
 */
struct block_data_variable_cells {
    block_signature sign;
    block_index bl_index;
    struct  {
        unsigned int free_bytes_amount;
        /* Position in block where free space starts, starting
         after the last used element. */
        block_offset free_space_start;
    } state;
    byte block_contents[];
};

/* Block containing key-cell's names.

 Contains value-cells of type String with jenkins-hash of
 these names for faster string comparasing while searching
 for a name.
 */
struct block_names {
    block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset free_space_start_tail;
    } state;
    byte block_contents[];
};

/* Block containing information about cells, which is used by
 application management system to impove search, insertion
 and update of data.

Signatures:
    - Bl_sign_meta_data_free
 */
struct block_meta {
    block_signature sign;
    block_index bl_index;
    block_index next_block_in_subsystem;
    struct {
        unsigned int free_cells_amount_in_block;
    } state;
    byte block_contents[];
};

#endif //BLOCK_TYPES_DISK_H
