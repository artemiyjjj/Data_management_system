#include "storage/storage_manager.h"

struct block_manager block_manager; //todo как экстернить, init?

unsigned int block_size;
int storage_fd;

enum storage_statuses init_storage(const char filename[], const unsigned int param_block_size) {
    int fd;
    if (open_file_storage(filename, &fd) == FILE_OPEN_FAILED) {
        fprintf(stderr, "Storage with name %s doesn't exist.\nCreating storage...", filename);
        if (create_file_new_storage(filename, &fd) == FILE_OPEN_FAILED) {
            fprintf(stderr, "Failed to create storage with filename %s", filename);
            return STORAGE_INIT_FAILED;
        }
    }
    block_size = param_block_size;
    storage_fd = fd;
    fprintf(stdout, "%d\n", block_size);
    fprintf(stdout, "%d", storage_fd);

    return STORAGE_INIT_SUCCED;
}


