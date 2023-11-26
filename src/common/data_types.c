#include "common/data_types.h"

#include <stdbool.h>

/*
 * Returns length of application-level available types of storing data.
 *
 * In case of String type, returning value should be multiplied by the length of String entity.
 */
size_t get_data_type_lenght(const enum data_type type) {
    switch (type) {
        case TYPE_INTEGER: return sizeof(int);
        case TYPE_FLOAT32: return sizeof(float);
        case TYPE_BOOLEAN: return sizeof(bool);
        case TYPE_STRING: return sizeof(char);
        default: return 0;
    }
}