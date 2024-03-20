#ifndef FILE_INTERACTION_H
#define FILE_INTERACTION_H

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include "storage/utils.h"

#include "utils/status_codes.h"

/* Opens existing storage. */
enum file_open_code open_file_storage(const char filename[], int* const fd);

/* Creates a new file for storage. */
enum file_open_code create_file_new_storage(const char filename[], int* const fd);

/* Closes stoarage. Uses then program exits. */
enum file_close_code close_file_storage(const struct storage_info storage_info);

// add incompatible page size error handler
enum mmap_code load_block(const struct storage_info storage_info, const unsigned int file_offset, void** block_file);

enum munmap_code unload_block(const struct storage_info storage_info, void* block_file);

/* Function to update block contents on corresponding segment in file. */
enum msync_code sync_block(const struct storage_info storage_info, void* const block_file);
// todo можно ли просматривать статус page.dirty через системные вызовы?
// Если да, то круто, иначе нужно создать в каждом block_* в памяти индикатор изменения значений 

/* Function to create block in file.
 *
 * @arg file_offset - offset from the file start, where new block should start.
 */
enum truncate_code create_empty_block(const struct storage_info storage_info, const unsigned int file_offset);

enum truncate_code delete_block_from_file(const struct storage_info storage_info, const unsigned int file_offset);
/* todo логика удаления блока
 для избежания фрагментации данных:
 - перемещение последующих блоков назад - дорого;
 - сохранение норм, проще отчистить содержимое для обновления информации о занятости
 - если удалили много инфы, можно создать механизм для перемещения клеток по соседниим блокам - сложно
*/

#endif //FILE_INTERACTION_H
