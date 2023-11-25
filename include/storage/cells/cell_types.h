#include "include/file/internals/cells/utils.h"
#include "include/common/data_types.h"

/* 
Signature - Cl_sign_node
*/
struct Cl_key_node {
    cell_signature sign;
    block_offset key_name;
    cell_index parent_index;
    cell_index subkeys_list_index;
    cell_index values_list_index;
    // todo мб убрать?? Все равно лист укажет есть ли следующий,
    // НО можно подстраховаться и проще индексировать кол-во детей и атрибутов 
    unsigned int subkeys_amount;
    unsigned int values_amount;
};

/*
Signature - Cl_sign_value
*/
struct Cl_key_value {
    cell_signature sign;
    block_offset value_name;
    data_type value_type;
    block_offset value_data_index;
};

/* Cell type for storing values bigger than 4kB. 
The cell has a linked list of cells, pointing to data cells which store parts big-value's parts and might belong to different blocks. 
In that case, each element of Cl_key_index list contains cell indexes to Cl_value_data, which shoudn't be interpreted without the context of big-value. 
Signature - Cl_sign_big_value
*/
struct Cl_key_big_value {
    cell_signature sign;
    block_offset value_name;
    /* Cell index for the first element of the list of cell indicies for each big-value's part */
    cell_index list_first_cell;
    size_t big_value_size;
};

/*
Signature 
    - Cl_sign_key_index - for subkeys list elements
    - Cl_sign_value_index - for values list elementsэ
*/
struct Cl_key_index {
    cell_signature sign;
    /* Cell index for the Cl_value_data / Cl_key_node cell with the value's / subkey's data. */
    cell_index key_value_cell;
    /* Cell index for the next Cl_key_index cell.*/
    cell_index next_cell;
};

/* Cell type indicates what right after it data is stored. Contains data lenght.
Signature - Cl_sign_value_data
*/
struct Cl_value_data {
    cell_signature sign;
    block_size cell_size;
    
};
