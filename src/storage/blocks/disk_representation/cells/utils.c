#include "storage/blocks/disk_representation/cells/utils.h"

#include <stddef.h>

struct cell_index create_cell_index(const block_index bl_index, const block_offset bl_offset) {
    return {.bl_index = bl_index, .bl_offset = bl_offset};
}

void change_block_index(struct cell_index* const cell, const block_index new_bl_index) {
    if (cell != NULL) { cell -> bl_index = new_bl_index; }
}

void change_block_offset(struct cell_index* const cell, const block_offset new_bl_offset) {
    if (cell != NULL) { cell -> bl_offset = new_bl_offset; }
}
