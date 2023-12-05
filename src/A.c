#include <stdio.h>
#include "common/data_structures/linked_list.h"

LINKED_LIST_DEFINE(int)

int main(int argc, char *argv[]) {
	printf("Hello world\n");
	// LINKED_LIST_DECLARE(int)

	linked_list_int *ll = linked_list_int_init(1).operation_result;
	// LINKED_LIST_DATA(ll) = 1;
	linked_list_int_push(&ll, 2);
	printf("Linked list node: %d\n", ll->data);
	linked_list_int *l2 = ll->next;
	printf("Linked list node 2: %d\n", LINKED_LIST_DATA(l2));


}