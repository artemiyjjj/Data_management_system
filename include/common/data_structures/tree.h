#ifndef TREE_H
#define TREE_H

#include "common/data_structures/data_structures_operations_result.h"
#include "common/data_structures/linked_list.h"
#include "utils/templates.h"

//TEMPLATE(linked_list, TREE_TYPE_PTR)
// #define GET_TREE_TYPE_TEMPLATE(T) TEMPLATE(tree, T)
// #define GET_TREE_TYPE_PTR_TEMPLATE(T) TEMPLATE(TEMPLATE(tree, T), ptr)

#define TREE_DECLARE(T)                                     \
struct tree_##T;                                            \
typedef struct tree_##T* tree_##T##_ptr;                     \
LINKED_LIST_DEFINE(tree_##T##_ptr)                              \
typedef struct {                                            \
    T data;                                                 \
    tree_##T##_ptr parent_node;                           \
    linked_list_tree_##T##_ptr* child_nodes;                    \
} tree_##T;                                                 \
operations_result tree_##T##_init();                          \
operations_result tree_##T##_create_node(const T data);                   \
operations_result tree_##T##_add_child(const tree_##T* const parent_tree_node, tree_##T* const child_tree_node);            \
operations_result tree_##T##_delete_node(tree_##T* const tree_node);     \
operations_result tree_##T##_delete_subtree(tree_##T* const tree_node);

#define TREE_DEFINE(T)                                      \
TREE_DECLARE(T)                                             \
operations_result tree_##T##_init() {                         \
    operations_result result = {};                          \
    tree_##T* tree = malloc(sizeof(*tree));                 \
    if (tree == NULL) {                                     \
        result.code = OPERATION_FAILURE;                    \
        return result;                                      \
    }                                                       \
    operations_result list_creation_result = linked_list_tree_##T##_ptr_init(NULL); \
    if (list_creation_result.code == OPERATION_SUCCES) {                            \
        tree -> child_nodes = list_creation_result.operation_result;                \
        tree -> data = 0;                                                           \
        tree -> parent_node = 0;                                                    \
        result.operation_result = tree;                                             \
        result.code = OPERATION_SUCCES;                                             \
    }                                                                               \
    else {                                                                          \
        free(tree);                                                                 \
        result.code = OPERATION_FAILURE;                                            \
    }                                                                               \
    return result;                                          \
}                                                           \
/* Adds a child tree node (2-nd parameter) to the parent tree node (1-st parameter).                                 \
 Returns operation code, operation result is invalid. */                                                              \
operations_result tree_##T##_add_child(const tree_##T* const parent_tree_node, tree_##T* const child_tree_node) {    \
    operations_result result = {};                                                                          \
    operations_result list_result;                                                                              \
    if (parent_tree_node == NULL || child_tree_node == NULL) {                                               \
        result.code = OPERATION_FAILURE;                                                                    \
        return result;                                                                                      \
    }                                                                                                       \
    linked_list_tree_##T##_ptr* child_list = parent_tree_node -> child_nodes;                                  \
    if (child_list -> data == NULL) {                                                                           \
        child_list -> data = child_tree_node;                                                                   \
        result.code = OPERATION_SUCCES;                                                                         \
    }                                                                                                           \
    else {                                                                                                      \
        list_result = linked_list_tree_##T##_ptr_push(&child_list, child_tree_node);                            \
        result.code = list_result.code;                                                                         \
    }                                                                                                           \
    if (result.code == OPERATION_SUCCES) {                                                        \
        child_tree_node -> parent_node = parent_tree_node;                                                       \
    }                                                                                                       \
    return result;                                                                                          \
}                                                                                                           \
                                                                                                            \
operations_result tree_##T##_create_node(const T data) {                                                    \
    operations_result result = tree_##T##_init();                                                           \
    if (result.code == OPERATION_FAILURE) {                                                                 \
        return result;                                                                                      \
    }                                                                                                       \
    tree_##T* tree = result.operation_result;                                                               \
    tree -> data = data;                                                                                    \
    return result;                                                                                          \
}                                                                                                           \
                                                                                                            \
/* Deletes single tree node. Before using the function, get sure it has no child nodes */                   \
operations_result tree_##T##_delete_node(tree_##T* const tree_node) {                                        \
    operations_result result = {};                                                                          \
    if (tree_node != NULL) {                                                                                \
        linked_list_tree_##T##_ptr* child_list = tree_node -> child_nodes;                                   \
        linked_list_tree_##T##_ptr* next_list;                                                                    \
        while (child_list != NULL) {                                                                        \
            next_list = child_list -> next;                                                                 \
            free(child_list);                                                                               \
            child_list = next_list;                                                                         \
        }                                                                                                   \
        free(tree_node);                                                                                    \
        result.code = OPERATION_SUCCES;                                                                     \
    }                                                                                                       \
    else {                                                                                                  \
        result.code = OPERATION_FAILURE;                                                                    \
    }                                                                                                       \
    return result;                                                                                          \
}                                                                                                           \
                                                                                                            \
/* Deletes subtree of any tree, without deleting the root node, given as an argument to the function  */    \
operations_result tree_##T##_delete_subtree(tree_##T* const tree_node) {                                    \
    operations_result result = {};                                                                          \
    if (tree_node == NULL) {                                                                                \
        result.code = OPERATION_FAILURE;                                                                    \
        return result;                                                                                      \
    }                                                                                                       \
    linked_list_tree_##T##_ptr* child_list = tree_node -> child_nodes;                                       \
    while (child_list != NULL && child_list -> data != NULL) {                                              \
        tree_##T##_delete_subtree(child_list -> data);                                                      \
        child_list = child_list -> next;                                                                    \
    }                                                                                                       \
    return result;                                                                                          \
}






#endif //TREE_H
