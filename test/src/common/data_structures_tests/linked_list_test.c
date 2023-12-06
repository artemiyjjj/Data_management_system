#include <assert.h>

#include "common/data_structures/linked_list.h"

LINKED_LIST_DEFINE(int)

DEFINE_TEST(linked_list_init) {
    const int test_value = 1;
    linked_list_int *ll = linked_list_int_init(test_value).operation_result;
    assert(ll != NULL);
    assert(ll->data == test_value);
}

DEFINE_TEST(linked_list_push) {
    const int test_value = 2;
    linked_list_int *ll = linked_list_int_init(1).operation_result;
    linked_list_push(&ll, test_value);
    linked_list_int *next_ll = ll->next;
    assert(next_ll->data = test_value);
}

DEFINE_TEST(linked_list_delete) {
    const int initial_value = 1;
    const int second_value = 2;
    linked_list_int *ll = linked_list_int_init(initial_value).operation_result;
    linked_list_push(&ll, second_value);
    linked_list_int *next_ll = ll->next;
    linked_list_delete(next_ll);
    assert(ll->next == NULL);
}
