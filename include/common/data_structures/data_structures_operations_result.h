#ifndef DATA_STRUCTURES_OPERATIONS_RESULT_H
#define DATA_STRUCTURES_OPERATIONS_RESULT_H

enum DS_operation_result_code{
    OPERATION_SUCCES = 0,
    OPERATION_FAILURE,
};

struct operations_result {
    enum DS_operation_result_code code;
    void* operation_result;
};

#endif //DATA_STRUCTURES_OPERATIONS_RESULT_H
