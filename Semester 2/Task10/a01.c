#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* x;
    double* y;
    int n;
    double t, x0, r;
    int task = 7;
    char* name = 0;
    if (!((argc == 4) && sscanf(argv[1], "%d", &x0) == 1 &&\
        sscanf(argv[2], "%d", &n))){
        printf("Usage %s x0 n name\n", argv[0]);
        return 1;
    }
    name = argv[3];
    x = (double*)malloc(n * 1 * sizeof(double));
    if (!x){
        printf("Not enough memory!\n");
        return 2;
    }
    y = (double*)malloc(n * 1 * sizeof(double));
    if (!y){
        printf("Not enough memory!\n");
        free(x);
        return 2;
    }
    if (name){
        io_status ret;
        ret = read_matrix(x, y, n, name);
        do{
            switch(ret){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", name); break;
                case ERROR_READ: printf("Cannot read %s \n", name); break;
            }
            free(x);
            free(y);
            return 3;
        } while(0);
    }
    printf("Initial matrix x \n");
    print_matrix(x, 1, n);
    printf("Initial matrix y \n");
    print_matrix(y, 1, n);
    t = clock();
    r = solve1(x0, n, x, y);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, r, t);
    free(x);
    free(y);
    return 0;
}