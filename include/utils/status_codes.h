#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

enum file_open_code {
    FILE_OPEN_SUCEED = 0,
    FILE_OPEN_FAILED
};

enum file_close_code {
    FILE_CLOSE_SUCCEED = 0,
    FILE_CLOSE_FAILED
};

enum mmap_code {
    MMAP_SUCCEED = 0,
    MMAP_FAILED,
    MMAP_FAILED_INCOMPATIBLE_PAGE_SIZE,
};

enum msync_code {
    MSYNC_SUCCED = 0,
    MSYNC_FAILED
};

enum truncate_code {
    TRUNCATE_SUCCED = 0,
    TRUNCATE_FAILED
};

enum munmap_code {
    MUNMAP_SUCCED = 0,
    MUNMAP_FAILED
};

enum alloc_code {
    MEM_ALLOC_SUCCEED = 0,
    MEM_ALLOC_FAILED
};

enum storage_init_status {
    STORAGE_INIT_FAILED = 0,
    STORAGE_INIT_SUCCED_LOAD,
    STORAGE_INIT_SUCCED_CREATE
};

enum storage_close_status {
    STORAGE_CLOSE_SUCCESS = 0,
    STORAGE_CLOSE_FAILED,
};

enum block_init_status {
    BLOCK_INIT_SUCCED = 0,
    BLOCK_INIT_FAILED
};

enum block_parsing_status {
    BLOCK_PARSING_SUCCEED = 0,
    BLOCK_PARSING_FAILED,
};

enum block_manager_blocks_creation_status {
    BLOCK_MANAGER_BLOCKS_CREATION_SUCCEED = 0,
    BLOCK_MANAGER_BLOCKS_CREATION_FAILED,
};

enum block_manager_blocks_read_status {
    BLOCK_MANAGER_BLOCKS_READ_SUCCEED = 0,
    BLOCK_MANAGER_BLOCKS_READ_FAILED,
};

enum block_manager_blocks_update_status {
    BLOCK_MANAGER_BLOCKS_UPDATE_SUCCEED = 0,
    BLOCK_MANAGER_BLOCKS_UPDATE_FAILED,
};

enum block_manager_blocks_deletion_status {
    BLOCK_MANAGER_BLOCKS_DELETION_SUCCEED = 0,
    BLOCK_MANAGER_BLOCKS_DELETION_FAILED,
};

enum cell_parsing_status {
    CELL_PARSING_SUCCEED = 0,
    CELL_PARSING_FAILED,
};



#endif //ERROR_HANDLE_H
