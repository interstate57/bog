#include <stdio.h>
#include "array_io.h"

io_status read_matrix(double* x, double* y, int n, const char* name){
    int i, j;
    FILE* fp;
    if (!(fp = fopen(name, "r"))){
        return ERROR_OPEN;
    }
    for (i = 0; i < n; i ++){
        for (j = 0; j < 2; j++){
            if (j == 0){
                if (fscanf(fp, "%lf", x + i) != 1){
                    fclose(fp);
                    return ERROR_READ;
                }
            }
            else{
                if (fscanf(fp, "%lf", y + i) != 1){
                    fclose(fp);
                    return ERROR_READ;
                }
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}

void print_matrix(double* a, int n, int m){
    int i, j;
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j++){
            printf(" %10.3e", a[i * m + j]);
        }
        printf("\n");
    }
}