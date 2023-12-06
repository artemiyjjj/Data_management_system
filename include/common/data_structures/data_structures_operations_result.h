#ifndef DATA_STRUCTURES_OPERATIONS_RESULT_H
#define DATA_STRUCTURES_OPERATIONS_RESULT_H
#include "utils/error_handle.h"

typedef enum {
    OPERATION_SUCCES = 0,
    OPERATION_FAILURE,
} DS_operation_result_code;

typedef struct {
    DS_operation_result_code code;
    void* operation_result;
} operations_result;

#endif //DATA_STRUCTURES_OPERATIONS_RESULT_H
