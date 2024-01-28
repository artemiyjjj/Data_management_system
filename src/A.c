#include <stdio.h>


#include "storage/storage_manager.h"

// LINKED_LIST_DEFINE(int)

#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char *argv[]) {
	// printf("Hello world\n");
	// if (argc != 2 || argc != 3)
	// 	return 1;

	int fd;
	open_file_storage("a.jj", &fd);
	// init_storage("a.jj", 4096);
	printf("%d", fd);


}