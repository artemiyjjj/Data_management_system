#include "storage/file/file_interaction.h"

enum file_open_codes open_file_storage(const char filename[], int* const fd) {
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
enum file_open_codes create_file_new_storage(const char filename[], int* const fd) {
	*fd = open(filename, O_CREAT | O_RDWR, S_IRWXU);
	if (*fd == -1) {
		perror("function: create_file_storage -> ");
		return FILE_OPEN_FAILED;
	}
	return FILE_OPEN_SUCEED;
}

enum file_close_codes close_file_storage(const int fd) {
	if (close(fd) != 0) {
		perror("function: close_file_storage -> ");
		return FILE_CLOSE_FAILED;
	}
	return FILE_CLOSE_SUCCEED;
}

enum mmap_codes load_block(const int  fd, const unsigned int file_offset) {

}

