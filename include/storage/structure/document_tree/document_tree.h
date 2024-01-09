#ifndef DOCUMENT_TREE_H
#define DOCUMENT_TREE_H

#include "common/data_structures/tree.h"
#include "common/data_types.h"

typedef struct DT_node {
    char* DT_key_name;
    struct data;
} DT_node;

TREE_DECLARE(DT_node)






#endif //DOCUMENT_TREE_H
