#include <stdio.h>
#include "array_io.h"

io_status read_matrix(double* a, int n, int m, const char* name){
    int i, j;
    FILE* fp;
    if (!(fp = fopen(name, "r"))){
        return ERROR_OPEN;
    }
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j++){
            if (fscanf(fp, "%lf", a + i * m + j) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}

void print_matrix(double* a, int n, int m, int p){
    int np = (n > p ? p : n);
    int mp = (m > p ? p : m);
    int i, j;
    for (i = 0; i < np; i ++){
        for (j = 0; j < mp; j++){
            printf(" %10.3e", a[i * m + j]);
        }
        printf("\n");
    }
}

double max(double a, double b){
    return (a > b ? a : b);
}

double f(int k, int n, int m, int i, int j){
    i++;
    j++;
    switch(k){
        case 1: return max(n, m) - max(i, j) + 1;
        case 2: return max(i, j);
        case 3: return (i > j ? i - j : j - i);
        case 4: return 1. / (i + j - 1);
    }
    return -1e308;
}

void init_matrix(double* a, int n, int m, int k){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            a[i * m + j] = f(k, n, m, i, j);
}