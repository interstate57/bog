#pragma once
typedef enum io_status_{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
} io_status;

io_status read_matrix(double* a, int n, int m, const char* name);
void print_matrix(double* a, int n, int m, int p);
double max(double a, double b);
double f(int k, int n, int m, int i, int j);
void init_matrix(double* a, int n, int m, int k);

