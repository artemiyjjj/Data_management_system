#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

enum file_open_codes {
    FILE_OPEN_SUCEED = 0,
    FILE_OPEN_FAILED
};

enum file_close_codes {
    FILE_CLOSE_SUCCEED = 0,
    FILE_CLOSE_FAILED
};

enum mmap_codes {
    MMAP_SUCCEED = 0,
    MMAP_FAILED,
    MMAP_FAILED_INCOMPATIBLE_PAGE_SIZE,
};

enum msync_codes {
    MSYNC_SUCCED = 0,
    MSYNC_FAILED
};

enum truncate_codes {
    TRUNCATE_SUCCED = 0,
    TRUNCATE_FAILED
};

enum munmap_codes {
    MUNMAP_SUCCED = 0,
    MUNMAP_FAILED
};

enum alloc_codes {
    MEM_ALLOC_SUCCEED = 0,
    MEM_ALLOC_FAILED
};

enum storage_statuses {
    STORAGE_INIT_SUCCED = 0,
    STORAGE_INIT_FAILED,
};

enum cell_parsing_statuses {
    CELL_PARSING_SUCCEED = 0,
    CELL_PARSING_FAILED,
};

enum block_parsing_statuses {
    BLOCK_PARSING_SUCCEED = 0,
    BLOCK_PARSING_FAILED,
};

#endif //ERROR_HANDLE_H
