#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "common/data_structures/data_structures_operations_result.h"

#define NODE_DECLARE(T)                     \
typedef struct {                            \
    T data;                                 \
} node_##T;                                 \
operations_result create_node_##T(T data);  \
operations_result delete_node_##T(node_##T node);        \

#define NODE_DEFINE(T)                      \
NODE_DECLARE(T)                             \
operations_result create_node_##T(T data) { \
    operations_result result = {};          \
    node_##T* node = malloc(sizeof(*node)); \
    if (node == NULL) { result.code = OPERATION_FAILURE; }      \
    else {                                                      \
        result.code = OPERATION_SUCCES;                         \
        result.operation_result = (void*) node;                 \
        node->data = data;                                      \
    }                                                           \
    return result;                                              \
}                                                               \
                                                                \
operations_result delete_node_##T(node_##T* node) {             \
    operations_result result = {};                              \
    if (node != NULL) {                                         \
        free(node);                                             \
    }                                                           \
    result = {.code = OPERATION_SUCCES };                       \
    return result;                                              \
}
#endif //NODE_H
