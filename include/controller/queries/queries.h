#ifndef QUERIES_H
#define QUERIES_H

enum search_criteria {
    BY_NAME = 0,
    BY_VALUE,
};

struct query_result {
    char* result;
};

/* Query for reading information from document tree.

 Path should lead to key.

 If _search_criteria_ is not specified, then subtree
 starting from key given in path will be returned.
 Otherwise, query should perform search by
 */
struct select_query {
    char* path;
    enum search_criteria search_criteria;
    union {
        char* node_name;
        struct data* value;
    } search_params;
};

struct insert_query {
    char* path;
};

/*

 Value should be set to NULL to leave attributes empty.
 */
struct create_query {
    char* path;
    char* attr_name;
    char* value;
};



struct update_query {
    char* path;
    char* attr_name;
    char* value;
};

struct delete_query {
    char* path;
};

#endif //QUERIES_H
