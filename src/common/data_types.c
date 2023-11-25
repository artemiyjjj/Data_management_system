#include "include/common/data_types.h"
#include <stdint.h>

size_t get_data_type_lenght(const data_type type) {
    if (type < 0) {
        return 0;
    }
    switch (type) {
        case TYPE_INTEGER: return sizeof(int); break;
        case TYPE_FLOAT32: return sizeof(float); break;
        case TYPE_BOOLEAN: return sizeof(bool); break;
        case TYPE_STRING: return ; break;
        default: return 0;
    }
}