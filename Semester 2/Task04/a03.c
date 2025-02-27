#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#include "sravneniya.h"
#include "sortirovki.h"
int main(int argc, char* argv[]){
    int n = 0, p = 0, c = 0;
    char* name = 0;
    char** a = 0;
    io_status ret;
    char* x = 0;
    int res = 0, task = 3;
    double t = 0;
    int (*f[])(const char* , const char*) = {up_strcmp, down_strcmp, up_len, down_len};
    int (*cmp)(const char* , const char*);
    int len_f = sizeof(f) / sizeof(f[0]);
    if (!(argc == 6 && sscanf(argv[2], "%d", &c) == 1 && sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 &&\
        c >= 1 && c <= len_f)){
        printf("Usage: %s x c n p filename\n", argv[0]);
        return 1;
    }
    cmp = f[c - 1];
    name = argv[5];
    x = argv[1];
    a = (char**)malloc(n * sizeof(char*));
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    ret = read_array(a, n, name);
    do{
        switch(ret){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
            case ERROR_MEMORY: printf("Not enough memory!\n"); break;
        }
        free(a);
        return 3;
    }while(0);
    print_array(a, n, p);
    t = clock();
    res = sort3(x, a, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("New array:\n");
    print_array(a, n, p);
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete_array(a, n);
    free(a);
    return 0;
}