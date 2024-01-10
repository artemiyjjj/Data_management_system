#ifndef CELL_TYPES_H
#define CELL_TYPES_H

#include "storage/cells/utils.h"
#include "common/data_types.h"
#include "storage/blocks/utils.h"

/* Cell type for stroing key entities with name, their subkeys and attributes.

Contains a state structure, which values dynamicly update according to program logic.

Signature - Cl_sign_key
*/
struct Cl_key {
    enum cell_signature sign;
    struct cell_index key_name_cell;
    struct cell_index parent_cell;
    struct cell_index subkeys_list_cell;
    struct {
        unsigned int subkeys_amount;
    } state;
};

/* Cell type for storing values for key.

Signature - Cl_sign_value
*/
struct Cl_value {
    enum cell_signature sign;
    enum data_type value_type;
    unsigned int value_size;
    block_offset value_data_index; // todo как то поменять, чтобы значение торчало с конца клетки: либо юнион либо void* либо byte[value_size]
};

/* Cell type for storing values larger than a capacity of data block.

 Value stored in this type of cell is cut into pieces and put in some amount of value cells,
 consequentially placed in a cell-list of type Cl_key_index.
 Value and index cells might belong to different data blocks.

 Signature - Cl_sign_big_value
*/
struct Cl_big_value {
    enum cell_signature sign;
    struct cell_index value_name;
    /* Cell index for next element of the list of big-value cells' parts */
    struct cell_index index_cell_of_parts;
    unsigned int big_value_size;
};

/* Cell type for storing key cells (subkeys) of typeCl_key_node and value cells of type Cl_key_value in a list manner.
Each cell contains block and cell index (pointer) for a key or value cell of a list and cell index of the next Cl_key_index,
representing a next value of list.

To specify type of cell which is represented in an index cell, signature must be set.

Signatures:
    - Cl_sign_key_index - list of Cl_key_node cell type (subkeys) elements
    - Cl_sign_value_index - list of Cl_key_value cell type (values) elements
*/
struct Cl_index {
    enum cell_signature sign;
    /* Cell index for the Cl_value_data / Cl_key_node cell with the value's / subkeyavaliable 's data. */
    struct cell_index key_subkey_or_value_cell;
    /* Cell index for the next Cl_key_index cell, pointing to the next cell of a list.*/
    struct cell_index next_cell;
};

/* Cell for storing info about each block.

 Used in blocks of type _block_head_.
*/
struct Cl_sys_block_head_info {
    enum cell_signature sign;
    block_index bl_index;
    enum block_signature bl_sign;
    unsigned int avaliable_space;
};

/* Cell type for storing application meta data on blocks with data and their avaliable space for content.

 */
struct Cl_sys_block_avaliable {
    enum cell_signature sign;
    struct cell_index cell_index;

};

int get_disk_cell_size(const enum cell_signature cell_sign);



#endif //CELL_TYPES_H
