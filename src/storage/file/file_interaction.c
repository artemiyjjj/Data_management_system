#include "storage/file/file_interaction.h"

#include "storage/utils.h"

enum file_open_code open_file_storage(const char filename[], int* const fd) {
	*fd = open(filename, O_RDWR);
	if (*fd == -1) {
		perror("function: open_file_storage -> ");
		return FILE_OPEN_FAILED;
	}
	return FILE_OPEN_SUCEED;
}

/* Creates file with given name and opens it.

 Returns fd for created file.
 File permissions set to user - read, write; group - read; others - nothing.
 */
enum file_open_code create_file_new_storage(const char filename[], int* const fd) {
	*fd = open(filename, O_CREAT | O_RDWR, S_IRWXU);
	if (*fd == -1) {
		perror("function: create_file_storage -> ");
		return FILE_OPEN_FAILED;
	}
	return FILE_OPEN_SUCEED;
}

enum file_close_code close_file_storage(const struct storage_info storage_info) {
	if (close(storage_info.fd) != 0) {
		perror("Failed to close storage. Function: close_file_storage -> \n");
		return FILE_CLOSE_FAILED;
	}
	return FILE_CLOSE_SUCCEED;
}

enum mmap_code load_block(const struct storage_info storage_info, const unsigned int file_offset, void** block_file) {
	*block_file = mmap(NULL, storage_info.block_size, PROT_READ | PROT_WRITE, MAP_SHARED, storage_info.fd, file_offset);
	if (block_file == MAP_FAILED && errno == EINVAL) {
		return MMAP_FAILED_INCOMPATIBLE_PAGE_SIZE;
	}
	else if (block_file == MAP_FAILED) {
		return MMAP_FAILED;
	}
	return MMAP_SUCCEED;
}

enum munmap_code unload_block(const struct storage_info storage_info, void* block_file) {
	if (sync_block(storage_info, block_file) == MSYNC_FAILED) {
		perror("Failed to sync block\n");
		return MUNMAP_FAILED;
	}
	return munmap(block_file, storage_info.block_size) == 0 ? MUNMAP_SUCCED : MUNMAP_FAILED;
}

enum msync_code sync_block(const struct storage_info storage_info, void* const block_file) {
	return msync(block_file, storage_info.block_size, MS_SYNC) == 0 ? MSYNC_SUCCED : MSYNC_FAILED;
}

enum truncate_code create_empty_block(const struct storage_info storage_info, const unsigned int file_offset) {
	int truncate_lenght = file_offset + storage_info.block_size;
	return ftruncate(storage_info.fd, truncate_lenght);
}

enum truncate_code delete_block_from_file(const struct storage_info storage_info, const unsigned int file_offset) {
	return TRUNCATE_FAILED; //todo
}
