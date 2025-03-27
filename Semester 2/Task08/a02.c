#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    double* b;
    double* x;
    double* xm;
    int n, m, p, ka, kx;
    double t, tau, r1, r2;
    int task = 2;
    char* namea = 0;
    char* namex = 0;
    if (!((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%le", &tau) == 1 && sscanf(argv[2], "%d", &m) == 1 &&\
        sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 &&\
        sscanf(argv[5], "%d", &ka) == 1 && (ka >= 0 && ka <= 4)) || (ka != 0 && argc > 9)){
        printf("Usage %s tau m n p ka [namea] kb [nameb] \n", argv[0]);
        return 1;
    }
    if (argc == 7){
        if (!(sscanf(argv[6], "%d", &kx) == 1 && (kx > 0 && kx <= 4) && (ka != 0))){
            printf("Usage %s tau m n p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    if (argc == 8 && ka == 0){
        namea = argv[6];
        if (!(sscanf(argv[7], "%d", &kx) == 1 && (kx > 0 && kx <= 4))){
            printf("Usage %s tau m n p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    else if (argc == 8 && ka != 0){
        if (!(sscanf(argv[6], "%d", &kx) == 1 && kx == 0)){
            printf("Usage %s tau m n p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        namex = argv[7];
    }
    if (argc == 9){
        namea = argv[6];
        if (!(sscanf(argv[7], "%d", &kx) == 1 && kx == 0)){
            printf("Usage %s tau m n p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        namex = argv[8];
    }

    a = (double*)malloc(n * n * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (namea){
        io_status reta;
        reta = read_matrix(a, n, n, namea);
        do{
            switch(reta){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", namea); break;
                case ERROR_READ: printf("Cannot read %s \n", namea); break;
            }
            free(a);
            return 3;
        } while(0);
    }
    else{
        init_matrix(a, n, n, ka);
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
    if (namex){
        io_status retx;
        retx = read_matrix(x, n, 1, namex);
        do{
            switch(retx){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", namex); break;
                case ERROR_READ: printf("Cannot read %s \n", namex); break;
            }
            free(a);
            free(b);
            free(x);
            return 3;
        } while(0);
    }
    else{
        init_matrix(x, n, 1, kx);
    }
    xm = (double*)malloc(n * 1 * sizeof(double));
    if (!xm){
        printf("Not enough memory!\n");
        free(a);
        free(b);
        free(x);
        return 2;
    }
    printf("Initial matrix a \n");
    print_matrix(a, n, n, p);
    printf("Initial matrix x \n");
    print_matrix(x, n, 1, p);
    printf("Initial matrix b \n");
    print_matrix(b, n, 1, p);
    t = clock();
    solve2(a, x, b, xm, n, m, tau);
    r1 = r1_(a, b, xm, n);
    r2 = r2_(xm, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("Final matrix xm \n");
    print_matrix(xm, 1, n, p);
    printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);
    free(a);
    free(b);
    free(x);
    free(xm);
    return 0;
}