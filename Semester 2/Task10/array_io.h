#pragma once
typedef enum io_status_{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
} io_status;

io_status read_matrix(double* x, double* y, int n, const char* name);
void print_matrix(double* a, int n, int m);
