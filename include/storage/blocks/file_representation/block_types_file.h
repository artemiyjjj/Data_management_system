#ifndef BLOCK_TYPES_DISK_H
#define BLOCK_TYPES_DISK_H

#include "storage/blocks/utils.h"
#include "storage/cells/utils.h"
#include "utils/types.h"

/* Structure for parsing block info from adress of any block. */
struct block_common {
    enum block_signature sign;
    block_index bl_index;
};

/* Block head contains general meta data about blocks.

 Stores information about all existing blocks as block index and
 signature. In case then blocks amount becomes greater than
 avaliable head-block contents space, new head block creates to
 continue storing
*/
struct block_head {
    enum block_signature sign;
    block_index bl_index;
    unsigned int cell_length;
    struct cell_index root_data_cell;
    struct {
        unsigned int occupied_cells_amount;
        block_offset new_cell_start;
        unsigned int blocks_amount;
        block_index next_head_block;
    } state;
    m_byte block_contents[];
};

/* Block containing data cells, possibly of any cell type, with
 fixed lenght of each cell.

 Allows to use slab mechanism to store values,
 delete and update data without fragmentation and to mark a block
 of this type with amount of free cells with certain lenght to
 quickly allocate new cells.
 */
struct block_data_fixed_cells {
    enum block_signature sign;
    block_index bl_index;
    unsigned int cell_lenght;
    struct {
        unsigned int free_cells_amount;
        block_offset new_cell_start;
    } state;
    m_byte block_contents[];
};

/* Block containing data cells of any cell type and lenght of \
 a cell might vary.

 Requires to use certain slab mechanism to avoid fragmentation.
 Blocks of this type are marked with amount of avaliable bytes
 in a block.
 */
struct block_data_variable_cells {
    enum block_signature sign;
    block_index bl_index;
    struct  {
        unsigned int free_bytes_amount;
        /* Position in block where free space starts, starting
         after the last used element. */
        block_offset new_cell_start;
        block_offset new_value_start;
    } state;
    m_byte block_contents[];
};

/* Block containing key-cell's names.

 Contains value-cells of type String with jenkins-hash of
 these names for faster string comparasing while searching
 for a name.
 */
struct block_names {
    enum block_signature sign;
    block_index bl_index;
    struct {
        unsigned int free_bytes_amount;
        block_offset new_cell_start;
        block_offset new_value_start;
    } state;
    m_byte block_contents[];
};

/* Block containing information about cells, which is used by
 application management system to impove search, insertion
 and update of data.

Signatures:
    - Bl_sign_meta_data_free
 */
struct block_meta {
    enum block_signature sign;
    block_index bl_index;
    unsigned int cell_lenght;
    struct {
        unsigned int free_cells_amount_in_block;
        block_offset new_cell_start;
        block_index next_block_in_subsystem;
    } state;
    m_byte block_contents[];
};

/* Structure to represent any type of block
 *
 * Use it's signature to determine block type.
*/
struct block_file_sign_ref {
    enum block_signature sign;
    union block_file_ptr {
        struct block_head* block_head_ptr;
        struct block_data_fixed_cells* block_data_fc_ptr;
        struct block_data_variable_cells* block_data_vc_ptr;
        struct block_names* block_names_ptr;
        struct block_meta* block_meta_ptr;
    } block_file_ptr;
};

#endif //BLOCK_TYPES_DISK_H
