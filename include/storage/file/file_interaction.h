#ifndef FILE_INTERACTION_H
#define FILE_INTERACTION_H

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "utils/status_codes.h"

/* Externs from A.c ...*/
extern unsigned int block_size;

/* Opens existing storage. */
enum file_open_codes open_file_storage(const char filename[], int* const fd);

/* Creates a new file for storage. */
enum file_open_codes create_file_new_storage(const char filename[], int* const fd);

/* Closes stoarage. Uses then program exits. */
enum file_close_codes close_file_storage(int fd);

// add incompatible page size error handler
enum mmap_codes load_block(const int  fd, const unsigned int file_offset);

enum munmap_codes unload_block(const int fd, const unsigned int file_offset);

/* Function to update block contents on corresponding segment in file. */
enum msync_codes sync_block(const int fd, void* const block_disk_representation);
// todo можно ли просматривать статус page.dirty через системные вызовы?
// Если да, то круто, иначе нужно создать в каждом block_* в памяти индикатор изменения значений 

/* Function to store newly created block in file. */
enum truncate_codes write_new_block_to_file(const int fd, const unsigned int file_offset, void* const block_disk_representation);

enum truncate_codes delete_block_from_file(const int fd, const unsigned int file_offset);
/* todo логика удаления блока
 для избежания фрагментации данных:
 - перемещение последующих блоков назад - дорого;
 - сохранение норм, проще отчистить содержимое для обновления информации о занятости
 - если удалили много инфы, можно создать механизм для перемещения клеток по соседниим блокам - сложно
*/

#endif //FILE_INTERACTION_H
