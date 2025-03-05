#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    int n, m, i, j, p, k;
    double t, r;
    int task = 8;
    char* name = 0;
    if (!((argc == 8 || argc == 9) && sscanf(argv[1], "%d", &i) == 1 &&\
        sscanf(argv[2], "%d", &j) == 1 && sscanf(argv[3], "%lf", &r) == 1 &&\
        sscanf(argv[4], "%d", &n) == 1 && sscanf(argv[5], "%d", &m) == 1 && sscanf(argv[6], "%d", &p) == 1 &&\
        sscanf(argv[7], "%d", &k) == 1 && (k >= 0 && k <= 4)) || (k != 0 && argc == 9)){
        printf("Usage %s i j r n m p k [name] \n", argv[0]);
        return 1;
    }
    if (argc == 9)
        name = argv[8];
    a = (double*)malloc(n * m * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (name){
        io_status ret;
        ret = read_matrix(a, n, m, name);
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
        init_matrix(a, n, m, k);
    }
    printf("Initial matrix \n");
    print_matrix(a, n, m, p);
    t = clock();
    solve8(a, n, m, i, j, r);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("Final matrix\n");
    print_matrix(a, n, m, p);
    printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);
    free(a);
    return 0;
}