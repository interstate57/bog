#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    double* b;
    double* c;
    int n, m, p, ka, kb, k;
    double t;
    int task = 10;
    char* namea = 0;
    char* nameb = 0;
    if (!((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%d", &n) == 1 &&\
        sscanf(argv[2], "%d", &m) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &k) == 1 &&\
        sscanf(argv[5], "%d", &ka) == 1 && (ka >= 0 && ka <= 4)) || !(ka == 0 && argc > 7)){
        printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
        return 1;
    }
    if (argc == 7){
        if (!(sscanf(argv[6], "%d", &kb) == 1 && (kb > 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    if (argc == 8 && ka == 0){
        namea = argv[6];
        if (!(sscanf(argv[7], "%d", &kb) == 1 && (kb > 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    else if (argc == 8 && ka != 0){
        if (!(sscanf(argv[6], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        nameb = argv[7];
    }
    if (argc == 9){
        namea = argv[6];
        if (!(sscanf(argv[7], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        nameb = argv[8];
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
    b = (double*)malloc(m * k * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        free(a);
        return 2;
    }
    if (nameb){
        io_status retb;
        retb = read_matrix(a, m, k, namea);
        do{
            switch(retb){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open %s \n", nameb); break;
                case ERROR_READ: printf("Cannot read %s \n", nameb); break;
            }
            free(a);
            free(b);
            return 3;
        } while(0);
    }
    else{
        init_matrix(a, m, k, kb);
    }
    c = (double*)malloc(n * k * sizeof(double));
    if (!c){
        printf("Not enough memory!\n");
        free(a);
        free(b);
        return 2;
    }
    printf("Initial matrix a \n");
    print_matrix(a, n, m, p);
    printf("Initial matrix b \n");
    print_matrix(a, m, 1, p);
    t = clock();
    solve10(a, b, c, n, m, k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("Final matrix\n");
    print_matrix(c, n, 1, p);
    printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);
    free(a);
    free(b);
    free(c);
    return 0;
}