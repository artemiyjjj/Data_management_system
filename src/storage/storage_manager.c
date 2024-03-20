#include <errno.h>

#include "storage/storage_manager.h"

// логику выбора размера блока от платформы через define
#define DEFAULT_BLOCK_SIZE 4096


enum storage_init_status init_storage(const char filename[], const struct block_manager_config bl_manager_config, struct storage_manager* const storage_manager) {
    struct block_manager bl_manager;
    int is_newly_created = 0;

    if (filename == NULL) {
        perror("Failed to init_storage: filename is not defined.\n");
        return STORAGE_INIT_FAILED;
    }

    storage_manager -> storage_info.block_size = DEFAULT_BLOCK_SIZE;
    if (open_file_storage(filename, &(storage_manager -> storage_info.fd)) == FILE_OPEN_FAILED) {
        fprintf(stderr, "Storage with name %s doesn't exist.\nCreating storage...\n", filename);
        // логика чтения размера блока из заголовка стораджа в файле
        if (create_file_new_storage(filename, &storage_manager -> storage_info.fd) == FILE_OPEN_FAILED) {
            fprintf(stderr, "Failed to create storage with filename %s", filename);
            return STORAGE_INIT_FAILED;
        }
        is_newly_created = 1;
        fprintf(stdout, "Storage with name %s created.\n", filename);
    }
    fprintf(stdout, "Storage with name %s opened.\n", filename);
    {
        enum block_manager_creation_mode block_manager_creation_mode = is_newly_created ? BM_CREATE_MODE_NEW : BM_CREATE_MODE_EXISTING;

        if (init_block_manager(bl_manager_config, block_manager_creation_mode, &bl_manager) == BLOCK_INIT_FAILED) {
            perror("Failed to initialize block_manager");
            return STORAGE_INIT_FAILED;
        }
        struct operations_result result = linked_list_block_manager_init(bl_manager);
        if (result.code == OPERATION_FAILURE) {
            perror("Failed to initialize block_manager list for storage_manager");
            return STORAGE_INIT_FAILED;
        }
        storage_manager -> list_block_manager = (struct linked_list_block_manager*) result.operation_result;
    }
    return is_newly_created ? STORAGE_INIT_SUCCED_CREATE : STORAGE_INIT_SUCCED_LOAD;
}

enum storage_close_status close_storage(struct storage_manager* const storage_manager) {
    // storage_manager->list_block_manager
    if (FILE_CLOSE_FAILED == close_file_storage(storage_manager -> storage_info)) {
        perror("Can not close file properly.");
    }
    fprintf(stdout, "File storage with fd %d is closed.\n", storage_manager -> storage_info.fd );
    return STORAGE_CLOSE_SUCCESS;
}

void select_value(struct select_query* const query);

void insert_value(struct insert_query* const query);

void update_value(struct update_query* const query);

void delete_value(struct delete_query* const query);


