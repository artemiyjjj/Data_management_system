#include "storage/blocks/utils.h"

#include "storage/blocks/block_manager_pub.h"

/* Calculates file offset from a given block length and block index.*/
unsigned int compute_file_offset_from_block_index(const unsigned int block_size, const block_index bl_index) {
	return block_size * bl_index;
}
