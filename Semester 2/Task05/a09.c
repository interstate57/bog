#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char* argv[]){
    double* a;
    double* b;
    double* c;
    int n, m, p, ka, kb;
    double t;
    int task = 9;
    char* namea = 0;
    char* nameb = 0;
    if (!((argc == 6 || argc == 7 || argc == 8) && sscanf(argv[1], "%d", &n) == 1 &&\
        sscanf(argv[2], "%d", &m) == 1 && sscanf(argv[3], "%d", &p) == 1 &&\
        sscanf(argv[4], "%d", &ka) == 1 && (ka >= 0 && ka <= 4)) || (ka != 0 && argc > 7)){
        printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
        return 1;
    }
    if (argc == 6){
        if (!(sscanf(argv[5], "%d", &kb) == 1 && (kb > 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    if (argc == 7 && ka == 0){
        namea = argv[5];
        if (!(sscanf(argv[6], "%d", &kb) == 1 && (kb > 0 && kb <= 4))){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
    }
    else if (argc == 7 && ka != 0){
        if (!(sscanf(argv[5], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        nameb = argv[6];
    }
    if (argc == 8){
        namea = argv[5];
        if (!(sscanf(argv[6], "%d", &kb) == 1 && kb == 0)){
            printf("Usage %s n m p ka [namea] kb [nameb] \n", argv[0]);
            return 1;
        }
        nameb = argv[7];
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
    b = (double*)malloc(m * 1 * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        free(a);
        return 2;
    }
    if (nameb){
        io_status retb;
        retb = read_matrix(b, m, 1, nameb);
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
        init_matrix(b, m, 1, kb);
    }
    c = (double*)malloc(n * 1 * sizeof(double));
    if (!c){
        printf("Not enough memory!\n");
        free(a);
        free(b);
        return 2;
    }
    printf("Initial matrix a \n");
    print_matrix(a, n, m, p);
    printf("Initial matrix b \n");
    print_matrix(b, m, 1, p);
    t = clock();
    solve9(a, b, c, n, m);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("Final matrix\n");
    print_matrix(c, n, 1, p);
    printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);
    free(a);
    free(b);
    free(c);
    return 0;
}