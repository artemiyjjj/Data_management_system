// todo проверить корректность конст указателей на блоки
#ifndef BLOCK_H
#define BLOCK_H

#include "storage/blocks/memory_representation/block_types_mem.h"
#include "storage/blocks/disk_representation/block_types_disk.h"
#include "storage/blocks/utils.h"

/* Create block head from memory block head. */
struct block_head* create_block_head(struct block_head_mem * const bl_head_mem);

/* Update  block head contents and status due to changes in corresponding memory block. */
void update_block_head(struct block_head * const bl_head_disk, struct block_head_mem * const bl_head_mem);


/* Create block data with fixed cell length from memory block data. */
struct block_data_fixed_cells* create_block_data_fixed_cells(struct block_data_fixed_cells_mem * const bl_data_fc_mem);

/* Update block data with fixed cell length due to changes in corresponding memory block. */
void update_block_fixed_cells(struct block_data_fixed_cells *const bl_data, struct block_data_fixed_cells_mem *const bl_data_fc_mem);


/* Create block data with variable cell length from memory block data. */
struct block_data_variable_cells* create_block_data_variable_cells(struct block_data_variable_cells_mem *const bl_data_vc_mem);

/* Update block data with variable cell length due to changes in corresponding memory block. */
void update_block_variable_cells(struct block_data_variable_cells * const bl_data, struct block_data_variable_cells_mem * const bl_data_vc_mem);


/* Create block names from memory block names. */
struct block_names* create_block_names(struct block_names_mem * const bl_names_mem);

/* Update block names due to changes in corresponding memory block. */
void update_block_names(struct block_names * const bl_names, struct block_names_mem * const bl_names_mem);


/* Create block meta from memory block meta. */
struct block_meta* create_block_meta(struct block_meta_mem * const bl_meta_mem);

/* Update block meta due to changes in corresponding memory block. */
void update_block_meta(struct block_meta * const bl_meta, struct block_meta_mem * const bl_meta_mem);

#endif //BLOCK_H
