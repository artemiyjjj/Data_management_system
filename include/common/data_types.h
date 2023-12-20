#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stddef.h>

enum data_type {
    TYPE_INTEGER = 0,
    TYPE_FLOAT32,
    TYPE_STRING,
    TYPE_BOOLEAN
};

size_t get_data_type_lenght(const enum data_type type);

#endif //DATA_TYPES_H
