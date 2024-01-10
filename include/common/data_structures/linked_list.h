#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "common/data_structures/data_structures_operations_result.h"

#define LINKED_LIST_DECLARE(T)          \
struct linked_list_##T {                        \
    T data;                             \
    struct linked_list_##T * prev;       \
    struct linked_list_##T * next;       \
};                                                                  \
inline struct operations_result linked_list_##T##_init(T data);                                     \
inline struct operations_result linked_list_##T##_push(struct linked_list_##T *linked_list, T data);    \
inline struct operations_result linked_list_##T##_delete(struct linked_list_##T *linked_list);          \

// #define LINKED_LIST_TYPE(T) linked_list_##T
// #define LINKED_LIST_DATA(linked_list) (linked_list)->data
// #define LINKED_LIST_PREV(linked_list) (linked_list)->prev
// #define LINKED_LIST_NEXT(linked_list) (linked_list)->next
//
// #define LINKED_LIST_INIT(T, data) linked_list_##T##_init(data)
// #define LINKED_LIST_PUSH(T, linked_list, data) linked_list_##T##_push(linked_list, data)
// #define LINKED_LIST_DELETE(T, linked_list) linked_list_##T##_delete(linked_list)

#define LINKED_LIST_DEFINE(T)                                                                   \
                                                                          \
inline struct operations_result linked_list_##T##_init(T data) {                                              \
    struct operations_result result;                                                              \
    struct linked_list_##T * linked_list = malloc(sizeof(*linked_list));                               \
    if (linked_list == NULL) { result.code = OPERATION_FAILURE; }                               \
    else {                                                                                      \
        result.code = OPERATION_SUCCES;                                                         \
        result.operation_result = (void*) linked_list;                                          \
        linked_list->data = data;                                                               \
    }                                                                                           \
    return result;                                                                              \
}                                                                                               \
inline struct operations_result linked_list_##T##_push(struct linked_list_##T *linked_list, T data) {               \
    struct operations_result result;                                                            \
    struct linked_list_##T *new_node = malloc(sizeof(*new_node));                                 \
    if (NULL == new_node) {                                                                     \
        result.code = OPERATION_FAILURE;                                                        \
        return result;                                                                          \
    }                                                                                           \
    new_node->data = data;                                                                      \
    linked_list->next = new_node;                                                            \
    new_node->prev = linked_list;                                                              \
    result.code = OPERATION_SUCCES;                                                             \
    return result;                                                                              \
}                                                                                               \
                                                                                                \
inline struct operations_result linked_list_##T##_delete(struct linked_list_##T *linked_list) { \
    struct operations_result result;                                          \
    if (NULL == linked_list){                       \
        result.code = OPERATION_FAILURE;                                    \
        return result;               \
    }                                                                       \
    struct linked_list_##T *prev_node = linked_list->prev;                        \
    struct linked_list_##T *next_node = linked_list->next;                        \
    if (prev_node != NULL) { prev_node->next = next_node; }                 \
    if (next_node != NULL) { next_node->prev = prev_node; }                 \
    free(linked_list);                                                     \
    result.code = OPERATION_SUCCES;                                         \
    return result;                                                          \
}

#endif //LINKED_LIST_H
