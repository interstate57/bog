#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    double* x;
    double* b;
    int n, p, k, res;
    double t, r1, r2;
    int task = 7, error = 0;
    char* name = 0;
    if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 &&\
        sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &k) == 1 &&\
        (k >= 0 && k <= 4)) || (k != 0 && argc > 4)){
        printf("Usage %s n p k [name]\n", argv[0]);
        return 1;
    }
    if (argc == 5){
        name = argv[4];
    }
    a = (double*)malloc(n * n * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (name){
        io_status ret;
        ret = read_matrix(a, n, n, name);
        do{
            switch(ret){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", name); break;
                case ERROR_READ: printf("Cannot read %s \n", name); break;
            }
            free(a);
            return 3;
        } while(0);
    }
    else{
        init_matrix(a, n, n, k);
    }
    b = (double*)malloc(n * 1 * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        free(a);
        return 2;
    }
    init_matrix_b(b, n, a);
    x = (double*)malloc(n * 1 * sizeof(double));
    if (!x){
        printf("Not enough memory!\n");
        free(a);
        free(b);
        return 2;
    }
    printf("Initial matrix a \n");
    print_matrix(a, n, n, p);
    printf("Initial matrix b \n");
    print_matrix(b, n, 1, p);
    t = clock();
    res = solve(n, a, b, x);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res != 0){
        printf("This method is not applicable!\n");
        return -5;
    }
    printf("Final matrix x \n");
    print_matrix(x, 1, n, p);
    if (name){
        io_status ret;
        ret = read_matrix(a, n, n, name);
        do{
            switch(ret){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", name); break;
                case ERROR_READ: printf("Cannot read %s \n", name); break;
            }
            free(a);
            return 3;
        } while(0);
    }
    else{
        init_matrix(a, n, n, k);
    }
    init_matrix_b(b, n, a);
    r2 = calc_r2(x, n);
    r1 = calc_r1(a, b, x, n, &error);
    if (error){
        r1 = -1;
    }
    printf ( "%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);
    free(a);
    free(b);
    free(x);
    return 0;
}