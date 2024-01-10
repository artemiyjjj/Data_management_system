#include "storage/blocks/utils.h"

extern unsigned int block_size;

unsigned int convert_block_index_to_file_offset(const block_index bl_index) {
	return block_size * bl_index;
}
