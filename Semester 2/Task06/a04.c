#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    double* b;
    double* x;
    int n, m, p, ka, kb, kx;
    double t, res;
    int task = 4;
    char* namea = 0;
    char* nameb = 0;
    char* namex = 0;
    if (!((argc == 7 || argc == 8 || argc == 9 || argc == 10) && sscanf(argv[1], "%d", &n) == 1 &&\
        sscanf(argv[2], "%d", &m) == 1 && sscanf(argv[3], "%d", &p) == 1 &&\
        sscanf(argv[4], "%d", &ka) == 1 && (ka >= 0 && ka <= 4)) || (ka != 0 && argc > 7)){
        printf("Usage %s n m p ka [namea] kb [nameb] kx [namex]\n", argv[0]);
        return 1;
    }
    if (argc == 7){
        if (!(sscanf(argv[5], "%d", &kb) == 1 && (kb > 0 && kb <= 4) && sscanf(argv[6], "%d", &kx) == 1 && (kx > 0 && kx <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
    }
    if (argc == 8 && ka == 0){
        namea = argv[5];
        if (!(sscanf(argv[6], "%d", &kb) == 1 && (kb > 0 && kb <= 4) && sscanf(argv[7], "%d", &kx) == 1 && (kx > 0 && kx <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
    }
    else if (argc == 8 && ka != 0){
        if (!(sscanf(argv[5], "%d", &kb) == 1 && (kb >= 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
        if (kb == 0){
            nameb = argv[6];
            if(!(sscanf(argv[7], "%d", &kx) == 1 && kx != 0)){
                printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
                return 1;
            }
        }
        else{
            if(!(sscanf(argv[6], "%d", &kx) == 1 && kx == 0)){
                printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
                return 1;
            }
            namex = argv[7];
        }
    }
    if (argc == 9 && ka != 0){
        if (!(sscanf(argv[5], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
        nameb = argv[6];
        if (!(sscanf(argv[7], "%d", &kx) == 1 && kx == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
        namex = argv[8];
    }
    else if (argc == 9 && ka == 0){
        namea = argv[5];
        if (!(sscanf(argv[6], "%d", &kb) == 1 && (kb >= 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
        if (kb == 0){
            nameb = argv[7];
            if(!(sscanf(argv[8], "%d", &kx) == 1 && kx != 0)){
                printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
                return 1;
            }
        }
        else{
            if(!(sscanf(argv[7], "%d", &kx) == 1 && kx == 0)){
                printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
                return 1;
            }
            namex = argv[8];
        }
    }
    if (argc == 10){
        namea = argv[5];
        if (!(sscanf(argv[6], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex]\n", argv[0]);
            return 1;
        }
        nameb = argv[7];
        if(!(sscanf(argv[8], "%d", &kx) == 1 && kx == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] kx [namex] \n", argv[0]);
            return 1;
        }
        namex = argv[9];
    }
    a = (double*)malloc(n * m * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (namea){
        io_status reta;
        reta = read_matrix(a, n, m, namea);
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
        init_matrix(a, n, m, ka);
    }
    x = (double*)malloc(m * 1 * sizeof(double));
    if (!x){
        printf("Not enough memory!\n");
        free(a);
        return 2;
    }
    if (namex){
        io_status retx;
        retx = read_matrix(x, m, 1, namex);
        do{
            switch(retx){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", namex); break;
                case ERROR_READ: printf("Cannot read %s \n", namex); break;
            }
            free(a);
            free(x);
            return 3;
        } while(0);
    }
    else{
        init_matrix(x, m, 1, kx);
    }
    b = (double*)malloc(n * 1 * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        free(a);
        free(x);
        return 2;
    }
    if (nameb){
        io_status retb;
        retb = read_matrix(b, n, 1, nameb);
        do{
            switch(retb){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", nameb); break;
                case ERROR_READ: printf("Cannot read %s \n", nameb); break;
            }
            free(a);
            free(x);
            free(b);
            return 3;
        } while(0);
    }
    else{
        init_matrix(b, n, 1, kb);
    }
    printf("Initial matrix a \n");
    print_matrix(a, n, m, p);
    printf("Initial matrix x \n");
    print_matrix(x, m, 1, p);
    printf("Initial matrix b \n");
    print_matrix(b, n, 1, p);
    t = clock();
    res = solve4(a, x, b, n, m);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    free(x);
    free(b);
    return 0;
}