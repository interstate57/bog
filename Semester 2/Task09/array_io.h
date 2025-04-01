#pragma once
typedef enum io_status_{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
} io_status;

io_status read_matrix(double* a, int n, int m, const char* name);
void print_matrix(double* a, int n, int m, int p);
double f(int k, int n, int m, int i, int j);
double max_zn(double a, double b);
void init_matrix(double* a, int n, int m, int k);
void init_matrix_b(double* b, int n, double* a);