#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#include "sravneniya.h"
#include "sortirovki.h"
int main(int argc, char* argv[]){
    int n = 0, pa = 0, s = 0, m = 0, pb = 0, diff = 0;
    char* name1 = 0;
    char* name2 = 0;
    char** a = 0;
    char** b = 0;
    char** c = 0;
    io_status reta, retb;
    int task = 2;
    double t = 0;
    int (*f[])(const char* , const char*) = {up_strcmp, down_strcmp, up_len, down_len};
    int len_f = sizeof(f) / sizeof(f[0]);
    int (*cmp)(const char* , const char*);
    if (!(argc == 8 && sscanf(argv[1], "%d", &s) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &pa) == 1 &&\
        s >= 1 && s <= len_f && sscanf(argv[5], "%d", &m) == 1 && sscanf(argv[6], "%d", &pb) == 1)){
        printf("Usage: %s s n pa filename1 m pb filename2\n", argv[0]);
        return 1;
    }
    cmp = f[s - 1];
    name1 = argv[4];
    name2 = argv[7];
    a = (char**)malloc(n * sizeof(char*));
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    reta = read_array(a, n, name1);
    do{
        switch(reta){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
            case ERROR_MEMORY: printf("Not enough memory!\n"); break;
        }
        free(a);
        return 3;
    }while(0);
    for (int i = 0; i < n - 1; i ++){
        if (cmp(a[i + 1], a[i]) < 0){
            printf("Array a is not an increasing one\n");
            delete_array(a, n);
            free(a);
            return 5;
        }
    }
    b = (char**)malloc(m * sizeof(char*));
    if (!b){
        printf("Cannot allocate memory!\n");
        delete_array(a, n);
        free(a);
        return 2;
    }
    retb = read_array(b, m, name2);
    do{
        switch(retb){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
            case ERROR_MEMORY: printf("Not enough memory!\n"); break;
        }
        delete_array(a, n);
        free(a);
        free(b);
        return 3;
    }while(0);
    for (int i = 0; i < m - 1; i ++){
        if (cmp(b[i + 1], a[i]) < 0){
            printf("Array b is not an increasing one\n");
            delete_array(a, n);
            free(a);
            delete_array(b, m);
            free(b);
            return 5;
        }
    }
    print_array(a, n, pa);
    print_array(b, m, pb);
    c = (char**)malloc((n + m) * sizeof(char*));
    if (!c){
        printf("Cannot allocate memory!\n");
        delete_array(a, n);
        free(a);
        delete_array(b, m);
        free(b);
        return 2;
    }
    t = clock();
    merge(a, b, n, m, c, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference (c, n + m, cmp);
    printf ("New array:\n");
    print_array (c, n + m, pa + pb);
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    delete_array(a, n);
    free(a);
    delete_array(b, m);
    free(b);
    free(c);
    return 0;
}